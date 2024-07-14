#ifndef CRC_H
#define CRC_H

#include <systemc.h>

// CRC32 Module Declaration
SC_MODULE(CRC32) {
    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_in<bool> data_in_valid;
    sc_in<unsigned char> data_in;
    sc_out<bool> crc_out_valid;
    sc_out<sc_uint<32>> crc_out;

    // Internal variables
    sc_uint<32> crc;

    // Method Prototypes
    void update_crc();

    // Constructor
    SC_CTOR(CRC32) {
        SC_METHOD(update_crc);
        sensitive << clk.pos();
        async_reset_signal_is(reset, true);
    }
};

#endif // CRC_H
