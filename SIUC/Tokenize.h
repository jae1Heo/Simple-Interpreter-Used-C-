#pragma once
#include "StandardDefs.h"


class Tokenize {
private:
	// token table
	vector<char*>token_table;
public:
	Tokenize();
	void LineToTok(char*);
	char* PeekToken(int index) const;
	size_t TokenLen() const;
	signed int GetInstructionCode();
	void IsVarOperator(const char*);
	void Release();

	~Tokenize();
};