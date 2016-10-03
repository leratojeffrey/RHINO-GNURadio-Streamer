/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <gnuradio/gr_complex.h>
#include <algorithm>
#include <stdexcept>
#include <complex>
#include <volk/volk.h>
#include <gnuradio/io_signature.h>
#include "RHINO_c_2_impl.h"

static const int64_t MAX_INT =  2147483647; //  (2^31)-1
static const int64_t MIN_INT = -2147483647; // -(2^31)-1

namespace gr {
  namespace MpatiBlocks {

    RHINO_c_2::sptr
    RHINO_c_2::make(size_t itemsize,int port,int payLoad)
    {
      return gnuradio::get_initial_sptr
        (new RHINO_c_2_impl(itemsize, port, payLoad));
    }

    /*
     * The private constructor
     */
    RHINO_c_2_impl::RHINO_c_2_impl(size_t itemsize,int port,int payLoad)
      : gr::sync_block("RHINO_c",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, itemsize)),d_itemsize(itemsize),c_port(port),c_payLoad(payLoad)
    {
		
		 Sconnect(c_port);
	}

    /*
     * Our virtual destructor.
     */
    RHINO_c_2_impl::~RHINO_c_2_impl()
    {
    }

    int
    RHINO_c_2_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {

      std::vector<short> serverMessage;
      serverMessage.resize(4);
      
      int num_bytes_to_send = (c_payLoad/d_itemsize);
     
	  //----------------------------------------------------------------------
	   
	  if(type==Short)
		{
			
			short *out = (short *) output_items[0]; // |I|0|0|0|
			for( int i =0;i<num_bytes_to_send;i+=2)
			{	
					serverMessage=receive_data();
					out[i]=(short)serverMessage[0];
					//out[i+1]=(short)serverMessage[1];
			}
		}
		
		else if(type==Int)
		{
			
			int32_t  *out =(int32_t *) output_items[0]; // |I|0|0|0|
			for( int i =0;i<num_bytes_to_send;i+=2)
			{	
				serverMessage=receive_data();
				int32_t r = llrintf(serverMessage[0]);
				int32_t r1 = llrintf(serverMessage[1]);
				if (r < MIN_INT)
					r = MIN_INT;
				else if (r > MAX_INT)
					r = MAX_INT;
						
				if (r1 < MIN_INT)
					r1 = MIN_INT;
				else if (r > MAX_INT)
					r1 = MAX_INT;		
				
					
				out[i] = static_cast<int>(r);
				//out[i+1] = static_cast<int>(r1);
			}
		}
		else if(type==Float)
		{
			
			float *out = (float*) output_items[0]; // |I|0|0|0|
			for( int i =0;i<num_bytes_to_send;i+=2)
			{	
				serverMessage=receive_data();
				out[i]=(float)serverMessage[0];
				//out[i+1]=(float)serverMessage[1];
				
			}
	
		}
		
		
		else if(type==Complex) // Similar to Default
		{
			gr_complex *out = (gr_complex *) output_items[0]; // |I|Q|0|0|
			for( int i =0;i<num_bytes_to_send;i++)
			{	
				serverMessage=receive_data();
				//out[2*i+1]=gr_complex((float)serverMessage[2],(float)serverMessage[3]);
				out[i]=gr_complex((float)serverMessage[0],(float)serverMessage[1]);
				
			}
		}
	   else
		{
			gr_complex *out = (gr_complex *) output_items[0];  // |I|Q|0|0|
			for( int i =0;i<num_bytes_to_send;i++)
			{	
				serverMessage=receive_data();
				//out[2*i+1]=gr_complex(serverMessage[2],serverMessage[3]); //2*i+1
				out[i]=gr_complex((float)serverMessage[0],(float)serverMessage[1]); //2*i
			}
			
		}
	   //----------------------------------------------------------------                    
	   
	   

        // Tell runtime system how many output items we produced.
        return num_bytes_to_send;
    }
    
       
    
    bool RHINO_c_2_impl::Sconnect(int port)
   {
	
	if((udpsocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))<0) 
	{
		exit(1); //[ERROR] Could not Create Socket. Please try Again.
	} 
	
	memset((char*)&rudpserver,0,sizeof(rudpserver));
	rudpserver.sin_family = AF_INET; 
	rudpserver.sin_port = htons(port);
	rudpserver.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(udpsocket,(struct sockaddr*)&rudpserver,sizeof(rudpserver))<0)
	{
		exit(1); //[ERROR] Could not Bind Socket
	}
	
	return true;
  }
  
std::vector<short> RHINO_c_2_impl::receive_data()
{
	
	std::vector<short> IQdata;
	IQdata.resize(4);
	
	int rudpclient_len = sizeof(rudpclient);
	struct rhinodata indata;
	int count = 0;
	
	int cres;	
		
	cres = recvfrom(udpsocket,(char*)&indata,sizeof(struct rhinodata),0,(struct sockaddr *)&rudpclient,(socklen_t *)&rudpclient_len);
	if(cres<0)
	{
		return IQdata; //[ERROR] Problem Receiving Data. Please try Again
	}
	IQdata[count] = (indata.I1>>8) + (indata.I1<<8);
	IQdata[count+1] = (indata.Q1>>8) + (indata.Q1<<8);
	IQdata[count+2] = (indata.I2>>8) + (indata.I2<<8);
	IQdata[count+3] = (indata.Q2>>8) + (indata.Q2<<8);
	
	return IQdata;
}

  
  void RHINO_c_2_impl::set_port(int port)
  {
	 c_port=port;
  }
	 
	 
  void RHINO_c_2_impl::set_payLoad(int payLoad)
  {
	  c_payLoad=payLoad;
  }

  } /* namespace MpatiBlocks */
} /* namespace gr */

