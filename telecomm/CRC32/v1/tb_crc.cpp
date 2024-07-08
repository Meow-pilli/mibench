SC_MODULE(Testbench) {
    sc_signal<bool> clk;
    sc_signal<bool> reset;
    sc_signal<unsigned char> data_in;
    sc_signal<DWORD> crc_out;

    CRC32 *crc32_module;

    void generate_clock() {
        while (true) {
            clk.write(false);
            wait(5, SC_NS);
            clk.write(true);
            wait(5, SC_NS);
        }
    }

    void run() {
        reset.write(true);
        wait(10, SC_NS);
        reset.write(false);
        wait(10, SC_NS);

        // Test data
        unsigned char test_data[] = { 'a', 'b', 'c', 'd', 'e' };
        for (int i = 0; i < 5; i++) {
            data_in.write(test_data[i]);
            wait(10, SC_NS);
        }

        sc_stop();
    }

    SC_CTOR(Testbench) {
        crc32_module = new CRC32("crc32_module");
        crc32_module->clk(clk);
        crc32_module->reset(reset);
        crc32_module->data_in(data_in);
        crc32_module->crc_out(crc_out);

        SC_THREAD(generate_clock);
        SC_THREAD(run);
    }

    ~Testbench() {
        delete crc32_module;
    }
};