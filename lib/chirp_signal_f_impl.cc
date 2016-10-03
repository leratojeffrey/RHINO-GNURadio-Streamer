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

#include <gnuradio/io_signature.h>
#include "chirp_signal_f_impl.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

namespace gr {
  namespace MpatiBlocks {

    chirp_signal_f::sptr
    chirp_signal_f::make(float phase,float freq_0,float freq_1,float time_1)
    {
      return gnuradio::get_initial_sptr
        (new chirp_signal_f_impl(phase,freq_0,freq_1,time_1));
    }

    /*
     * The private constructor
     */
    chirp_signal_f_impl::chirp_signal_f_impl(float phase,float freq_0,float freq_1,float time_1)
      : gr::sync_block("chirp_signal_f",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(float))),f_phase(phase),f_freq_0(freq_0),f_freq_1(freq_1),f_time_1(time_1)
    {}

    /*
     * Our virtual destructor.
     */
    chirp_signal_f_impl::~chirp_signal_f_impl() 
    {
    }

    int
    chirp_signal_f_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
     float *out = (float *) output_items[0];
  
	 std::vector<float>  t;// = 0.0:0.001:5.0;
	 int L = 5000;  //number of samples
	 t.resize(L);	// time interval
	 
	 //calculations of attributes
	 float phase = 2*(M_PI*f_phase)/360.0f; 
	 float a = (M_PI *(f_freq_1-f_freq_0))/f_time_1;
	 float b = 2*M_PI*f_freq_0;	
	 float tindexer = 0.0f;
	 //
	 
	
		for(int i = 0; i< L; i++)
		{
			t[i] = tindexer;
			tindexer = tindexer + 0.001f;
		}

		for(int i = 0; i < L; i++) // or L instead of noutput
		{
			out[i] = cos(a*pow(t[i],2)+(b*t[i])+phase);
		}	
	
		return noutput_items;
		
	}
		
    
    
    void
    chirp_signal_f_impl::set_phase(float phase)
    {
      f_phase = phase;
    }

    void
    chirp_signal_f_impl::set_start_freq(float frequency)
    {
      f_freq_0= frequency;
    }

    void
    chirp_signal_f_impl::set_freq_1(float freq)
    {
      f_freq_1=freq;

    }

    void
    chirp_signal_f_impl::set_time(float t)
    {
      f_time_1 = t;
    }

  } /* namespace MpatiBlocks */
} /* namespace gr */

