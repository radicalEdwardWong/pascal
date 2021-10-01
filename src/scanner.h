#ifndef scanner_h
#define scanner_h

#include "misc.h"
#include "token.h"

class Scanner {
	protected:
		WordToken wordToken;
		NumberToken numberToken;
		StringToken stringToken;
		SpecialToken specialToken;
		EOFToken eofToken;
		ErrorToken errorToken;
	public:
		virtual ~Scanner(void) {}
		virtual Token *Get(void) = 0;
};

class TextScanner : public Scanner {
	private:
		TextInBuffer *const pTextInBuffer; // ptr to input text buffer to scan
		void SkipWhiteSpace(void);
	public:
		TextScanner(TextInBuffer *pBuffer);
		virtual ~TextScanner(void) { delete pTextInBuffer; }
		virtual Token *Get(void);
};

#endif
