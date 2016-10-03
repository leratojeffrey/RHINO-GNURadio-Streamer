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

#ifndef INCLUDED_MPATIBLOCKS_CHIRP_SIGNAL_F_IMPL_H
#define INCLUDED_MPATIBLOCKS_CHIRP_SIGNAL_F_IMPL_H

#include <MpatiBlocks/chirp_signal_f.h>

namespace gr {
  namespace MpatiBlocks {

    class chirp_signal_f_impl : public chirp_signal_f
    {
     private:
      float f_phase;
      float f_freq_0;
      float f_freq_1;
      float f_time_1;
     

     public:
      chirp_signal_f_impl(float f_phase,float f_freq_0,float f_freq_1,float f_time_1);
      ~chirp_signal_f_impl();

      // Where all the action really happens
        int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
	         
	
	 float starting_freq() const {return f_freq_0;}
	 float frequency_1() const {return f_freq_1;}
	 float time_1() const {return f_time_1;}
     float phase() const {return f_phase;}
     
	
	 void set_phase(float phase_0);
	 void set_start_freq(float freq);
	 void set_freq_1(float _freq);
	 void set_time(float time);   
	 
    };

  } // namespace MpatiBlocks
} // namespace gr

#endif /* INCLUDED_MPATIBLOCKS_CHIRP_SIGNAL_F_IMPL_H */

