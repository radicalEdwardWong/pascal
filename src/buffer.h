#ifndef buffer_h
#define buffer_h

#include <fstream>
#include <stdio.h>
#include <cstring>
#include "misc.h"
#include "error.h"

using namespace std;

extern char eofChar;
extern int inputPosition;
extern int listFlag;
extern int level;

const int maxInputBufferSize = 256;

class TextInBuffer
{
	protected:
		fstream file; // input text file
		char *const pFileName; // ptr to the file name
		char text[maxInputBufferSize]; // input text buffer
		char *pChar; // ptr to the current char in the text buffer

		virtual char GetLine(void) = 0;

	public:
		TextInBuffer(const char *pInputFileName, AbortCode ac);

		virtual ~TextInBuffer(void)
		{
			file.close();
			delete pFileName;
		}

		char Char (void) const { return *pChar; }
		char GetChar (void);
		char PutBackChar(void);
};

class SourceBuffer : public TextInBuffer {
	private:
		virtual char GetLine(void);

	public:
		SourceBuffer(const char *pSourceFileName);
};


class TextOutBuffer {
	public:
		char text[maxInputBufferSize + 16]; // output text buffer

		virtual void PutLine(void) = 0;

		void PutLine(const char *pText)
		{
			strcpy(text, pText);
			PutLine();
		}
		
};

class ListBuffer : public TextOutBuffer
{
	private:
		char *pSourceFileName; // ptr to source file name (for page header)
		char date[26]; // date string for page header
		int pageNumber; // current page number
		int lineCount; //count of lines in the current page

		void PrintPageHeader(void);

	public:
		virtual ~ListBuffer(void) { delete pSourceFileName; }

		void Initialize(const char *fileName);
		virtual void PutLine(void);

		void PutLine(const char *pText)
		{
			TextOutBuffer::PutLine(pText);
		}

		void PutLine(const char *pText, int lineNumber, int nestingLevel)
		{
			sprintf(text, "%4d %d: %s", lineNumber, nestingLevel, pText);
			PutLine();
		}
};

extern ListBuffer list;

#endif
