#pragma once
#define APP
#define _CRTDBG_MAP_ALLOC
#define _USE_MATH_DEFINES
#define TEST

#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#include <cmath>
#include <string>

#include "strophoid.h"
#include "funcs.h"

enum STATUS_CODE {
	SUCCESS = 0,
	FAIL,
	MEMORY_ERROR,
	WRONG_PARAMS,
	NOT_FOUND
};