#ifndef symtab_h
#define symtab_h

#include <string>
#include "misc.h"

extern int xrefFlag;
extern int currentLineNumber;

class LineNumList;

class SymtabNode {
	private:
		SymtabNode  *left, *right;
		char *pString; // symbol string
		short xSymtab; // symbol table index
		short xNode; // node index
		LineNumList *pLineNumList; // list of line numbers
	
		friend class Symtab;

	public:

	float value;
	SymtabNode(const char *pStr);
	~SymtabNode(void);

	SymtabNode *LeftSubtree (void) const { return left; }
	SymtabNode *RightSubtree (void) const { return right; }
	char *String (void) const { return pString; }
	short NodeIndex (void) const { return xNode; }

	void Print(void) const;
};

class Symtab {
	private:
		SymtabNode *root; // binary tree root
		short cntNodes; // node counter
		short xSymtab; // symbol table index

	public:
		Symtab()
		{
			root = NULL;
			cntNodes = 0;
			xSymtab = 0;
		}

		~Symtab() { delete root; }

		SymtabNode *Search (const char *pString) const;
		SymtabNode *Enter (const char *pString);
		SymtabNode *Root (void) const { return root; }
		int NodeCount(void) const { return cntNodes; }
		void Print (void) const { root->Print(); }
};

class LineNumNode {
	private:
		LineNumNode *next; // prt to next node
		const int number; // line number
		friend class LineNumList;

	public:
		LineNumNode(void) : number(currentLineNumber) { next = NULL; }
};

class LineNumList {
	private:
		LineNumNode *head, *tail;

	public:
		LineNumList(void) { head = tail = new LineNumNode; }
		virtual ~LineNumList(void);
		void Update(void);
		void Print(int newLineFlag, int ident) const;
};

#endif
