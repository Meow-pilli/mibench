//===========================================================================
//
//
// File Name    : main.cpp
// Description  : crc32 CIPHER and INV CHIPER  main
// Release Date : 24/11/2014 
// Author       : PolyU DARC Lab
//                Benjamin Carrion Schafer, Shuangnan Liu
//
// Revision History
//---------------------------------------------------------------------------
// Date             Author      Version     Description
//---------------------------------------------------------------------------
//14/02/2013        PolyU           1.0     Main system description
//24/11/2014        PolyU           1.1     cipher and inv cipher combined into same file
//
// g++ -o crc32_cipher.exe main.cpp tb_crc32_cipher_3G.cpp crc32_cipher.cpp -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib -lsystemc -lm
//===========================================================================

#include "crc32.h"
#include "tb_crc32.h"


int sc_main(int argc, char** argv)
{
  sc_clock                clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
  sc_signal<bool>         rst;
  sc_signal<sc_uint<8> >  in_data[SIZE];
  sc_signal<sc_uint<8> >  out_data[SIZE];


  int x;
  char name[10];


  crc32 	 u_crc32("crc32");
  test_crc32 test("test_crc32");

  //connect to crc32
  u_crc32.clk( clk );
  u_crc32.rst( rst );
 // u_crc32.mode( mode );

  for(x=0; x < SIZE; x++){
    u_crc32.idata[x]( in_data[x] );
    u_crc32.odata[x]( out_data[x] );
  }


  // connect to Test Bench
  test.clk( clk );
  test.rst( rst );
 // test.mode( mode );

  for(x=0; x < SIZE; x++){
    test.idata[x]( in_data[x] );
    test.odata[x]( out_data[x] );
  }


#ifdef WAVE_DUMP
  // Trace files
  sc_trace_file* trace_file = sc_create_vcd_trace_file("trace_behav");

  // Top level signals
  sc_trace(trace_file, clk             , "clk");
  sc_trace(trace_file, rst             , "rst");

 for(x=0; x < SIZE; x++){
   sprintf(name, "in_data%d",x);   
   sc_trace(trace_file, in_data[x]          , name);

   sprintf(name, "out_data%d",x);   
   sc_trace(trace_file, out_data[x]            , name);
 
  }

#endif  // End WAVE_DUMP

  sc_start( 25, SC_NS );
  rst.write(0);
  //mode.write(0);  // Encrypt DATA. Set to 1 to decrypt

  
  sc_start( 25, SC_NS );
  rst.write(1);

  
  sc_start(1000, SC_NS); 
  sc_start();
#ifdef WAVE_DUMP
   sc_close_vcd_trace_file(trace_file);
#endif

    return 0;

};





