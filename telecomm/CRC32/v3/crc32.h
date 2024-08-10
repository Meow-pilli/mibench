#ifndef CRC32_H_
#define CRC32_H_


#include "define.h"


SC_MODULE (crc32) {


public:

   // Inputs
   sc_in_clk clk;
   sc_in<bool> rst;
   sc_in<sc_uint<8> > in_data ;

   // Output
   sc_out< sc_uint<8> > crc32_output ;


   /* F */
   void crc32_main ( void );


   // Constructor
 SC_CTOR (crc32) {

       SC_CTHREAD (crc32_main, clk.pos() );
       reset_signal_is(rst, false) ;
       sensitive << clk.pos();

   }

   // Destructor
   ~crc32() {}


};


#endif   //  CRC32_H_

