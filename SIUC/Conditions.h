#pragma once
#include "StandardDefs.h"
#include "ResourceManagement.h"

class Conditions {
protected:
	vector<char*>Ops_a; // arithmetic operators
	vector<char*>Args; // arguments
	queue<char*>q;
public:
	Conditions();
	void Append(vector<char*>);
	//virtual bool CondCheck();
	void QueueBuild();
	void Release();
	~Conditions();
};

class ConditionIF : Conditions {
public:
	ConditionIF();
	//virtual bool CondCheck();
	~ConditionIF();
};

class ConditionWHILE : Conditions {
public:
	ConditionWHILE();
	//virtual bool CondCheck();
	~ConditionWHILE();
};
