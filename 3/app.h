#pragma once

#define APP

#include <iostream>
#include <limits>

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