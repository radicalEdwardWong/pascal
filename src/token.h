#ifndef token_h
#define token_h

#include "misc.h"
#include "error.h"
#include "buffer.h"

extern TCharCode charCodeMap[];

class TToken {
	protected:
		TTokenCode code;
		TDataType type;
		TDataValue value;
		char string[maxInputBufferSize];
	public:
		TToken(void)
		{
			code = tcDummy;
			type = tyDummy;
			value.integer = 0;
			string[0] = '\0';
		}

		TTokenCode Code() const { return code; }
		TDataType Type() const { return type; }
		TDataValue Value() const { return value; }
		char *String() { return string; }

		virtual void Get(TTextInBuffer &buffer) = 0;
		virtual int IsDelimiter(void) const = 0;
		virtual void Print(void) const = 0;
};

class TWordToken : public TToken {
	private:
		void CheckForReservedWord(void);
	public:
		virtual void Get(TTextInBuffer &buffer);
		virtual int IsDelimiter(void) const { return false; }
		virtual void Print(void) const;
};

class TNumberToken : public TToken {
	private:
		char ch;
		char *ps;
		int digitCount;
		int countErrorFlag;
		int AccumulateValue(TTextInBuffer &buffer, float &value, TErrorCode ec);
	public:
		TNumberToken(void) { code = tcNumber; }
		virtual void Get(TTextInBuffer &buffer);
		virtual int IsDelimiter(void) const { return false; }
		virtual void Print(void) const;
};

class TStringToken : public TToken {
	public:
		TStringToken() { code = tcString; }
		virtual void Get(TTextInBuffer &buffer);
		virtual int IsDelimiter(void) const { return true; }
		virtual void Print(void) const;
};

class TSpecialToken : public TToken {
	public:
		virtual void Get(TTextInBuffer &buffer);
		virtual int IsDelimiter(void) const { return true; }
		virtual void Print(void) const;
};

class TEOFToken : public TToken {
	public:
		TEOFToken(void) { code = tcEndOfFile; }
		virtual void Get(TTextInBuffer &buffer) {}
		virtual int IsDelimiter(void) const { return false; }
		virtual void Print(void) const {}
};

class TErrorToken : public TToken {
	public:
		TErrorToken(void) { code = tcError; }
		virtual void Get(TTextInBuffer &buffer);
		virtual int IsDelimiter(void) const { return false; }
		virtual void Print(void) const {}
};

void strlwr(char *string);

#endif
