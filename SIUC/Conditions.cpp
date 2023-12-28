#include "Conditions.h"


Conditions::Conditions() : expression(nullptr), exp_num(0), cmp_op(nullptr) {}
Conditions::~Conditions() {
	if (!Ops_a.empty()) {
		for (int i = 0; i < Ops_a.size(); i++) {
			Ops_a.pop_back();
		}
	}

	if (!Args.empty()) {
		for (int i = 0; i < Args.size(); i++) {
			Args.pop_back();
		}
	}
	
	for (int i = 0; i < exp_num; i++) {
		delete[] expression[i];
	}

	delete[] expression;

}

void Conditions::Append(vector<char*> args) {
	int tk_op;
	for (auto& tk : args) {
		tk_op = TokenOperatorCheck(tk); // if given token is an argument or an comp operator, returns 3
		try {
			if (tk_op <= 0) {
				throw tk_op;
			}
			if (tk_op >= 3) { 
				Args.push_back(tk);
			}
			else {
				Ops_a.push_back(tk);
			}
		}
		catch (int err) {
			fputs("operator = cannot be used in if-statement", stderr);
		}
	}
}

void Conditions::QueueBuild() {
	queue<char*> tk_queue;
	int opIdx = 0;
	tk_queue.push(Args[0]);
	for (int i = 0; i < Args.size() - 1; i++) {
		if (TokenOperatorCheckComp(Args[i]) != 3) {
			cmp_op = new char[sizeof(char) * sizeof(Args[i]) + 1];
			strcpy_s(cmp_op, sizeof(Args[i]) + 1, Args[i]); // if-statement can only have single compare operator.
			tk_queue.push(Args[i + 1]);
		}
		else {
			if (TokenOperatorCheckComp(Args[i + 1]) == 3) {
				tk_queue.push(Args[i + 1]);
				tk_queue.push(Ops_a[opIdx]);
				opIdx++;
			}
			else {
				tk_queue.push(Args[i + 1]);
			}
		}
	}

	deque<char*> deq = tk_queue._Get_container(); // deque for receive container of the queue
	vector<char*> tks;
	for (auto& a : deq) {
		tks.push_back(a);
	}

	expression = new char* [tks.size()];
	size_t index = 0;
	for (int i = 0; i < tks.size(); i++) {
		expression[i] = new char[sizeof(tks[i]) + 1];
		strcpy_s(expression[i], sizeof(tks[i]) + 1, tks[i]);
	}

	exp_num = tks.size(); // member variable for the number of tokens

}

bool Conditions::isIFSatisfied(VarResources& var) { 
	int index = 0; // local variable to divide epression. left exp, operator, right exp
	Variable v_left, v_l_temp;
	Variable v_right, v_r_temp;
	// while loop for getting index of compare operator
	while (strcmp(expression[index], cmp_op)) {
		index++;
	}
	
	v_left.Set(var.VarGetStrDataByName(expression[0]));
	for (int i = 1; i < index; i++) {
		try {
			if (!TokenOperatorCheck(expression[i])) {
				throw i;
			}
			else if (TokenOperatorCheck(expression[i]) < 3) {
				if (TokenOperatorCheck(expression[i]) == 1) {
					// if subtraction
					v_left = v_left - v_l_temp;
				}
				else if (TokenOperatorCheck(expression[i]) == 2) {
					// if addition
					v_left = v_left + v_l_temp;
				}
			}
			else {
				v_l_temp.Set(var.VarGetStrDataByName(expression[i]));
			}
		}
		catch (int err) {
			fputs("= operator cannot be used in if-statement", stderr);
			exit(-1);
		}
	}
	

	v_right.Set(var.VarGetStrDataByName(expression[index + 1]));
	for (int i = index + 2; i < exp_num; i++) {
		try {
			if (!TokenOperatorCheck(expression[i])) {
				throw i;
			}
			else if (TokenOperatorCheck(expression[i]) < 3) {
				if (TokenOperatorCheck(expression[i]) == 1) {
					// if subtraction
					v_right = v_right - v_r_temp;
				}
				else if (TokenOperatorCheck(expression[i]) == 2) {
					// if addition
					v_right = v_right + v_r_temp;
				}
			}
			else {
				v_r_temp.Set(var.VarGetStrDataByName(expression[i]));
			}
		}
		catch (int err) {
			fputs("= operator cannot be used in if-statement", stderr);
			exit(-1);
		}
	}

	// compare expression
	if (!TokenOperatorCheckComp(cmp_op)) {
		if (v_left.GetNum() != NULL && v_right.GetNum() != NULL) {
			// if left and right are both string,
			if (!strcmp(v_left, v_right)) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (v_left.GetNum() == NULL && v_right.GetNum() == NULL) {
			// if left and right are both number;
			if (v_left.GetNum() == v_right.GetNum()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			fputs("number and string cannot be compared", stderr);
			exit(-1);
		}
	}
}


void Conditions::Release() {
	
}