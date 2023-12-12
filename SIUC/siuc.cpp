#include "siuc.h"

VarResources ctr_resources;
Tokenize ctr_tokens;

char tempLineBuffer[TEMP_BUF];

void RecvTokens(const char* fn) {
	FILE* file = fopen(fn, "r");
	while (!feof(file)) {
		fgets(tempLineBuffer, TEMP_BUF, file);
		ctr_tokens.LineToTok(tempLineBuffer);
		InstructionProcess();
	
	}
}

void InstructionProcess() {
	switch (ctr_tokens.GetInstructionCode()) {
	case PRINT:
		break;
	case PRINTLN:
		break;
	case IF:
		break;
	case WHILE:
		break;
	case END:
		break;
	case ERR:
		exit(-1);

	}
}