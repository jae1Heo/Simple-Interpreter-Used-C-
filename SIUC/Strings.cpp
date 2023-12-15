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

unsigned int TokenOperatorCheck(const char* op) {
	if (!strcmp(op, "=")) {
		return 0;
	}
	else if (!strcmp(op, "-")) {
		return 1;
	}
	else if (!strcmp(op, "+")) {
		return 2;
	}
	else { // error, for now
		return 3;
	}
}

void TokenOperatorCheck(const char ch) { // for variable
	if (ch == '=' || ch == '+' || ch == '-') {
		throw int(ch);
	}
}