#ifndef icode_h
#define icode_h

#include <fstream.h>
#include "token.h"
#include "scanner.h"

class SymtabNode;

class Icode : public Scanner {
	fstream file; // intermediate code file
	const char *const pFileName; // ptr to the file name
	int size; // byte size of file

	char **symtabStrings; // vector of symbol table strings
	int symtabCount; // count of string in the vector

public:
	enum Mode {input, output};

	Icode(const char *pIcodeFileName, Mode mode);
	~Icode(void);

	void GoTo(int location) { file.seekg(location, ios::beg); }
	int Size(void) const { return size; }

	void Put(int value);
	void Put(TokenCode tc, short index = -1);
	vod Put(const SymtabNode *pNode);

	virtual Token *Get (void);
	int GetInteger(void);
	void GetSymtabStrings(void);
};
