#include "Strings.h"

const char* Append(const char* lhs, const char* rhs) {
	char* temp = new char[strlen(lhs) + strlen(rhs) + 1];
	strcpy_s(temp, sizeof(char) * strlen(lhs) + 1, lhs);
	strcpy_s(temp + sizeof(char) * strlen(lhs), sizeof(char) * strlen(rhs) + 1, rhs);
	return temp;
}

void toLower(char* rhs) {
	char* temp = rhs;
	while (*temp) {
		if (isalpha(*temp)) {
			*temp = tolower((unsigned char)*temp);
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
	else { // error, or variable?
		return 3;
	}
}

void TokenOperatorCheck(const char ch) { // helper function for variable declaration
	if (ch == '=' || ch == '+' || ch == '-') {
		throw int(ch);
	}
}

unsigned int TokenOperatorCheckComp(const char* op) {
	if (!strcmp(op, "==")) {
		return 0;
	}
	else if (!strcmp(op, "<")) {
		return 1;
	}
	else if (!strcmp(op, ">")) {
		return 2;
	}
	else {
		return 3; // error?
	}
}


