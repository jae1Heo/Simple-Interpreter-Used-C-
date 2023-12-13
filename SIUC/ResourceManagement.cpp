#include "ResourceManagement.h"

VarResources::VarResources() {}

void VarResources::VarInit(const char* v_name, const char* v_data) {
	var_table.push_back(new Variable(v_name, v_data));
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

bool VarResources::VariableValidation(const char* token) {
	char var_name_f = token[0];
	if (isdigit(var_name_f)) {
		return false;
	}
	return true;
	
} // if given variable's first character is a number, returns false. otherwise, returns true.

const char* VarResources::VarGetDataByName(const char* v_name) {
	int index = VarSearchByName(v_name);
	if (index < 0) {
		return v_name;
	}
	else {
		return var_table[index]->GetStr();
	}
} // if variable exists, returns data. otherwise, returns given name

VarResources::~VarResources() {
	var_table.~vector();
}