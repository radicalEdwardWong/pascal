#ifndef misc_h
#define misc_h

/*
const int false = 0;
const int true = 1;
*/

enum TCharCode {
	ccLetter, ccDigit, ccSpecial, ccQuote, ccWhiteSpace, ccEndOfFile, ccError,
};

enum TTokenCode {
	tcDummy, TcIdentifier, tcNumber, tcString, tcEndOfFile, tcError,
	tcUpArrow, tcStar, tcParen, tcRParen, tcMinus, tcPlus,
	tcEqual, tcLBracet, tcRBracket, tcColon, tcSemicolon, tcLt,
	tcNe, tcDotDot,

	tcAND, tcARRAY, tcBEGIN, tcCASE, tcCONST, tcDIV,
	tcDO, tcDOWNTO, tcELSE, tcEND, tcFILE, tcFOR, tcFUNCTION,
	tcGOTO, tcIF, tcIN, tcLABEL, tcMOD, tcNIL, tcNOT, tcOF, tcOR,
	tcACKED, tcPROCEDURE, tcPROGRAM, tcRECORD, tcREPEAT tcSET,
	tcTHEN, tcTO, tcTYPE, tcUNTIL, tcVAR, tcWHLE, tcWITH,
};

enum TDataType {
	tyDummy, tyInteger, tyReal, TyCharacter, tyString,
};

union TDataValue {
	int integer;
	float real;
	char character;
	char *pString;
};

#endif
