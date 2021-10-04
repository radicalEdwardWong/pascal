#include <stdio.h>
#include <ctype.h>

void strlwr(char *string) {
	char *ch = string;
	do {
		*ch = (char)tolower((int)*ch);
	} while (*ch++ != '\0');
}
