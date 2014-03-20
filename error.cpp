//  ***************************************************************************
//  *                                                           
//  *   DESCRIPTION:                                  
//  *                                                           
//  *   FILE:   error.cpp                               
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
#include<cstdlib>
#include<iostream>
#include "error.h"
using namespace std;

int errorCount = 0; // count of syntax errors

//-----------------------------------------------------------------------------
//  Abort messages  Keyed to enumeration type AbortCode
//-----------------------------------------------------------------------------

static char* abortMsg[] = {
    NULL,
    "Invalid command line arguments",
    "Failed to open source file",
    "Failed to open intermediate form file",
    "Failed to open assembly file",
    "Too many syntax errors",
    "Stack overflow",
    "Code segment overflow",
    "Nesting too deep",
    "Runtime error",
    "Unimplemented feature",
};

//-----------------------------------------------------------------------------
//  AbortTranslation A fatal error occurred during the code translation. Print
//  the abort code to the error file and then exit.
//-----------------------------------------------------------------------------

void AbortTranslation(AbortCode ac) {
    cerr << " *** Fatal translator error: " << abortMsg[-ac] << endl;
    exit(ac);
}

