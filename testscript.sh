#!/bin/bash
make

echo "pgmEcho correct message for wrong # of parameters"                                PASSED         
echo "EXPECTED: ERROR: Bad Argument Count"                                                                                                                                                                                                                                       
echo "ACTUAL: "
./pgmEcho hi 

echo "pgmEcho correct error string with bad filename"                                   PASSED         
echo "EXPECTED: ERROR: Bad File Name"                                                                                                                                                                                                                            
echo "ACTUAL: "  
./pgmEcho badfile outputfile.pgm

echo "pgmComp correct message for wrong # of parameters"                                PASSED         
echo "EXPECTED: ERROR: Bad Argument Count"                                                                                                                                                                                                                                       
echo "ACTUAL: "
./pgmComp hi

echo "pgmComp correct error string with bad filename"                                   PASSED         
echo "EXPECTED: ERROR: Bad File Name"                                                                                                                                                                                                                            
echo "ACTUAL: "  
./pgmComp badfile outputfile.pgm

echo "pgma2b correct message for wrong # of parameters"                                PASSED         
echo "EXPECTED: ERROR: Bad Argument Count"                                                                                                                                                                                                                                       
echo "ACTUAL: "
./pgma2b hi 

echo "pgma2b correct error string with bad filename"                                   PASSED         
echo "EXPECTED: ERROR: Bad File Name"                                                                                                                                                                                                                            
echo "ACTUAL: "  
./pgma2b badfile outputfile.pgm

echo "pgmb2a correct message for wrong # of parameters"                                PASSED         
echo "EXPECTED: ERROR: Bad Argument Count"                                                                                                                                                                                                                                       
echo "ACTUAL: "
./pgma2b hi 

echo "pgmb2a correct error string with bad filename"                                   PASSED         
echo "EXPECTED: ERROR: Bad File Name"                                                                                                                                                                                                                            
echo "ACTUAL: "  
./pgmb2a badfile outputfile.pgm

echo "pgmReduce correct message for wrong # of parameters"                                PASSED         
echo "EXPECTED: ERROR: Bad Argument Count"                                                                                                                                                                                                                                       
echo "ACTUAL: "
./pgmReduce hi 

echo "pgmReudce correct error string with bad filename"                                   PASSED         
echo "EXPECTED: ERROR: Bad File Name"                                                                                                                                                                                                                            
echo "ACTUAL: "  
./pgmReduce badfile 5 outputfile.pgm

echo "pgmTile correct message for wrong # of parameters"                                PASSED         
echo "EXPECTED: ERROR: Bad Argument Count"                                                                                                                                                                                                                                       
echo "ACTUAL: "
./pgmTile hi 

echo "pgmTile correct error string with bad filename"                                   PASSED         
echo "EXPECTED: ERROR: Bad File Name"                                                                                                                                                                                                                            
echo "ACTUAL: "  
./pgmTile badfile 5 outputfile.pgm

echo "pgmAssemble correct message for wrong # of parameters"                                PASSED         
echo "EXPECTED: ERROR: Bad Argument Count"                                                                                                                                                                                                                                       
echo "ACTUAL: "
./pgmAssemble hi 

echo "pgmAssemble correct error string with bad filename"                                   PASSED         
echo "EXPECTED: ERROR: Bad File Name"                                                                                                                                                                                                                            
echo "ACTUAL: "  
./pgmAssemble badfile 5 5 0 0 outputfile.pgm

make clean