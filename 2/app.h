#pragma once

#define APP
#define _USE_MATH_DEFINES
#include <cmath>
#include "strophoid.h"


#ifndef CLASS_ONLY

#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#include <string>
#include "funcs.h"

enum STATUS_CODE {
	SUCCESS = 0,
	FAIL,
	MEMORY_ERROR,
	WRONG_PARAMS,
	NOT_FOUND
};

#endif



/*

1. ������ ������ �� ������ ����������������� � ������������� (������ ����/�����) // DONE

2. ������, �� ���������� ��������� ������� ������ ����� �������� const // DONE

3. ��������� ������� ������ ���� const // DONE

4. ������� ���������� �����

*/