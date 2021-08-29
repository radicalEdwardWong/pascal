#ifndef buffer_h
#define buffer

#include <fstream.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"
#include "error.h"

extern char eofChar;
extern int inputPosition;
extern int listFlag;
extern int level;

const int maxInputBufferSize = 256;

class TTextInBuffer
{
	protected:
		fstream file; // input text file
		char *const pFileName; // ptr to the file name
		char text[maxInputBufferSize]; // input text buffer
		char *pChar; // ptr to the current char in the text buffer

		virtual char GetLine(void) = 0;

	public:
		TTextInBuffer(const char *pInputFileName, TAbortCode ac);

		virtual ~TTextInBuffer(void)
		{
			file.close();
			delete pFileName;
		}

		char Char (void) const { return *pChar; }
		char GetChar (void);
		char PutBackChar(void);
};

class TSourceBuffer : public TTextInBuffer {
	private:
		virtual char GetLine(void);

	public:
		TSourceBuffer(const char *pSourceFileName);
};


class TTextOutBuffer {
	public:
		char text[maxInputBufferSize + 16]; // output text buffer

		virtual void PutLine(void) = 0;

		void PutLine(const char *pText)
		{
			strcpy(text, pText);
			PutLine();
		}
		
};

class TListBuffer : public TTextOutBuffer
{
	private:
		char *pSourceFileName; // ptr to source file name (for page header)
		char date[26]; // date string for page header
		int pageNumber; // current page number
		int lineCount; //count of lines in the current page

		void PrintPageHeader(void);

	public:
		virtual ~TListBuffer(void) { delete pSourceFile; }

		void Initialize(const char *fileName);
		virtual void PutLine(void);

		void PutLine(const char *pText)
		{
			TTextOutBuffer::PutLine(pText);
		}

		void PutLine(const char *pText, int lineNumber, int nestingLevel)
		{
			sprintf(text, "%4d %d: %s", lineNumber, nestingLevel, pText);
			PutLine();
		}
};

extern TListBuffer list;

#endif
