//  ***************************************************************************
//  *
//  *   DESCRIPTION:
//  *
//  *   FILE:   buffer.h
//  *
//  *   MODULE:
//  *
//  *   Copyright (c) 2014 by Fabio D'Alfonso
//  *   For instructional purposes only.  No warranties.
//  *
//  ***************************************************************************
//  *
//  *   Based on Material by Ronald Mak
//  *   Copyright (c) 1996
//  *
//  ***************************************************************************
#ifndef BUFFER_H
#define BUFFER_H

#include<fstream>
#include<cstdio>
#include<cstring>
#include "misc.h"
#include "error.h"
using namespace std;

//-----------------------------------------------------------------------------
//                          **************************
//                          *
//                          *
//                          *         INPUT
//                          *
//                          *
//                          **************************
//-----------------------------------------------------------------------------

extern char eofChar;
extern int inputPosition;
extern int listFlag;
extern int level;

const int maxInputBufferSize = 256;

//-----------------------------------------------------------------------------
// TextInBuffer  Abstract text input class
//-----------------------------------------------------------------------------

class TextInBuffer {
protected:
	fstream file; // input text file
	char* const pFileName;  // ptr to the filename
	char text[maxInputBufferSize]; // input text buffer
	char* pChar; // pointer to the current char

	virtual char GetLine() = 0;
public:
	TextInBuffer(const char* pInputFileName, AbortCode ac);
	virtual ~TextInBuffer() {
		file.close();
		delete pFileName;
	}
	char Char() const {
		return *pChar;
	}
	char GetChar ();
	char PutBackChar();
};

//-----------------------------------------------------------------------------
// SourceBuffer  Source buffer subclass of TextInBuffer
//-----------------------------------------------------------------------------

class SourceBuffer : public TextInBuffer {
	virtual char GetLine();
public:
	SourceBuffer(const char* pSourceFileName);
};

//-----------------------------------------------------------------------------
//                          **************************
//                          *
//                          *
//                          *         OUTPUT
//                          *
//                          *
//                          **************************
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// TextOutBuffer  Abstract text output buffer class
//-----------------------------------------------------------------------------

class TextOutBuffer {
public:
	char text[maxInputBufferSize + 16]; // Output text buffer
	virtual void PutLine() = 0;
	void PutLine(const char* pText) {
		strcpy(text, pText);
		//PutLine();
	}
};

//-----------------------------------------------------------------------------
// ListBuffer  List buffer subclass of TextOutBuffer
//-----------------------------------------------------------------------------

class ListBuffer : public TextOutBuffer {
	char* pSourceFileName; // pointer to source file (for page header)
	char date[26]; // date string for page header
	int pageNumber; // current page number
	int lineCount; // count of lines in the current page

	void PrintPageHeader();
public:
	virtual ~ListBuffer() {
		delete pSourceFileName;
	}
	void Initialize(const char* fileName);
	virtual void PutLine();
	void PutLine(const char* pText) {
		TextOutBuffer::PutLine(pText);
	}


	void PutLine(const char* pText, int lineNumber, int nestingLevel) {
		sprintf(text, "%4d %d: %s", lineNumber, nestingLevel, pText);
		PutLine();
	}
};

extern ListBuffer list;

#endif
