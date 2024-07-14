#include <systemc.h>
#include "crc.h"

SC_MODULE(Testbench) {
    sc_signal<bool> clk;
    sc_signal<bool> reset;
    sc_signal<bool> data_in_valid;
    sc_signal<unsigned char> data_in;
    sc_signal<bool> crc_out_valid;
    sc_signal<sc_uint<32>> crc_out;

    CRC32 *crc32_inst;

    void clk_gen() {
        while (true) {
            clk.write(true);
            wait(10, SC_NS);
            clk.write(false);
            wait(10, SC_NS);
        }
    }

    void stim() {
        reset.write(true);
        wait(20, SC_NS);
        reset.write(false);
        wait(20, SC_NS);

        data_in_valid.write(true);
        data_in.write('A');
        wait(20, SC_NS);

        data_in.write('B');
        wait(20, SC_NS);

        data_in.write('C');
        wait(20, SC_NS);

        data_in_valid.write(false);
        wait(40, SC_NS);

        sc_stop();
    }

    SC_CTOR(Testbench) {
        crc32_inst = new CRC32("CRC32");
        crc32_inst->clk(clk);
        crc32_inst->reset(reset);
        crc32_inst->data_in_valid(data_in_valid);
        crc32_inst->data_in(data_in);
        crc32_inst->crc_out_valid(crc_out_valid);
        crc32_inst->crc_out(crc_out);

        SC_THREAD(clk_gen);
        SC_THREAD(stim);
    }

    ~Testbench() {
        delete crc32_inst;
    }
};

int sc_main(int argc, char* argv[]) {
    Testbench tb("tb");
    sc_start();
    return 0;
}
