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

VarResources::~VarResources() {
	var_table.~vector();
}