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
	tcDummy, tcWord, tcNumber, tcPeriod, tcEndOfFile, tcError,
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
