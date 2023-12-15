#include "Tokenize.h"

#pragma warning (disable:4996)

Tokenize::Tokenize() {}

void Tokenize::LineToTok(char* line) {
	char* token = strtok(line, " ,\n\t");
	while (token != NULL) {
		token_table.push_back(token);
		token = strtok(NULL, " ,\n\t");
	}
}

char* Tokenize::PeekToken(int index) const {
	return token_table[index];
}

signed int Tokenize::GetInstructionCode() {
	toUpper(token_table.front());
	
	if (!strcmp(token_table.front(), "PRINT")) {
		return 1;
	}
	else if (!strcmp(token_table.front(), "PRINTLN")) {
		return 2;
	}
	else if (!strcmp(token_table.front(), "IF")) {
		return 3;
	}
	else if (!strcmp(token_table.front(), "WHILE")) {
		return 4;
	}
	else if (!strcmp(token_table.front(), "END")) {
		return 5;
	}
	else if(!strcmp(token_table.front(), "VAR")) { // it could be error but also could be variable declaration
		return 0;
	}
	else {
		return -1;
	}
}

size_t Tokenize::TokenLen() const {
	return token_table.size();
}

void Tokenize::IsVarOperator(const char* token) {
	if (TokenOperatorCheck(token)) {
		throw (-1);
	}
}

void Tokenize::Release() {
	token_table.clear();
}

Tokenize::~Tokenize() {
	token_table.~vector();
}