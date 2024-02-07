#include "Variable.h"

Variable::Variable() {}

Variable::Variable(const char* v_name, const char* rhs) {
	vName = new char[strlen(v_name) + 1];
	strcpy_s(vName, strlen(v_name) + 1, v_name);
	if (!(nData = strtod(rhs, NULL))) {
		nData = INT_MIN;
	}
	sData = new char[strlen(rhs) + 1];
	strcpy_s(sData, sizeof(char) * strlen(rhs) + 1, rhs);
}

Variable::Variable(const Variable& rhc) {
	vName = new char[strlen(rhc.vName) + 1];
	strcpy_s(vName, strlen(rhc.vName) + 1, rhc.vName);
	if (rhc.GetNum() != NULL) {
		nData = rhc.GetNum();
	}
	sData = new char[strlen(rhc.GetStr()) + 1];
	strcpy_s(sData, sizeof(char) * strlen(rhc.GetStr()) + 1, rhc.GetStr());
}

Variable::Variable(Variable&& rhc) noexcept{
	operator=(rhc);
}

char* Variable::GetVarName() const {
	return vName;
}

void Variable::Set(const char* rhs) {
	if (!(nData = strtod(rhs, NULL))) {
		nData = INT_MIN;
	}
	delete[] sData;
	sData = new char[strlen(rhs) + 1];
	strcpy_s(sData, sizeof(char) * strlen(rhs) + 1, rhs);
}

double Variable::GetNum() const {
	if (nData != INT_MIN) {
		return nData;
	}
	return INT_MIN;
}

char* Variable::GetStr() const {
	if (sData != nullptr) {
		return sData;
	}
	return nullptr;
}

Variable& Variable::operator=(const Variable& rhc) {
	if ((nData = rhc.GetNum()) == INT_MIN) {
		nData = INT_MIN;
	}
	delete[] sData;
	sData = new char[strlen(rhc.GetStr()) + 1];
	strcpy_s(sData, sizeof(char) * strlen(rhc.GetStr()) + 1, rhc.GetStr());
	return *this;
}

Variable& Variable::operator=(Variable&& rhc) noexcept{
	if ((nData = rhc.GetNum()) == INT_MIN) {
		nData = INT_MIN;
	}
	sData = rhc.sData;
	rhc.sData = nullptr;
	rhc.nData = INT_MIN;
	return *this;
}

Variable Variable::operator+(const Variable& rhc) const {
	Variable temp(*this);
	if (rhc.GetNum() != INT_MIN && temp.GetNum() != INT_MIN) {
		double d_temp = nData + rhc.GetNum();
		temp.nData = d_temp;
		temp.Set(to_string(d_temp).c_str());
	}
	else {
		char* s_temp = new char[strlen(temp.GetStr()) + strlen(rhc.GetStr()) + 1];
		strcpy_s(s_temp, strlen(temp.GetStr()) + strlen(rhc.GetStr()) + 1, Append(temp.GetStr(), rhc.GetStr()));
		temp.Set(s_temp);
	}

	return temp;
}

Variable& Variable::operator+(const Variable& rhc) {
	double n_temp = nData;
	if (rhc.GetNum() != INT_MIN && nData != INT_MIN) {
		nData += rhc.GetNum();
		Set(to_string(nData).c_str());
	}
	else {
		char* s_temp = new char[strlen(sData) + 1];
		strcpy_s(s_temp, sizeof(char) * strlen(sData) + 1, sData);
		delete[] sData;
		sData = new char[strlen(s_temp) + strlen(rhc.GetStr()) + 1];
		strcpy_s(sData, strlen(s_temp) + strlen(rhc.GetStr()) + 1, Append(s_temp, rhc.GetStr()));
	}
	return *this;
}

Variable& Variable::operator+=(const Variable& rhc) {
	double n_temp = nData;
	if (rhc.GetNum() != INT_MIN && nData != INT_MIN) {
		nData += rhc.GetNum();
		Set(to_string(nData).c_str());
	}
	else {
		char* s_temp = new char[strlen(sData) + 1];
		strcpy_s(s_temp, sizeof(char) * strlen(sData) + 1, sData);
		delete[] sData;
		sData = new char[strlen(s_temp) + strlen(rhc.GetStr()) + 1];
		strcpy_s(sData, strlen(s_temp) + strlen(rhc.GetStr()) + 1, Append(s_temp, rhc.GetStr()));
	}
	return *this;
}

// string 
Variable& Variable::operator+=(const char* rhs) {
	if (nData != INT_MIN && strtod(rhs, NULL)) {
		nData += strtod(rhs, NULL);
		Set(to_string(nData).c_str());
	}
	else {
		char* s_temp = new char[strlen(sData) + 1];
		strcpy_s(s_temp, sizeof(char) * strlen(sData) + 1, sData);
		delete[] sData;
		sData = new char[strlen(s_temp) + strlen(rhs) + 1];
		strcpy_s(sData, strlen(s_temp) + strlen(rhs) + 1, Append(s_temp, rhs));
	}
	return *this;
}

Variable& Variable::operator-(const Variable& rhc) {
	if (rhc.GetNum() != INT_MIN && nData != INT_MIN) {
		nData -= rhc.GetNum();
		Set(to_string(nData).c_str());
	}
	else { // if both variables are not a number, quit program
		fputs("strings cannot be subtracted", stderr);
		exit(-1);
	}
	return *this;
}

Variable Variable::operator-(const Variable& rhc) const {
	Variable temp(*this);
	if (temp.GetNum() != INT_MIN && rhc.GetNum() != INT_MIN) {
		temp.nData -= rhc.nData;
	}
	else {
		fputs("strings cannot be subtracted", stderr);
		exit(-1);
	}
	return temp;
}

Variable& Variable::operator-=(const Variable& rhc) {
	if (rhc.GetNum() != INT_MIN && nData != INT_MIN) {
		nData -= rhc.GetNum();
		Set(to_string(nData).c_str());
	}
	else {
		fputs("strings cannot be subtracted", stderr);
		exit(-1);
	}
	return *this;
}

Variable& Variable::operator-=(const char* rhs) {
	if (nData != INT_MIN && strtod(rhs, NULL)) {
		nData -= strtod(rhs, NULL);
		Set(to_string(nData).c_str());
	}
	else {
		fputs("strings cannot be subtracted", stderr);
		exit(-1);
	}

	return *this;
}

bool Variable::operator==(const Variable& rhc) const {
	if (this->GetNum() != INT_MIN && rhc.GetNum() != INT_MIN) {
		return (this->GetNum() == rhc.GetNum());
	}
	else {
		if (!strcmp(this->GetStr(), rhc.GetStr())) {
			return true;
		}
		else {
			return false;
		}
	}
}

Variable::~Variable() {
	delete[] sData;
	delete[] vName;
	nData = INT_MIN;
}