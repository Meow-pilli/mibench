
#include "define.h"


#ifndef TB_CRC32_H_
#define TB_CRC32_H_

SC_MODULE (test_CRC32){

  // Inputs
  sc_in<bool>          clk;
  sc_in<bool>          rst;

  sc_in<sc_uint<8> > crc32_output; 

  // Outputs
  sc_out<sc_uint<8> >  in_data;



  //File pointers
  FILE * in_crc32_file, *out_crc32_golden_file, *out_crc32_file_read;
  FILE  *out_crc32_file, *diff_file;

  
  /* C */
  void compare_results();

  /* R  */
  void recv();

  /* S */
  void send();


  SC_CTOR ( test_CRC32 ) {
 
    SC_CTHREAD(send,clk.pos());
    reset_signal_is(rst,false);

    SC_CTHREAD(recv,clk.pos());
    reset_signal_is(rst,false);
  }

  ~test_CRC32(){}

};


#endif  // TB_CRC32_H
