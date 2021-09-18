#include <string.h>
#include <stdio.h>
#include <token.h>

const int minResWordLen = 2;
const int maxResWordLen = 9;

struct TResWord {
	char *pString;
	TTokenCode code;
};

static TResWord rw2[] = {
	{"do", tcDO}, {"if", tcIF}, {"in", tcIN}, {"of", tcOF},
	{"or", tcOR}, {"to", tcTO}, {NULL},
};

static TResWord rw3[] = {
	{"and", tcAND}, {"div", tcDIV}, {"end", tcEND}, {"for", tcFOR},
	{"mod", tcMOD}, {"nil", tcNIL}, {"not", tcNOT}, {"set", tcSET},
	{"var", tcVAR}, {NULL},
};

static TResWord rw4[] = {
	{"case", tcCASE}, {"els", tcELSE}, {"file", tcFILE},
	{"goto", tcGOTO}, {"then", tcTHEN}, {"type", tcTYPE},
	{"with", tcWITH}, {NULL},
};

static TResWord rw5[] = {
	{"array", tcARRAY}, {"begin", tcBEGIN}, {"const", tcCONST},
	{"label", tcLABEL}, {"until", tcUNTIL}, {"while", tcWHILE},
	{NULL},
};

static TResWord rw6[] = {
	{"downto", tcDOWNTO}, {"packed", tcPACKED}, {"record", tcRECORD},
	{"repeat", tcREPEAT}, {NULL},
};

static TResWord rw7[] = {
	{"program", tcPROGRAM}, {NULL},
};

static TResWord rw8[] = {
	{"function", tcFUNCTION}, {NULL},
};

static TResWord rw9[] = {
	{"procedure", tcPROCEDURE}, {NULL},
};
