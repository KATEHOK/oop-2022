#pragma once

#define APP

#include <iostream>

#include "sequence.h"

enum status {
	SUCCESS = 0,
	FAIL,
	OVERSIZE,
	MEMORY_ERROR,
};