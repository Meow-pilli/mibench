
#include "crc32.h"
#include "tb_crc32.h"


int sc_main(int argc, char** argv)
{
  sc_clock                clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
  sc_signal<bool>         rst;
  sc_signal<sc_uint<8> >  in_data;

 
  sc_signal<sc_uint<8> > crc32_output; 
  int x;
  char name[10];


  crc32 u_CRC32("CRC*");
  test_CRC32 test("test_CRC32");

  //connect to ave8 module
  u_CRC32.clk( clk );
  u_CRC32.rst( rst );


  u_CRC32.in_data( in_data );

  u_CRC32.crc32_output( crc32_output );

  // connect to test bench
  test.clk( clk );
  test.rst( rst );
  

   test.in_data( in_data );


  test.crc32_output( crc32_output );


#ifdef WAVE_DUMP
  // Trace files
  sc_trace_file* trace_file = sc_create_vcd_trace_file("trace_behav");

  // Top level signals
  sc_trace(trace_file, clk              , "clk");
  sc_trace(trace_file, rst              , "rst"); 
  sc_trace(trace_file, in_data          , "ind_data");
  sc_trace(trace_file, filter_output    , "crc32_output");

#endif  // End WAVE_DUMP

  sc_start( 25, SC_NS );
  rst.write(0);

  sc_start( 25, SC_NS );
  rst.write(1);

  sc_start();

#ifdef WAVE_DUMP
   sc_close_vcd_trace_file(trace_file);
#endif

    return 0;

};
