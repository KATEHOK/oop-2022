#pragma once

#define FUNCS

#include <iostream>

namespace funcs {

	template<typename T, std::size_t N>
	constexpr std::size_t array_size(T(&arr)[N]) noexcept
	{
		return N;
	}

}
