#pragma once
#include "StandardDefs.h"
#include "ResourceManagement.h"

class Conditions {
protected:
	vector<char*>Ops_a; // arithmetic operators
	vector<char*>Args; // arguments
	char** expression;
	size_t exp_num;
	char* cmp_op;
public:
	Conditions();
	void Append(vector<char*>);
	void QueueBuild(); 
	bool isIFSatisfied(VarResources&); // **helper method - checking if-statement is satisfied
	void Release();
	~Conditions();
};
