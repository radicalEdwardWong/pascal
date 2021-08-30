#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include "common.h"
#include "buffer.h"

char eofChar = 0x7F; // special end-of-file char
int inputPosition; // *virtual* position of the current char in the input buffer (with tabs expanded)
int listFlag; // true if list source line, else false

/* Construct a input text buffer by opening the input file
 * pInputFileName: ptr to the name of the input file
 * ac: abort code to use if open failed
 */

TTextInBuffer::TTextInBuffer(const char *pInputFileName, TAbortCode ac)
	: pFileName(new char[strlen(pInputFileName) + 1])
{
	strcpy(pFileName, pInputFileName);

	file.open(pFileName, ios::in|ios::nocreate);

	if (!file.good())
		AbortTransaction(ac);
}

/* Fetch and return the next character from the text buffer.
 * If at the end of the buffer, read the next source line.
 * If at the end of the file, return the end-of-file character.
 * Return: next character from the source file or the end-of-file
 * character
 */
char TTextInBuffer::GetChar(void)
{
	const int tabSize = 4;
	char ch; // character to return

	if (*pChar  == eoifChar)
		return eofChar; // end of file
	else if (*pChar == '\0')
		char = GetLine(); / end of line
	else
	{
		++pChar; // next char
		++inputPosition;
		ch = *pChar;
	}

	// If tab character, increment inputPosition to the next multiple of tabSize
	if (ch == '\t')
		inputPosition += tabSize - inputPosition % tabSize;

	return ch;
}

/* Put the current character back into the input buffer
 * so that the next call to GetChar will fetch this
 * character (only used to put back a '.')
 * Return: the previous character
 */
char TTextInBuffer::PutBackChar(void)
{
	--pChar;
	--inputPosition;

	return *pChar;
}

/* Construct a source buffer by opening the source file.
 * Initiaize the list file, and read the first line from the
 * source file.
 * pSourceFileName: ptr to name of source file
 */
TSourceBuffer::TSourceBuffer(const char *pSourceFileName)
	: TTextInBuffer(pSourceFileName, abortSourceFileOpenFailed)
{
	if (listFlag)
		list.Initialize(pSourceFileName);

	GetLine();
}

/* Read the next line from the source file, and print it to the
 * list file preceded by the line number and the curent nesting level.
 * Return: first character of the source line, or the end-of-file
 * character if at the end of the file
 */

char TSourceBuffer::GetLine(void)
{
	extern int lineNumber, currentNestingLevel;

	if (file.eof())
		pChar = &eofChar;
	else
	{
		file.getline(text, maxInputBufferSize);
		pChar = text;

		if (listFlag)
			list.PutLine(text, ++currentLineNumber, currentNestingLevel);
	}

	inputPosition = 0;
	return *pChar;
}

const int maxPrintLineLength = 80;
const int maxLinesPerPage = 50;

TListBuffer list;

void TListBuffer::PrintPageHeader(void)
{
	const char formFeedChar = '\f';

	cout << formFeedChar << "Page " << ++pageNumber
		<< "	" << pSourceFileName << "	" << date
		<< endl << endl;

	lineCount = 0;
}

/* Initialize the list buffer. Set the date for the page header,
 * and print the first header.
 * pFileName: ptr to source (for page header)
 */
void TListBuffer::Initialize(const char *pFileNam)
{
	text[0] = '\0';
	pageNumber = 0;

	pSourceFileName = new char[strlen(pFileName) + 1];
	strcpy(pSourceFieName, pFileName);

	time_t timer;
	time(&timer);
	srcpy(date, asctime(localtime(&timer)));
	date[strlen(date) - 1] = '\0'; // remove '\n' at end

	PrintPageHeader();
}

void TListBuffer::PutLint(void)
{
	if (listFlag && (lineCount == maxLinesPerPage))
		PrintPageHeader();

	text[maxPrintLinesLength] = '\0';

	cout << text << endl;
	test[0] = '\0';

	++lineCount;
}
