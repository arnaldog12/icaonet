
// Copyright (C) 2009 DEIS - University of Bologna (Italy)
// All rights reserved.
//
// FVC-onGoing sample source code.
// http://biolab.csr.unibo.it/fvcongoing
//
// This source code can be used by FVC participants to create FVC executables.
// It cannot be distributed and any other use is strictly prohibited.
//
// Warranties and Disclaimers:
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND
// INCLUDING, BUT NOT LIMITED TO, WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
// IN NO EVENT WILL UNIVERSITY OF BOLOGNA BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES,
// INCLUDING DAMAGES FOR LOSS OF PROFITS, LOSS OR INACCURACY OF DATA,
// INCURRED BY ANY PERSON FROM SUCH PERSON'S USAGE OF THIS SOFTWARE
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//

/* ---------------------------------------------------------------
            FVC-onGoing Win32 testing header file

            v 1.0 - March 2009

   --------------------------------------------------------------- */

#ifndef FVC_H
#define FVC_H

typedef enum ErrorCode
{
	SUCCESS = 0,
	SYNTAX_ERROR = 1,
	CANNOT_OPEN_OUTPUT_FILE = 2,
	CANNOT_OPEN_IMAGE_FILE = 3,
	IMAGE_LOAD_ERROR = 5,
	CANNOT_UPDATE_OUTPUT_FILE = 7,
	INIT_ERROR = 100,
	SETUP_ERROR = 101
}ErrorCode;

typedef enum RetVal
{
	IMAGE_CAN_BE_PROCESSED = 1,
	NO_MORE_INFO = 0,
	UNSUPPORTED_IMAGE_SIZE = -1,
	UNSUPPORTED_IMAGE_FORMAT = -2,
	UNUSEFUL_IMAGE_CONTENT = -3
}RetVal;

static RetVal errorCodeToRetVal(ErrorCode errorCode)
{
	switch (errorCode)
	{
	case SUCCESS:					return RetVal::IMAGE_CAN_BE_PROCESSED;
	case CANNOT_OPEN_IMAGE_FILE:	return RetVal::UNSUPPORTED_IMAGE_FORMAT;
	case IMAGE_LOAD_ERROR:			return RetVal::UNUSEFUL_IMAGE_CONTENT;
	default:						return RetVal::NO_MORE_INFO;
	}
}

#endif /* FVC_H */