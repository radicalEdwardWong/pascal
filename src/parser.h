#ifndef parser_h
#define parser_h

#include "misc.h"
#include "token.h"
#include "scanner.h"
#include "complist.h"

class Parser {
	private:
		TextScanner *const pScanner;
		Token *pToken;
		TokenCode token;
		CompactListBuffer *const pCompact;
	
		void GetToken(void)
		{
			pToken = pScanner->Get();
			token = pToken->Code();
		}

	public:
		Parser(TextInBuffer *pBuffer)
			: pScanner(new TextScanner(pBuffer)),
			pCompact(new CompactListBuffer) {}

		~Parser(void)
		{
			delete pScanner;
			delete pCompact;
		}

		void Parse(void);
};

#endif
