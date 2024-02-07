#pragma once
#include "StandardDefs.h"

class Variable
{
private:
	char* vName = nullptr;
	char* sData = nullptr;
	double nData = NULL;
public:
	Variable();
	explicit Variable(const char*, const char*);
	Variable(const Variable&);
	Variable(Variable&&) noexcept;
	// constructors
	
	char* GetVarName() const;
	void Set(const char*);
	double GetNum() const;
	char* GetStr() const;
	// helper

	operator char*() { return sData; }
	operator double() {
		return nData;
	}

	Variable& operator=(const Variable&);
	Variable& operator=(Variable&&) noexcept;
	Variable operator+(const Variable&) const;
	Variable& operator+(const Variable&);
	Variable& operator+=(const Variable&);
	Variable& operator+=(const char*);
	Variable& operator-=(const Variable&);
	Variable& operator-=(const char*);
	Variable& operator-(const Variable&);
	Variable operator-(const Variable&) const;
	bool operator==(const Variable&) const;
	// operator

	~Variable();
};

