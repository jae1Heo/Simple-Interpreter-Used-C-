#include "siuc.h"

VarResources ctr_resources;
Tokenize ctr_tokens;
stack<Conditions*> if_vector;

int if_counter = 0;

char tempLineBuffer[TEMP_BUF];
char tempPrintBuffer[TEMP_BUF];

void RecvTokens(const char* fn) {
	FILE* file;
	fopen_s(&file, fn, "r");

	if (file == NULL) {
		fputs("Cannot open file", stderr);
		exit(-1);
	}

	while (!feof(file)) {
		memset(tempLineBuffer, 0, sizeof(char) * TEMP_BUF);
		fgets(tempLineBuffer, sizeof(char) * TEMP_BUF, file);

		ctr_tokens.LineToTok(tempLineBuffer);
		InstructionProcess();
	}
	fputs("Press any key to quit", stdout);
	fgetc(stdin);
}

void InstructionProcess() {
	switch (ctr_tokens.GetInstructionCode()) {
	case PRINT:
		if (if_vector.empty() || if_vector.top()->isIFSatisfied(ctr_resources)) { TokenCat(); }
		break;
	case PRINTLN:
		if (if_vector.empty() || if_vector.top()->isIFSatisfied(ctr_resources)) {
			TokenCat();
			fputs("\n", stdout);
		}
		break;
	case IF:
		if (if_vector.empty() || if_vector.top()->isIFSatisfied(ctr_resources)) {
			if_vector.push(new Conditions());
			vector<char*> ifTokens;
			for (int i = 1; i < ctr_tokens.TokenLen(); i++) {
				ifTokens.push_back(ctr_tokens.PeekToken(i));
			}

			if_vector.top()->Append(ifTokens);
			if_vector.top()->QueueBuild();
			/*
			if_vector.push(Conditions());
			vector<char*> ifTokens;
			for (int i = 1; i < ctr_tokens.TokenLen(); i++) {
				ifTokens.push_back(ctr_tokens.PeekToken(i));
			}

			if_vector.top().Append(ifTokens);
			//if_vector.top().QueueBuild();
			*/
		}
		break;
	case WHILE:
		if (if_vector.empty() || if_vector.top()->isIFSatisfied(ctr_resources)) {

		}
		break;
	case END:
		if (!if_vector.empty()) {
			delete if_vector.top();
			if_vector.pop();
		}
		break;
	case VAR: // could be variable declaration
		// variale validation
		// variable cannot start with number
		if (if_vector.empty() || if_vector.top()->isIFSatisfied(ctr_resources)) {
			try {
				ctr_resources.VariableValidation(ctr_tokens.PeekToken(1));
				TokenOperatorCheck(ctr_tokens.PeekToken(1)[0]);
				ctr_tokens.IsVarOperator(ctr_tokens.PeekToken(2));
			}
			catch (int err) {
				fputs("number/operator cannot be a variable name", stderr);
				exit(err);
			}


			if (ctr_resources.VarSearchByName(ctr_tokens.PeekToken(1)) == -1) {
				ctr_resources.VarInit(ctr_tokens.PeekToken(1), ctr_tokens.PeekToken(3));
			}
			else {
				fputs("Invalid variable name", stderr);
				exit(-1);
			}
		}
		
		break;
	}
	ctr_tokens.Release();
}

void TokenCat() {
	if (ctr_tokens.TokenLen() < 2) {
		fputs("few arguments Usage: print/println args..", stderr);
		exit(-1);
	}
	size_t len = 0;
	char strBuffer[TEMP_BUF];
	char* rtnPtr;
	memset(strBuffer, 0, sizeof(char) * TEMP_BUF);

	// first token
	sprintf_s(strBuffer, "%s", ctr_resources.VarGetStrDataByName(ctr_tokens.PeekToken(1)));
	if (ctr_tokens.TokenLen() == 3) {
		sprintf_s(strBuffer, "%s %s", strBuffer, ctr_resources.VarGetStrDataByName(ctr_tokens.PeekToken(2)));
	}
	else if (ctr_tokens.TokenLen() > 3) {
		for (int i = 2; i < ctr_tokens.TokenLen(); i++) {
			sprintf_s(strBuffer, "%s %s",strBuffer,  ctr_resources.VarGetStrDataByName(ctr_tokens.PeekToken(i)));
		}
	}
	len = strlen(strBuffer);
	strBuffer[len + 1] = 0;
	fputs(strBuffer, stdout);
}
