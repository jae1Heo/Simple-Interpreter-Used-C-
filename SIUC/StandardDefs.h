#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <string>

#include "Strings.h"


using namespace std;


#define TEMP_BUF 256
#define TOKEN_NUM 10
#define VAR_BUF 1024
#define TOKEN_BUF 1024

enum E_TOKENS{VAR = 0,PRINT = 1, PRINTLN, IF, WHILE, END};
enum OPERATORS{EQU = 0, LESS = 1, GRT = 2, ERR = 3}; // 3 is error for now.

