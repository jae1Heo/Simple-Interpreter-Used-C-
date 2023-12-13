#pragma once
#include "StandardDefs.h"
#include "Variable.h"

class VarResources {
private:
	// variable table
	//vector<Variable*>var_table;
	// queue for loop
	queue<char*>loop_que;
	// stack for conditions
	stack<char*>cond_stk;
public:
	vector<Variable*>var_table;
	VarResources();
	void VarInit(const char*, const char*);
	signed int VarSearchByName(const char*);
	const char* VarGetDataByName(const char*);
	bool VariableValidation(const char*);
	
	~VarResources();
	
};




