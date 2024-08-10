
#include "tb_crc32.h"


//--------------------------
// Send data thread
//--------------------------
void test_CRC32::send(){

  // Variables declaration
  int i=0;
  unsigned int  in_crc32_read;

  //Reset routine
  in_crc32_file = fopen(INFILENAME, "rt");


  if(!in_crc32_file){
    cout << "Could not open " << INFILENAME << "\n";
    sc_stop();
    exit (-1);
  }


  wait();
  i= 0;
  while(true){

    while(fscanf(in_crc32_file,"%u", &in_crc32_read) != EOF){
	in_data.write(in_crc32_read);
	  wait();
    }
  
   
    fclose(in_crc32_file);

    cout << endl << "Starting comparing results " << endl;
 
    compare_results();
    sc_stop();

    wait();

  }//while_loop
}



//-----------------------------
// Receive data thread
//----------------------------
void test_CRC32::recv(){

  // Variables declaration
  unsigned int crc32_out_write=0;

  out_crc32_file = fopen (OUTFILENAME, "wt");

  if(!out_crc32_file){
    cout << "Could not open " << OUTFILENAME << "\n";
    sc_stop();
    exit (-1);
  }


  wait();

  while(true){
    crc32_out_write = crc32_output.read();

    fprintf(out_crc32_file,"%d\n",crc32_out_write);

    wait();
  }
}


//---------------------------------
// Compare results function
//--------------------------------
void test_CRC32::compare_results(){

  int outcrc32, outcrc32_golden, line=1, errors=0;

  // Close file where outputs are stored
  fclose(out_crc32_file);

  // Open results file
  out_crc32_file = fopen (OUTFILENAME, "rt");

  if(!out_crc32_file){
    cout << "Could not open " << OUTFILENAME << endl;
    sc_stop();
    exit (-1);
  }

    //
    //Load the golden output from file
    //
    out_crc32_golden_file = fopen (OUTFILENAME_GOLDEN, "rt");
    if(!out_crc32_golden_file){
      cout << "Could not open " << OUTFILENAME_GOLDEN << endl;
      sc_stop();
      exit (-1);
     }

    //
    // comparison result with golden output
    //

    diff_file = fopen (DIFFFILENAME, "w");
    if(!diff_file){
	 cout << "Could not open " << DIFFFILENAME<< "\n";
	 sc_stop();
	 exit (-1);
       }

    while(fscanf(out_crc32_golden_file, "%d", &outcrc32_golden) != EOF){
      fscanf(out_crc32_file,"%d", &outcrc32);
     

      cout << endl <<"Cycle["<< line << "]: " << outcrc32_golden << "-- "<< outcrc32;


	   if(outcrc32 != outcrc32_golden){
	     cout << "\nOutput missmatch [line:" << line << "] Golden:" << outcrc32_golden << " -- Output:" << outcrc32;

	     fprintf(diff_file,"\nOutput missmatch[line:%d] Golden: %d -- Output: %d",line, outcrc32_golden, outcrc32);
	     
	     errors++;
	   }

          line ++;

    }

    if(errors == 0)
      cout << endl << "Finished simulation SUCCESSFULLY" << endl;
    else
      cout << endl << "Finished simulation " << errors << " MISSMATCHES between Golden and Simulation" << endl;


    fclose(out_crc32_file);
    fclose(diff_file);
    fclose(out_crc32_golden_file);



}

