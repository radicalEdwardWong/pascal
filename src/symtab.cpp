#include <stdio.h>
#include <iostream>
#include "buffer.h"
#include "symtab.h"

int xrefFlag = false; // true = cross-referencing on, false = off

SymtabNode::SymtabNode(const char *pStr)
{
	left = right = NULL;
	pLineNumList = NULL;
	value = 0.0;
	xNode = 0;

	// allocate and copy the symbol string
	pString = new char[strlen(pStr) + 1];
	strcpy(pString, pStr);

	// if cross-referencing, update the line number list
	if (xrefFlag)
		pLineNumList = new LineNumList;
}

SymtabNode::~SymtabNode(void)
{
	// clean subtrees
	delete left;
	delete right;

	// clean node components
	delete[] pString;
	delete pLineNumList;
}

void SymtabNode::Print(void) const
{
	const int maxNamePrintWidth = 16;

	// print left subtree
	if (left)
		left->Print();

	// Print the node; first the name, then the list of line numbers
	sprintf(list.text, "%*s", maxNamePrintWidth, pString);
	if (pLineNumList) {
		pLineNumList->Print(strlen(pString) > maxNamePrintWidth, maxNamePrintWidth);
	}
	else
		list.PutLine();

	// print right subtree
	if (right)
		right->Print();
}

SymtabNode *Symtab::Search(const char *pString) const
{
	SymtabNode *pNode = root;
	int comp;

	while (pNode) {
		comp = strcmp(pString, pNode->pString); // compare names

		if (comp == 0) break; // found

		// not yet found, search left/right subtrees
		pNode = comp < 0 ? pNode->left : pNode->right;
	}

	// if found and cross-referencing, update the line number list
	if (xrefFlag && (comp == 0))
		pNode->pLineNumList->Update();

	return pNode; // NULL if node not found
}

SymtabNode *Symtab::Enter(const char *pString)
{
	SymtabNode *pNode;
	SymtabNode **ppNode = &root; // ptr to ptr to node

	// search table for insertion point
	while ((pNode = *ppNode) != NULL) {
		int comp = strcmp(pString, pNode->pString);
		if (comp == 0)
			return pNode;

		ppNode = comp < 0 ? &(pNode->left) : &(pNode->right);
	}

	// create and insert a new node
	pNode = new SymtabNode(pString); // create new node
	pNode->xSymtab = xSymtab; // set its symtab index
	pNode->xNode = cntNodes++; // set its node indexes
	*ppNode = pNode; // insert it
	return pNode; // return ptr to it
}

LineNumList::~LineNumList(void)
{
	while (head) {
		LineNumNode *pNode = head; // ptr to node to delete
		head = head->next; // move down list
		delete pNode;
	}
}

void LineNumList::Update(void)
{
	// if the line number is there it will be at the tail
	if (tail && (tail->number == currentLineNumber))
		return;

	// append the new node
	tail->next = new LineNumNode;
	tail = tail->next;
}

/* newLineFlag: if true, start a new line immediately
 * indent: amount to indent subsequent lines
 */
void LineNumList::Print(int newLineFlag, int indent) const
{
	const int maxLineNumberPrintWidth = 4;
	const int maxLineNumbersPerLine = 10;

	int n; // count of numbers per line
	LineNumNode *pNode; // ptr to line number node
	char *plt = &list.text[strlen(list.text)]; // ptr to where in list text to append

	n = newLineFlag ? 0 : maxLineNumbersPerLine;

	// for each line number node in list
	for (pNode = head; pNode; pNode = pNode->next) {

		// start new line i current one is full
		if (n == 0) {
			list.PutLine();
			sprintf(list.text, "%*s", indent, " ");
			plt = &list.text[indent];
			n = maxLineNumbersPerLine;
		}

		// append the line number to the list text
		sprintf(plt, "%*d", maxLineNumberPrintWidth, pNode->number);
		plt += maxLineNumberPrintWidth;

		--n;
	}

	list.PutLine();
}
