//  ***************************************************************************
//  *                                                           
//  *   DESCRIPTION:                                  
//  *                                                           
//  *   FILE:   list.cpp                               
//  *                                                           
//  *   MODULE:                                        
//  *                                                           
//  *   Copyright (c) 2013 by Fabio D'Alfonso                        
//  *   For instructional purposes only.  No warranties.        
//  *                                                           
//  ***************************************************************************
//  *
//  *   Based on Material by Ronald Mak 
//  *   Copyright (c) 1996
//  *
//  ***************************************************************************
#include<iostream>
#include "error.h"
#include "buffer.h"
using namespace std;

//-----------------------------------------------------------------------------
//  main 
//-----------------------------------------------------------------------------

int main( int argc, char * argv[]) {
    char ch; // character fetched from source

    //--Check the command line arguments.
    if(argc != 2) {
        cerr << "Usage list <source file>"  << endl;
        AbortTranslation(abortInvalidCommandLineArgs);
    }

    //--Create source file buffer.
    SourceBuffer source(argv[1]);

    //--Loop to fetch each character of the source.
    do {
        ch= source.GetChar();
    } while (ch != eofChar);
}
