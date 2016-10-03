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

#ifndef INCLUDED_MPATIBLOCKS_RHINO_C_2_IMPL_H
#define INCLUDED_MPATIBLOCKS_RHINO_C_2_IMPL_H

#include <MpatiBlocks/RHINO_c_2.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <unistd.h>  
#include <time.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <fstream>


namespace gr {
  namespace MpatiBlocks {
	  
	  
	 struct rhinodata
	{
	short I1;
	short Q1;
	short I2;
	short Q2;
	short dummy; // the zero paddings that make up 10bytes
	};
	
	enum Type
	{
		Complex,
		Float,
		Int,
		Short,
		Complex2
		
	};

    class RHINO_c_2_impl : public RHINO_c_2
    {
     private:
        size_t  d_itemsize;
		int c_port;
		int c_payLoad;
		int udpsocket;
		int clen;
		struct sockaddr_in rudpserver;
		struct sockaddr_in rudpclient;
		Type type;

     public:
      RHINO_c_2_impl(size_t itemsize,int port,int payLoad);
      ~RHINO_c_2_impl();

	       
	   bool Sconnect(int);
	   std::vector<short> receive_data();
	//  size_t getSize(Type t);
      
      
      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
	       
	       
	 int port_number () const {return c_port;}
	 int payLoad_size () const {return c_payLoad;} 
	      
	
	 void set_port(int port);
	 void set_payLoad(int payLoad);    
    };
    
    

  } // namespace MpatiBlocks
} // namespace gr

#endif /* INCLUDED_MPATIBLOCKS_RHINO_C_2_IMPL_H */

