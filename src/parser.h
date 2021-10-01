#ifndef parser_h
#define parser_h

#include "misc.h"
#include "token.h"
#include "scanner.h"

class Parser {
	private:
		TextScanner *const pScanner;
		Token *pToken;
		TokenCode token;
		TCompactListBuffer *const pCompact;
	
		void GetToken(void)
		{
			pToken = pScanner->Get();
			token = pToken->Code();
		}

	public:
		Parser(TextInBuffer *pBuffer)
			: pScanner(new TextScanner(pBuffer)),
			pCompact(new TCompactListBuffer) {}

		~Parser(void)
		{
			delete pScanner;
			delete pCompact;
		}
};

#endif
