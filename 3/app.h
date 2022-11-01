#pragma once

#define APP
#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <limits>
#include <stdlib.h>
#include <crtdbg.h>
#include <exception>
#include <string>
#include <vector>

#include "sequence.h"
#include "dialog.h"

enum status {
	SUCCESS = 0,
	FAIL,
	OVERSIZE,
	MEMORY_ERROR,
	NOT_FOUND,
	WRONG_PARAMS,
};