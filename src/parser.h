#ifndef parser_h
#define parser_h

#include "misc.h"
#include "token.h"
#include "scanner.h"

class TParser {
	private:
		TTextScanner *const pScanner;
		TToken *pToken;
		TTokenCode token;
	
		void GetToken(void)
		{
			pToken = pScanner->Get();
			token = pToken->Code();
		}
	public:
		TParser(TTextInBuffer *pBuffer)
			: pScanner(new TTextScanner(pBuffer)) {}

		~TParser(void) { delete pScanner; }

		void Parse(void);
};


#endif
