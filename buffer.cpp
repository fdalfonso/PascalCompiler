//  ***************************************************************************
//  *
//  *   DESCRIPTION:
//  *
//  *   FILE:   buffer.cpp
//  *
//  *   MODULE: Buffer
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
#include<cstdio>
#include<cstring>
#include<iostream>
#include<ctime>
#include "common.h"
#include "buffer.h"


//-----------------------------------------------------------------------------
//                          **************************
//                          *
//                          *
//                          *  Text Input Buffer
//                          *
//                          *
//                          **************************
//-----------------------------------------------------------------------------

char eofChar = 0x7F; // Special end of file character
int inputPosition; // "virtual" position of the current char
// in the input buffer (with tabs expanded)
int listFlag = true; // true if list source lines, else false

//-----------------------------------------------------------------------------
// Constructor: construct an imput text buffer by opening the input file
//-----------------------------------------------------------------------------

TextInBuffer::TextInBuffer(const char* pInputFileName, AbortCode ac)
	: pFileName(new char[strlen(pInputFileName) +  1]) {

	// -- Copy the input file name
	strcpy(pFileName, pInputFileName);

	// Open the input file. Abort if failed.
	file.open(pFileName);

	if(!file.good()) AbortTranslation(ac);
}

//-----------------------------------------------------------------------------
// GetChar: Fetch and return the next character form the text buffer.
// If at the and of the buffer, read the next source line. If at the end of
// the file returns the end-of-file character.
//-----------------------------------------------------------------------------

char TextInBuffer::GetChar() {
	const int tabSize = 8;
	char ch;

	if(*pChar == eofChar) return eofChar; // end of file
	else if (*pChar == '\0') ch = GetLine(); // end of line
	else {
		++pChar;
		++inputPosition;
	}

	if (ch == '\t') inputPosition += tabSize - inputPosition % tabSize;

	return ch;
}

//-----------------------------------------------------------------------------
// PutBackChar: Put the current character back into the input buffer so that
// the next call to GetChar will fetch this character. (only called to put
// back a '.')
//-----------------------------------------------------------------------------

char TextInBuffer::PutBackChar() {
	--pChar;
	--inputPosition;

	return *pChar;
}

//-----------------------------------------------------------------------------
//                          **************************
//                          *
//                          *
//                          *     Source Buffer 
//                          *
//                          *
//                          **************************
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Constructor: Construct a source buffer by opening the source file
//-----------------------------------------------------------------------------

SourceBuffer::SourceBuffer(const char* pSourceFileName)
	: TextInBuffer(pSourceFileName, abortSourceFileOpenFailed) {

	if(listFlag) list.Initialize(pSourceFileName);

	GetLine();
}

//-----------------------------------------------------------------------------
// GetLine Read the next line from the source file, and print it
// to the list file preceded by line number and the current nesting
// level
//-----------------------------------------------------------------------------

char SourceBuffer::GetLine() {
	extern int lineNumber, currentNestingLevel;

	if(file.eof()) pChar = &eofChar;

	else {
		file.getline(text, maxInputBufferSize);
		pChar = text;

		if (listFlag)
			list.PutLine(text, ++currentLineNumber, currentNestingLevel);
	}

	inputPosition = 0;
	return *pChar;
}

//-----------------------------------------------------------------------------
//                          **************************
//                          *
//                          *
//                          *       List Buffer
//                          *
//                          *
//                          **************************
//-----------------------------------------------------------------------------

const int maxPrintLineLenght = 80;
const int maxLinesPerPage = 50;

ListBuffer list; // the list file buffer

//-----------------------------------------------------------------------------
// PrintPageHeader: Start  a new page of thi list file and print
// the page header
//-----------------------------------------------------------------------------

void ListBuffer::PrintPageHeader() {
	const char formFeedChar = '\f';

	cout << formFeedChar << "Page " << ++pageNumber
	     << "  " << pSourceFileName << "  " <<  date  << endl << endl;

	lineCount = 0;
}

//-----------------------------------------------------------------------------
//  Initialize
//-----------------------------------------------------------------------------

void ListBuffer::Initialize(const char* pFileName) {
	text[0] = '\0';
	pageNumber = 0;

	// -- Copy the input file name.
	pSourceFileName = new char[strlen(pFileName) + 1];
	strcpy(pSourceFileName, pFileName);

	// -- Set the date.
	time_t timer;
	time(&timer);
	strcpy(date, asctime(localtime(&timer)));
	date[strlen(date) - 1] = '\0'; // remove '\n' at end

	PrintPageHeader();
}

//-----------------------------------------------------------------------------
// PutLine
//-----------------------------------------------------------------------------

void ListBuffer::PutLine() {
	//-- Start a new page if the current one is full.
	if(listFlag && (lineCount == maxLinesPerPage)) PrintPageHeader();

	//-- Truncate the line if it's too long.
	text[maxPrintLineLenght] = '\0';

	//-- Print the text line, and than blank out the text.
	cout << text << endl;
	text[0] = '\0';

	++lineCount;
}
