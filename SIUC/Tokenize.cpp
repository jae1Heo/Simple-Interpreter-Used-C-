#include "Tokenize.h"

#pragma warning (disable:4996)

Tokenize::Tokenize() {}

void Tokenize::LineToTok(char* line) {
	char* token = strtok(const_cast<char*>(line), " ,\n\t");
	while (token != NULL) {
		token_table.push_back(token);
		token = strtok(NULL, " ,\n\t");
	}
}

char* Tokenize::PeekToken(int index) const {
	return token_table[index];
}

signed int Tokenize::GetInstructionCode() {
	toLower(token_table.front());
	
	if (!strcmp(token_table.front(), "print")) {
		return 1;
	}
	else if (!strcmp(token_table.front(), "println")) {
		return 2;
	}
	else if (!strcmp(token_table.front(), "if")) {
		return 3;
	}
	else if (!strcmp(token_table.front(), "while")) {
		return 4;
	}
	else if (!strcmp(token_table.front(), "end")) {
		return 5;
	}
	else if(!strcmp(token_table.front(), "var")) { // it could be error but also could be variable declaration
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

vector<char*> Tokenize::GetEntireTokens() const {
	return token_table;
}

void Tokenize::Release() {
	size_t tk_len = TokenLen();
	for (int i = 0; i < tk_len; i++) {
		token_table.pop_back();
	}
}

Tokenize::~Tokenize() {
	size_t tk_len = TokenLen();
	for (int i = 0; i < tk_len; i++) {
		token_table.pop_back();
	}
}