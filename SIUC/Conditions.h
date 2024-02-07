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
public:
	Conditions();
	void Append(vector<char*>);
	bool isIFSatisfied(VarResources&); // **helper method - checking if-statement is satisfied
	~Conditions();
};
