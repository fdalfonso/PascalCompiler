//  ***************************************************************************
//  *
//  *   DESCRIPTION:
//  *
//  *   FILE:   error.h
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
#ifndef ERROR_H
#define ERROR_H

extern int errorCount;

//-----------------------------------------------------------------------------
//  Abort codes for fata translation errors 
//-----------------------------------------------------------------------------

enum AbortCode {
	abortInvalidCommandLineArgs = -1,
	abortSourceFileOpenFailed = -2,
	abortIFormFileOpenFailed = -3,
	abortAssemblyFileOpenFailes = -4,
	abortTooManySyntaxErrors = -5,
	abortStackOverflow = -6,
	abortCodeSegmentOverflow = -7,
	abortNestingTooDeep = -8,
	abortRunTimeError = -9,
	abortUnimplementedFeature = -10,
};

void AbortTranslation(AbortCode ac);

#endif // ERROR_H
