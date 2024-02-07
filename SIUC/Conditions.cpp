#include "Conditions.h"


Conditions::Conditions() :  left_size(0), right_size(0), cmp_op(nullptr), left(nullptr), right(nullptr) {}

Conditions::~Conditions() {
	delete cmp_op;
	delete[] left;
	delete[] right;

}

void Conditions::Append(vector<char*> args) {
	int idx = 0;
	while (TokenOperatorCheckComp(args[idx]) >= 3) {
		idx++;
	}
	left = new char* [sizeof(char*) * idx - 1];

	for (int i = 0; i < idx; i++) {
		left[i] = new char[sizeof(char) * strlen(args[i]) + 1];
		strcpy_s(left[i], sizeof(char) * strlen(args[i]) + 1, args[i]);
		left[i][sizeof(char) * strlen(args[i]) + 1] = '\0';
		left_size++;
	}
	
	cmp_op = new char[sizeof(char) * strlen(args[idx]) + 1];
	strcpy_s(cmp_op, sizeof(char) * strlen(args[idx]) + 1, args[idx]);
	cmp_op[strlen(args[idx]) + 1] = '\0';
	
	right = new char* [sizeof(char*) * (args.size() - idx) + 1];

	for (int i = idx + 1; i < args.size(); i++) {
		right[i - (idx + 1)] = new char[sizeof(char) * strlen(args[i]) + 1];
		strcpy_s(right[i - (idx + 1)], sizeof(char) * strlen(args[i]) + 1, args[i]);
		right[i - (idx + 1)][sizeof(char) * strlen(args[i]) + 1] = '\0';
		right_size++;
	}

}

bool Conditions::isIFSatisfied(VarResources& var) { 
	Variable v_left, v_l_temp;
	Variable v_right, v_r_temp;
	int curOp = 0; // variable curOp would be used for storing both side's arithmetic operators.

	// computing left side
	v_left.Set(var.VarGetStrDataByName(left[0]));
	bool isLeftStringOnly = (v_left.GetNum() == INT_MIN);

	// if left side has more than one arguemtns
	if (left_size > 1) {
		for (int i = 1; i < left_size; i++) {
			if (TokenOperatorCheck(left[i]) > 0 && TokenOperatorCheck(left[i]) < 3) {
				curOp = TokenOperatorCheck(left[i]);
			}
			else {
				v_l_temp.Set(var.VarGetStrDataByName(left[i]));
				try {
					if (isLeftStringOnly && v_l_temp.GetNum() != INT_MIN) {
						throw isLeftStringOnly;
					}
					if (!isLeftStringOnly && v_l_temp.GetNum() == INT_MIN) {
						throw isLeftStringOnly;
					}
				}
				catch (bool err) {
					fputs("string cannot operated with integer", stderr);
					exit(-1);
				}

				try {
					if (curOp <= 0) {
						throw curOp;
					}
					else {
						switch (curOp) {
						case SUB:
							v_left -= v_l_temp;
							break;
						case ADD:
							v_left += v_l_temp;
							break;
						}
					}
				}
				catch (int err) {
					fputs("Operator = cannot be used", stderr);
					exit(-1);
				}
			}
		}
	}
	
	// computing right side
	v_right.Set(var.VarGetStrDataByName(right[0]));
	bool isRightStringOnly = (v_right.GetNum() == INT_MIN);

	// if right side has more than one arguments
	if (right_size > 1) {
		for (int i = 1; i < right_size; i++) {
			if (TokenOperatorCheck(right[i]) > 0 && TokenOperatorCheck(right[i]) < 3) {
				curOp = TokenOperatorCheck(right[i]);
			}
			else {
				v_r_temp.Set(var.VarGetStrDataByName(right[i]));
				try {
					if (isRightStringOnly && v_r_temp.GetNum() != INT_MIN) {
						throw isRightStringOnly;
					}

					if (!isRightStringOnly && v_r_temp.GetNum() == INT_MIN) {
						throw isRightStringOnly;
					}
				}
				catch (int err) {
					fputs("string cannot operated with integer", stderr);
					exit(-1);
				}

				try {
					if (curOp <= 0) {
						throw curOp;
					}
					else {
						switch (curOp) {
						case SUB:
							v_right -= v_r_temp;
							break;
						case ADD:
							v_right += v_r_temp;
							break;
						}
					}
				}
				catch (int err) {
					fputs("Operator = cannot be used", stderr);
					exit(-1);
				}
				
			}
		}
	}

	// computing results



	// if both sides are string,
	if (isLeftStringOnly && isRightStringOnly) {
		// for string, only equal operator would be allowed to compare.
		// if given is not an equal operator
		if (TokenOperatorCheckComp(cmp_op) > 0) {
			fputs("Cannot compare between strings", stderr);
			exit(-1);
		}
		else {
			return (v_left == v_right);
		}
	}
	// if both sides are integer
	else if (!isLeftStringOnly && !isRightStringOnly) {
		switch (TokenOperatorCheckComp(cmp_op)) {
		case EQU_C:
			return (v_left == v_right);
			break;
		case LESS:
			return (v_left.GetNum() < v_right.GetNum());
			break;
		case GRT:
			return (v_left.GetNum() > v_right.GetNum());
			break;
		}
	}
	// otherwise
	else {
		fputs("String cannot be operated with integer", stderr);
		exit(-1);
	}

}
