#include "ResourceManagement.h"

VarResources::VarResources() {}

void VarResources::VarInit(const char* v_name, const char* v_data) {
	var_table.push_back(new Variable(v_name, v_data));
}

void VarResources::PushCondition(const char* s_cond) {
	cond_stk.push(const_cast<char*>(s_cond));
}

char* VarResources::TopCondition() const {
	return cond_stk.top();
}

void VarResources::PopCondition() {
	cond_stk.pop();
}

signed int VarResources::VarSearchByName(const char* v_name) {
	int index = 0;
	for (auto& var : var_table) {
		if (!strcmp(var_table[index]->GetVarName(), v_name)) {
			return index;
		}
		index++;
	}

	return -1;
}

void VarResources::VariableValidation(const char* token) {
	char var_name_f = token[0];
	if (isdigit(var_name_f)) {
		throw int(var_name_f);
	}
}

const char* VarResources::VarGetStrDataByName(const char* v_name) {
	int index = VarSearchByName(v_name);
	if (index < 0) {
		return v_name;
	}
	else {
		return var_table[index]->GetStr();
	}
} // if variable exists, returns string data. otherwise, returns given name

const double VarResources::VarGetDataByName(const char* v_name) {
	int index = VarSearchByName(v_name);
	if (index < 0) {
		return NULL;
	}
	else {
		return var_table[index]->GetNum();
	}
	 
} // if variable exists, returns data (double). otherwise, returns null

VarResources::~VarResources() {
	var_table.~vector();
}