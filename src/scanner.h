#ifndef scanner_h
#define scanner_h

#include "misc.h"
#include "buffer.h"
#include "token.h"

class TScanner {
	protected:
		TWordToken wordToken;
		TNumberToken numberToken;
		TStringToken stringToken;
		TSpecialToken specialToken;
		TEOFToken eofToken;
		TErrorToken erroToken;
	public:
		virtual ~TScanner(void) {}
		virtual TToken *Get(void) = 0;
};

class TTextScanner : public TScanner {
	protected:
		TWordToken wordToken;
		TNumberToken numberToken;
		TStringToken stringToken;
		TSpecialToken specialToken;
		TEOFToken eofToken;
		TErrorToken errorToken;
	public:
		virtual ~TScanner(void) {}
		virtual TToken *Get(void) = 0;
};

class TTextScanner : public TScanner {
	TTextInBuffer *const pTextInBuffer; // ptr to input text buffer to scan
};

#endif
