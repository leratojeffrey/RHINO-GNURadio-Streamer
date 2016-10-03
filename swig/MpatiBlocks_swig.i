/* -*- c++ -*- */

#define MPATIBLOCKS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "MpatiBlocks_swig_doc.i"

%{
#include "MpatiBlocks/chirp_signal_f.h"
#include "MpatiBlocks/chirpSignal2_f.h"
#include "MpatiBlocks/RHINO_c.h"
#include "MpatiBlocks/RHINO_c_2.h"
%}


%include "MpatiBlocks/chirp_signal_f.h"
GR_SWIG_BLOCK_MAGIC2(MpatiBlocks, chirp_signal_f);
%include "MpatiBlocks/chirpSignal2_f.h"
GR_SWIG_BLOCK_MAGIC2(MpatiBlocks, chirpSignal2_f);
%include "MpatiBlocks/RHINO_c.h"
GR_SWIG_BLOCK_MAGIC2(MpatiBlocks, RHINO_c);
%include "MpatiBlocks/RHINO_c_2.h"
GR_SWIG_BLOCK_MAGIC2(MpatiBlocks, RHINO_c_2);




