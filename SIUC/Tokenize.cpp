#include "Tokenize.h"

#pragma warning (disable:4996)

Tokenize::Tokenize() {}

void Tokenize::LineToTok(char* line) {
	char* token = strtok(line, " ");
	while (token != NULL) {
		toUpper(token);
		token_table.push_back(token);
		token = strtok(NULL, " ");
	}
}

char* Tokenize::PeekToken(int index) const {
	return token_table[index];
}

unsigned int Tokenize::GetInstructionCode() {
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
	else { // it could be error but also could be variable declaration
		return 0;
	}
}

signed int Tokenize::TokenLen() const {
	return token_table.size();
}

void Tokenize::Release() {
	for (auto& tok : token_table) {
		delete[] tok;
	}
}

Tokenize::~Tokenize() {
	token_table.~vector();
}