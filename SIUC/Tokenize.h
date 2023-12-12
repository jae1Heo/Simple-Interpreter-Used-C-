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
	unsigned int GetInstructionCode();
	void Release();

	~Tokenize();
};