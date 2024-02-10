#pragma once
#include "StandardDefs.h"
#include "ResourceManagement.h"

class Conditions {
protected:
	char** left;
	char** right;
	size_t left_size;
	size_t right_size;
	char* cmp_op;
	int cond; // false - if, true - while
	int subRoutineVarCounter; 
public:
	Conditions();
	void Append(vector<char*>, int);
	bool isIFSatisfied(VarResources&);
	void conditionSet(int); // helper method - setting variable "ifOrWhile" 0, 1 are available for the argument. 
	int determCondition();
	void incSubRoutineVarCounter();
	int getSubRoutineVarCounter();
	void resetSubRoutineVarCounter();
	~Conditions();
};
