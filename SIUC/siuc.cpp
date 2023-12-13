#include "siuc.h"

VarResources ctr_resources;
Tokenize ctr_tokens;

char tempLineBuffer[TEMP_BUF];
char tempPrintBuffer[TEMP_BUF];

void RecvTokens(const char* fn) {
	FILE* file;
	fopen_s(&file, fn, "r");
	while (!feof(file)) {
		fgets(tempLineBuffer, sizeof(char) * TEMP_BUF, file);
		ctr_tokens.LineToTok(tempLineBuffer);
		InstructionProcess();
	
	}
}

void InstructionProcess() {
	switch (ctr_tokens.GetInstructionCode()) {
	case PRINT:
		fputs(TokenCat(), stdout);
		break;
	case PRINTLN:

		break;
	case IF:
		break;
	case WHILE:
		break;
	case END:
		break;
	case VAR: // could be variable declaration
		// variale validation
		// variable cannot start with number
		
		if (ctr_resources.VariableValidation(ctr_tokens.PeekToken(1)) && (TokenOperatorCheck(ctr_tokens.PeekToken(2)) == 0)) {
			if (ctr_resources.VarSearchByName(ctr_tokens.PeekToken(1)) == -1) {
				ctr_resources.VarInit(ctr_tokens.PeekToken(1), ctr_tokens.PeekToken(3));
			}
			else {
				fputs("Variable already exists", stderr);
				exit(-1);
			}
		}
		else {
			fputs("Invalid variable name", stderr);
			exit(-1);
		}
		
		break;
	}

}


const char* TokenCat() {
	char strBuffer[TEMP_BUF];
	memset(strBuffer, 0, sizeof(char) * TEMP_BUF);

	// first token
	if (ctr_resources.VarSearchByName(ctr_tokens.PeekToken(1)) < 0) {
		sprintf_s(strBuffer, "%s", ctr_tokens.PeekToken(1));
	}
	else {
		sprintf_s(strBuffer, "%s", ctr_resources.VarGetDataByName(ctr_tokens.PeekToken(1)));
	}

	// else
	if (ctr_tokens.TokenLen() > 3) {
		for (int i = 2; i < ctr_tokens.TokenLen(); i++) {
			sprintf_s(strBuffer, "%s %s", strBuffer, ctr_resources.VarGetDataByName(ctr_tokens.PeekToken(i)));
		}
	}
	else if (ctr_tokens.TokenLen() == 3) {
		sprintf_s(strBuffer, "%s %s", strBuffer, ctr_resources.VarGetDataByName(ctr_tokens.PeekToken(2)));
	}
	return strBuffer;
}
