#include <string.h>
#include <stdio.h>
#include <math.h>
#include "token.h"

void TNumberToken::Get(TTextInBuffer *buffer)
{
	const int maxInteger = 32767;
	const int maxExponent = 37;

	float numValue = 0.0; // value ignoring the decimal point
	int wholePlaces = 0; // digits before the decimal point
	char exponentSign = '+';
	float eValue = 0.0; // value of number after 'E'
	int exponent = 0; // final value of exponent
	int sawDotDotFalag = false; // true of encountered '..', else false

	ch = buffer.Char();
	ps = string;
	digitCount = 0;
	countErrorFlag = false;
	code = tcError;
	type = tyInteger;

	// Get the whole part of the number by accumulating
	// the values of its digits into numValue. wholePlaces keeps
	// track of the number of digits in this part
	if (! AccumulateValue(buffer, numValue, errInvalidNumber))
		return;
	wholePlaces = digitCount;

	// If the current character is a dot, then either we hve a
	// fraction part or we are seeing the first character of a '..'
	// token. To find out, we must fetch the next character.
	if (ch == '.') {
		ch = buffer.GetChar();

		if (ch == '.') {
			// we have a .. token. Backup up buffer so that the token can be extracted next.
			sawDotDotFlag = true;
			buffer.PutBackChar();
		}
		else
		{
			type = tyReal;
			*ps++ = '.';

			// we have a fraction part. Accumulate it into numValue;
			if (! AccumulateValue(buffer, numValue, errInvalidFraction))
				return;
			decimalPlaces = digitCount - wholePlaces;
		}
	}

	// Get the exponent part, if any. There cannot be an exponent
	// part if we already saw the '..' token.
	if (!sawDotDotFlag && ((ch == 'E') || (ch == 'e')) {
		type = tyReal;
		*ps++ = ch;
		ch = buffer.GetChar();

		// Fetch the exponent's sign, if any.
		if ((ch == '+') || (ch == '-')) {
			*ps++ = exponentSign = ch;
			ch = buffer.GetChar();
		}

		// Accumulate the value of the number after 'E' into eValue.
		digitCount = 0;
		if (! AccumulateValue(buffer, eValue, errInvalidExponent))
			return;

		if (exponentSign == '-')
			eValue = -eValue;
	}

	// Too many digits?
	if (countErrorFlag) {
		Error(errTooManyDigits);
		return;
	}

	// Calculate and check the final exponent value,
	// and then use it to adjust the number's value.
	exponent = int(eValue) - decimalPlaces;
	if ((exponent + wholePlaces < -maxExponent) ||
		(exponent + wholePlaces > maxExponent)) {
		Error(errRealOutOfRange);
		return
	}
	if (exponent != 0)
		numValue *= float(pow(10, exponent));

	// Check and set the numeric value.
	if (type == tyInteger) {
		if ((numValue < -maxInteger) || (numValue > maxInteger)) {
			Error(errIntegerOutOfRange);
			return;
		}
		value.integer = int(numValue);
	}
	else
		value.real = numValue;

	*ps = '\0';
	code = tcNumber;
}

int TNumberToken::AccumulateValue(TTextInBuffer &buffer,
								float &value, TerrorCode ec) {
	const int maxDigitCount = 20;

	// Error if the first character is not a digit
	if (charCodeMap[ch] != ccDigit) {
		Error(ec);
		return false; // failure (>_<)
	}

	// Accumulate the value as long as the total allowable
	// number of digits has not been exceeded
	do {
		*ps++ = ch;

		if (++digitCount <= maxDigitCount)
			value = 10*value + (ch - '0'); // shift left and add
		else
			countErrorFlag = true; // too many digits

		ch = buffer.GetChar();
	} while (charCodeMap[ch] == ccDigit);

	return true; // success (^.^)-b
}

void TNumberToken::Print(void) const
{
	if (type == tyInteger)
		sprintf(list.text, "\t%-18s =%d", ">> integer:", value.integer);
	else
		sprintf(list.text, "\t%-18s =%g", ">> real:", value.real);

	list.PutLine();
}
