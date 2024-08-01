//---------------------------------------------------------------------------
//
//
// File Name    : qsort.h
// Description  : Quick sort module declaration
// Release Date : 01/08/13
// Author       : PolyU DARC Group
//                Benjamin Carrion Schafer, Anushree Mahapatra
//
// Revision History
//---------------------------------------------------------------------------
// Date       Version      Author       Description
//---------------------------------------------------------------------------
//            1.0       Darel Rex Finley   Initial version. This public-domain C implementation by
// 01/08/13   1.1       PolyU DARC Group   Conversion into Synthesizable SystemC
//---------------------------------------------------------------------------

#ifndef CRC32_H
#define CRC32_H

#include "define.h"


SC_MODULE(crc32)
{
    sc_in<bool> clk;
    sc_in<bool> rst;

   sc_in<sc_uint<8> > indata;
   sc_out<sc_uint<8> > odata;


   /* R */
   //void UPDC32();
   uint32_t UPDC32(unsigned char ch, uint32_t crc);
   void crc32buf(char *buf, size_t len, uint32_t *oldcrc32);
	
   SC_CTOR(crc32)
     {
       SC_CTHREAD(crc32buf, clk.pos()) ;
       reset_signal_is(rst, false) ;
     }

   ~crc32(){}

};

#endif 

