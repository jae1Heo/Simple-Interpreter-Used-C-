#include "siuc.h"

VarResources ctr_resources;
Tokenize ctr_tokens;
stack<Conditions*> cond_stack;
// main

vector<char*> loop_elements;
// loop

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

		if ((!cond_stack.empty() && cond_stack.top()->determCondition() == WHILE) || (strstr(tempLineBuffer, "while"))) {
			char* temp = new char[sizeof(char) * strlen(tempLineBuffer) + 1];
			strcpy_s(temp, sizeof(char) * strlen(tempLineBuffer) + 1, tempLineBuffer);
			temp[strlen(tempLineBuffer) + 1] = '\0';
			loop_elements.push_back(temp);
		}

		ctr_tokens.LineToTok(tempLineBuffer);
		InstructionProcess(ctr_resources, ctr_tokens);
	}
	fputs("Press any key to quit", stdout);
	fgetc(stdin);
}

void InstructionProcess(VarResources& ctr_rcs, Tokenize& ctr_tks) {
	switch (ctr_tks.GetInstructionCode()) {
	case PRINT:
		if (cond_stack.empty() || (cond_stack.top()->determCondition() == IF && cond_stack.top()->isIFSatisfied(ctr_rcs)) || (cond_stack.top()->determCondition() == WHILE && cond_stack.top()->isIFSatisfied(ctr_rcs))) { TokenCat(ctr_rcs, ctr_tks); }
		break;
	case PRINTLN:
		if (cond_stack.empty() || (cond_stack.top()->determCondition() == IF && cond_stack.top()->isIFSatisfied(ctr_rcs)) || (cond_stack.top()->determCondition() == WHILE && cond_stack.top()->isIFSatisfied(ctr_rcs))) {
			TokenCat(ctr_rcs, ctr_tks);
			fputs("\n", stdout);
		}
		break;
	case IF:
		if (cond_stack.empty() || (cond_stack.top()->determCondition() == IF && cond_stack.top()->isIFSatisfied(ctr_rcs)) || (cond_stack.top()->determCondition() == WHILE && cond_stack.top()->isIFSatisfied(ctr_rcs))) {
			cond_stack.push(new Conditions());
			vector<char*> ifTokens;
			for (int i = 1; i < ctr_tks.TokenLen(); i++) {
				ifTokens.push_back(ctr_tks.PeekToken(i));
			}
			
			cond_stack.top()->Append(ifTokens, IF);
		}
		break;
	case WHILE:
		if (cond_stack.empty() || (cond_stack.top()->determCondition() == IF && cond_stack.top()->isIFSatisfied(ctr_rcs)) || (cond_stack.top()->determCondition() == WHILE && cond_stack.top()->isIFSatisfied(ctr_rcs))) {
			cond_stack.push(new Conditions());
			vector<char*> whileTokens;
			for (int i = 1; i < ctr_tks.TokenLen(); i++) {
				whileTokens.push_back(ctr_tks.PeekToken(i));
			}
			
			cond_stack.top()->Append(whileTokens, WHILE);
		}
		break;
	case END:
		if (!cond_stack.empty()) {
			if (cond_stack.top()->determCondition() == WHILE) {
				Tokenize loop_elem_tokenize;
				while (cond_stack.top()->isIFSatisfied(ctr_rcs)) {
					for (int i = 0; i < loop_elements.size(); i++) {
						char* temp = new char[strlen(loop_elements[i]) + 1];
						strcpy_s(temp, sizeof(char) * strlen(loop_elements[i]) + 1, loop_elements[i]);
						temp[strlen(loop_elements[i]) + 1] = '\0';
						loop_elem_tokenize.LineToTok(temp);

						InstructionProcess(ctr_rcs, loop_elem_tokenize);
						loop_elem_tokenize.Release();
					}
				}
			}
			if (cond_stack.top()->getSubRoutineVarCounter() > 0) {
				for (int i = 0; i < cond_stack.top()->getSubRoutineVarCounter(); i++) {
					ctr_rcs.RemoveLastVariable();
				}
			}
			cond_stack.pop();
		}
		break;
	case VAR: // could be variable declaration
		// variale validation
		// variable cannot start with number
		if (cond_stack.empty() || (cond_stack.top()->determCondition() == IF && cond_stack.top()->isIFSatisfied(ctr_rcs)) || (cond_stack.top()->determCondition() == WHILE && cond_stack.top()->isIFSatisfied(ctr_rcs))) {
			try {
				ctr_rcs.VariableValidation(ctr_tks.PeekToken(1));
				TokenOperatorCheck(ctr_tks.PeekToken(1)[0]);
				ctr_tks.IsVarOperator(ctr_tks.PeekToken(2));
			}
			catch (int err) {
				fputs("number/operator cannot be a variable name", stderr);
				exit(err);
			}


			if (ctr_rcs.VarSearchByName(ctr_tks.PeekToken(1)) == -1) {
				ctr_rcs.VarInit(ctr_tks.PeekToken(1), ctr_tks.PeekToken(3));
				if (!cond_stack.empty()) {
					cond_stack.top()->incSubRoutineVarCounter();
				}
			}
			else {
				fputs("Invalid variable name", stderr);
				exit(-1);
			}
		}
		
		break;
	default:
		if (ctr_rcs.VarSearchByName(ctr_tks.PeekToken(0)) > -1) { 
			// arithmatic operation could only be done by two arguments - a = a + b
			if(TokenOperatorCheck(ctr_tks.PeekToken(1)) == 0) {
				// 0 =(1) 2 +,-(3) 4
				Variable temp = ctr_rcs.varAt(ctr_rcs.VarSearchByName(ctr_tks.PeekToken(2)));
				switch (TokenOperatorCheck(ctr_tks.PeekToken(3))) {
				case SUB:			
					ctr_rcs.varAt(ctr_rcs.VarSearchByName(ctr_tks.PeekToken(0))) = temp - ctr_rcs.varAt(ctr_rcs.VarSearchByName(ctr_tks.PeekToken(4)));
					break;
				case ADD:
					ctr_rcs.varAt(ctr_rcs.VarSearchByName(ctr_tks.PeekToken(0))) = temp + ctr_rcs.varAt(ctr_rcs.VarSearchByName(ctr_tks.PeekToken(4)));
					break;
				default:
					fputs("Invalid operator", stderr);
					exit(-1);
				}
			}
			else { // if not '='
				fputs("Invalid operator", stderr);
				exit(-1);
			}
		}
		else {
			printf("variable %s is undefined \n", ctr_tks.PeekToken(0));
			exit(-1);
		}
	}
	ctr_tks.Release();
}


void TokenCat(VarResources& ctr_rcs, Tokenize& ctr_tks) {
	if (ctr_tks.TokenLen() < 2) {
		fputs("few arguments Usage: print/println args..", stderr);
		exit(-1);
	}
	size_t len = 0;
	char strBuffer[TEMP_BUF];
	char* rtnPtr;
	memset(strBuffer, 0, sizeof(char) * TEMP_BUF);

	// first token
	sprintf_s(strBuffer, "%s", ctr_rcs.VarGetStrDataByName(ctr_tks.PeekToken(1)));
	if (ctr_tks.TokenLen() == 3) {
		sprintf_s(strBuffer, "%s %s", strBuffer, ctr_rcs.VarGetStrDataByName(ctr_tks.PeekToken(2)));
	}
	else if (ctr_tks.TokenLen() > 3) {
		for (int i = 2; i < ctr_tks.TokenLen(); i++) {
			sprintf_s(strBuffer, "%s %s",strBuffer,  ctr_rcs.VarGetStrDataByName(ctr_tks.PeekToken(i)));
		}
	}
	len = strlen(strBuffer);
	strBuffer[len + 1] = 0;
	fputs(strBuffer, stdout);
}
