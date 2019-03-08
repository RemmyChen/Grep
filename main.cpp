/*
 *
 *  COMP 15 Project 2 Gerp - It's Like grep But Something Is Off
 *
 *  main.cpp
 *  Main executable.
 *  Modified By (UTLN): rchen07
 *           On       : 11/30/2017
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>

#include "Gerp.h"

using namespace std;


void report_unopen();
void report_usg_error();

int main(int argc, char *argv[])
{
    if (argc != 2) {
   		report_usg_error();
   	}

    Gerp gerp;
    gerp.index(argv[1]);
    cout << "Query? ";
    gerp.takeorder(cin);
    cout << endl << "Goodbye! Thank you and have a nice day." << endl;
        
   	return 0;
}


/*  PURPOSE: prints error when folder can't open
    RETURN: void
    PARAMETERS: none */
void report_unopen()
{
    cerr << "Unable to open folder" << endl;
    exit(1);
}



/*  PURPOSE: prints error when command line is incorrect
    RETURN: void
    PARAMETERS: none */
void report_usg_error()
{
    cerr << "Usage: gerp directory" << endl;
    cerr << "            where: directory is a valid directory" << endl;
    exit(1); 
}