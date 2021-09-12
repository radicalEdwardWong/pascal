#ifndef scanner_h
#define scanner_h

#include "misc.h"
#include "token.h"

class TScanner {
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
	private:
		TTextInBuffer *const pTextInBuffer; // ptr to input text buffer to scan
		void SkipWhiteSpace(void);
	public:
		TTextScanner(TTextInBuffer *pBuffer);
		virtual ~TTextScanner(void) { delete pTextInBuffer; }
		virtual TToken *Get(void);
};

#endif
