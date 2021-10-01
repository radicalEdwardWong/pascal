#ifndef misc_h
#define misc_h

/*
const int false = 0;
const int true = 1;
*/

enum CharCode {
	ccLetter, ccDigit, ccSpecial, ccQuote, ccWhiteSpace, ccEndOfFile, ccError,
};

enum TokenCode {
	tcDummy, tcIdentifier, tcNumber, tcString, tcEndOfFile, tcError,
	tcUpArrow, tcStar, tcParen, tcRParen, tcMinus, tcPlus,
	tcEqual, tcLBracet, tcRBracket, tcColon, tcSemicolon, tcLt,
	tcGt, tcComma, tcPeriod, tcSlash, tcColonEqual, tcLe, tcGe,
	tcNe, tcDotDot,

	tcAND, tcARRAY, tcBEGIN, tcCASE, tcCONST, tcDIV,
	tcDO, tcDOWNTO, tcELSE, tcEND, tcFILE, tcFOR, tcFUNCTION,
	tcGOTO, tcIF, tcIN, tcLABEL, tcMOD, tcNIL, tcNOT, tcOF, tcOR,
	tcPACKED, tcPROCEDURE, tcPROGRAM, tcRECORD, tcREPEAT, tcSET,
	tcTHEN, tcTO, tcTYPE, tcUNTIL, tcVAR, tcWHILE, tcWITH,
};

enum DataType {
	tyDummy, tyInteger, tyReal, tyCharacter, tyString,
};

union DataValue {
	int integer;
	float real;
	char character;
	char *pString;
};

#endif
