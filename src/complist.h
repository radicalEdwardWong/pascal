#ifndef complist_h
#define complist_h

#include "buffer.h"

const int maxCompactTextLength = 72;

class CompactListBuffer : public TextOutBuffer {
	private:
		int textLength;
		char *pText; // points to current position in text buffer

	public:
		CompactListBuffer(void)
		{
			pText = text;
			*pText = '\0';
			textLength = 0;
		}

		void PutBlank(void);
		void Put(const char *pString);
		void PutLine(void);
};

#endif
