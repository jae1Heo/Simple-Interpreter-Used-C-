#include "Strings.h"

const char* Append(const char* lhs, const char* rhs) {
	char* temp = new char[strlen(lhs) + strlen(rhs) + 1];
	strcpy_s(temp, sizeof(char) * strlen(lhs) + 1, lhs);
	strcpy_s(temp + sizeof(char) * strlen(lhs), sizeof(char) * strlen(rhs) + 1, rhs);
	return temp;
}

void toUpper(char* rhs) {
	char* temp = rhs;
	while (*temp) {
		if (isalpha(*temp)) {
			*temp = toupper((unsigned char)*temp);
		}
		temp++;
	}
}