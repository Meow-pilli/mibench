// crc_32_systemc.cpp
#include <systemc.h>
#include "crc.h"

SC_MODULE(CRC32) {
    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_in<unsigned char> data_in;
    sc_out<DWORD> crc_out;

    DWORD crc32;
    DWORD crc_32_tab[256];

    void process() {
        if (reset.read() == true) {
            crc32 = 0xFFFFFFFF;  // Initial value for CRC
        } else {
            unsigned char ch = data_in.read();
            crc32 = updateCRC32(ch, crc32);
            crc_out.write(crc32);
        }
    }

    SC_CTOR(CRC32) {
        SC_METHOD(process);
        sensitive << clk.pos();
        sensitive << reset;
        initialize_crc32_table();
    }

    DWORD updateCRC32(unsigned char ch, DWORD crc) {
        return crc_32_tab[(crc ^ ch) & 0xFF] ^ (crc >> 8);
    }

    void initialize_crc32_table() {
        DWORD crc;
        for (int i = 0; i < 256; i++) {
            crc = i;
            for (int j = 8; j > 0; j--) {
                if (crc & 1)
                    crc = (crc >> 1) ^ 0xEDB88320;
                else
                    crc >>= 1;
            }
            crc_32_tab[i] = crc;
        }
    }
};


