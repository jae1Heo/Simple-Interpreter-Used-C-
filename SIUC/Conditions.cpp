#include "Conditions.h"


Conditions::Conditions() {}
Conditions::~Conditions() {}

ConditionIF::ConditionIF() {}
ConditionIF::~ConditionIF(){}

ConditionWHILE::ConditionWHILE() {}
ConditionWHILE::~ConditionWHILE() {}

void Conditions::Append(vector<char*> args) {
	for (auto& tk : args) {
		try {
			if (TokenOperatorCheck(tk) == 0) {
				throw 0;
			}
		}
		catch (int err) {
			fputs("Arithmetic equal(=) cannot be used", stderr);
			exit(-1);
		}

		if (TokenOperatorCheck(tk) != 3) {
			Ops_a.push_back(tk);
		}
		else {
			Args.push_back(tk);
		}
	}
}

void Conditions::QueueBuild() {
	int opIdx = 0;
	q.push(Args[0]);
	for (int i = 0; i < Args.size() - 1; i++) {
		if (TokenOperatorCheckComp(Args[i]) != 3) {
			q.push(Args[i + 1]);
		}
		else {
			if (TokenOperatorCheckComp(Args[i + 1]) == 3) {
				q.push(Args[i + 1]);
				q.push(Ops_a[opIdx]);
				opIdx++;
			}
			else  {
				q.push(Args[i + 1]);
			}
		}
	}
}

void Conditions::Release() {
	
}