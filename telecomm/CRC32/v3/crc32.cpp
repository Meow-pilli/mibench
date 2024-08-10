#include "crc32.h"


//  Main thread  
void ave8::ave8_main ( void ) {

	// Variables declaration
	sc_uint<11> sum=0; 
	sc_uint<8> buffer[SIZE];
	int i;

	// Reset state - should be executable in 1 clock cycle

	wait();  


	// Main thread	
	while (1) {

		// Shift data
		for(i=SIZE-1; i>0 ;i--)
		buffer[i]=buffer[i-1];

		// Read new data
		buffer[0] = in_data.read();

		// Add values together
		sum=buffer[0];

		for(i=1;i < SIZE ; i++)
		sum += buffer[i];

		// computer average and return value
		ave8_output.write(sum/SIZE) ;
		wait();

	}
}

