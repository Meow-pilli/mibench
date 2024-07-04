# Makefile
SYSTEMC_HOME = /home/user/systemc/systemc-3.0.0
SYSTEMC_INC = -I$(SYSTEMC_HOME)/include
SYSTEMC_LIB = -L$(SYSTEMC_HOME)/lib-linux64 -lsystemc

all: crc_32_systemc

crc_32_systemc: crc_32_systemc.cpp
	g++ crc_32_systemc.cpp -o crc_32_systemc $(SYSTEMC_INC) $(SYSTEMC_LIB)

clean:
	rm -rf crc_32_systemc output*

