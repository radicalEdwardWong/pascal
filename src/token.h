#ifndef token_h
#define token_h

#include "misc.h"
#include "error.h"
#include "buffer.h"
#include "str.h"

extern CharCode charCodeMap[];

class Token {
	protected:
		TokenCode code;
		DataType type;
		DataValue value;
		char string[maxInputBufferSize];
	public:
		Token(void)
		{
			code = tcDummy;
			type = tyDummy;
			value.integer = 0;
			string[0] = '\0';
		}

		TokenCode Code() const { return code; }
		DataType Type() const { return type; }
		DataValue Value() const { return value; }
		char *String() { return string; }

		virtual void Get(TextInBuffer &buffer) = 0;
		virtual int IsDelimiter(void) const = 0;
		virtual void Print(void) const = 0;
};

class WordToken : public Token {
	private:
		void CheckForReservedWord(void);
	public:
		virtual void Get(TextInBuffer &buffer);
		virtual int IsDelimiter(void) const { return false; }
		virtual void Print(void) const;
};

class NumberToken : public Token {
	private:
		char ch;
		char *ps;
		int digitCount;
		int countErrorFlag;
		int AccumulateValue(TextInBuffer &buffer, float &value, ErrorCode ec);
	public:
		NumberToken(void) { code = tcNumber; }
		virtual void Get(TextInBuffer &buffer);
		virtual int IsDelimiter(void) const { return false; }
		virtual void Print(void) const;
};

class StringToken : public Token {
	public:
		StringToken() { code = tcString; }
		virtual void Get(TextInBuffer &buffer);
		virtual int IsDelimiter(void) const { return true; }
		virtual void Print(void) const;
};

class SpecialToken : public Token {
	public:
		virtual void Get(TextInBuffer &buffer);
		virtual int IsDelimiter(void) const { return true; }
		virtual void Print(void) const;
};

class EOFToken : public Token {
	public:
		EOFToken(void) { code = tcEndOfFile; }
		virtual void Get(TextInBuffer &buffer) {}
		virtual int IsDelimiter(void) const { return false; }
		virtual void Print(void) const {}
};

class ErrorToken : public Token {
	public:
		ErrorToken(void) { code = tcError; }
		virtual void Get(TextInBuffer &buffer);
		virtual int IsDelimiter(void) const { return false; }
		virtual void Print(void) const {}
};

#endif
