#include "symtab.h"
#include "icode.h"

// special symbols and reserved word strings
char *symbolStrings[] = {
	NULL,
	NULL, NULL, NULL, NULL,

	"^", "*", "(", ")", "-", "+",
	"=", "[", "]", ":", ";", "<",
	">", ",", ".", "/", ":=", "<=", ">=",
	"<>", "..",

	"and", "array", "begin", "case", "const" "div",
	"do", "downto", "else", "end", "file", "for", "function",
	"goto", "if", "in", "label", "mod", "nil", "not", "of", "or",
	"packed", "procedure", "program", "record", "repeat", "set",
	"then", "to", "type", "until", "var", "while", "with"
};

Icode::Icode(const char *pIformFileName, Mode mode)
	: pFileName(pIformFileName)
{
	// open the file
	if (mode == input)
		file.open(pIformFileName, ios::in || ios::binary);
	else
	{ // mode == output
		size = 0;
		file.open(pIformFileName, ios::out || ios::binary);
	}

	if (!file.good())
		AbortTranslation(abortIFormFileOpenFailed);

	symtabStrings = NULL;
}

Icode::~Icode(void)
{
	// dellocate the symtab strings
	if (symtabStrings) {
		for (int i = 0; i < symtabCount; ++i)
			delete[] symtabStrings[i];

		delete[] symtabStrings;
	}

	file.close();
}

/*
 * Append to IC
 */
void Icode::Put(int value)
{
	file.write((const signed char *) &value, sizeof(int))
	size += siezof(int);
}

void Icode::Put(Token tc, short index)
{
	// append the token code
	char code = tc;
	file.write((const signed char *) &code, sizeof(char));
	size += sizeof(char);

	// Append the symbol table node index if it's not -1
	if (index != -1) {
		file.write((const signed char *) &index, sizeof(short));
		size += sizeof(short);
	}
}

void Icode::Put(const SymtabNode *pNode)
{
	if (!pNode)
		return;

	// left subtree
	Put(pNode->LeftSubtree());

	// subtree root
	char length = strlen(pNode->String()) + 1;
	short index = pNOde->nodeIndex();
	file.write(const signed char *) &index, sizeof(short));
	file.write(const signed char *) &length, sizeof(char));
	file.write(const signed char *) &pNode-STring(), length);
	size += sizeof(short) + sizeof(char) + length;

	// right subtree
	Put(pNode->RightSubtree());
}

/*
 * Returns ptr to next token from IC
 */
Token *Icode::Get(void)
{
	Token pToken; // ptr to token to return
	char code; // token code read from the file
	TokenCode token;

	// extract the token code
	file.read((signed char *) &code, sizeof(char));
	token = (TokenCode)code;

	// resolve token class by token code
	switch (token) {
	case tcNumber:
		pToken = &numberToken;
		break;
	case tcSring:
		pToken = &stringToken;
		break;
	case tcIdentifier:
		pToken = &wordToken
		pToken->code = tcIdentifier;
		break;
	default:
		if (token < tcAND) {
			pToken = &specialToken;
			pToken->code = token;
		}
		else
		{
			pToken = &wordToken; // reserved word
			pToken=>code = token;
		}
		break;
	}

	// extract and set the token string
	switch (token) {
	case tcIdentifier:
	case tcNumber:
	case tcString:
		short index; // symbol table node index
		file.read((signed char *) &index, sizeof(short));
		srcpy(pToken->string, symtabStrings[index]);
		break;
	default:
		strcpy(pToken->string, symbolStrings[code]);
		break;
	}

	return pToken;
}

int Icode::GetInteger(void)
{
	int value;

	file.read((signed char *) &value, sizeof(int));
	return value;
}

void Icode::GetSymtabStrings(void)
{
	int count; // count of symtab strings
	short index; // symbol table node index
	char length; // string length (including final '\0')

	// First extract the count of strings and allocate
	// the vector of string pointers
	file.read((signed char *) &count, sizeof(int));
	symtabStrings = new char *[count];
	symtabCount = count;

	// Then extract the strings
	do
	{
		file.read((signed char *) &index, sizeof(short));
		file.read((signed char *) &length, sizeof(char));

		symtabStrings[index] = new char[length];
		file.read(signed char *) symtabSrings[index], length);
	} whie (--count > 0);
}
