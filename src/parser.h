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
		TCompactListBuffer *const pCompact;
	
		void GetToken(void)
		{
			pToken = pScanner->Get();
			token = pToken->Code();
		}

	public:
		TParser(TTextInBuffer *pBuffer)
			: pScanner(new TTextScanner(pBuffer)),
			pCompact(new TCompactListBuffer) {}

		~TParser(void)
		{
			delete pScanner;
			delete pCompact;
		}
};

#endif
