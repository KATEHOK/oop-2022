#pragma once

#define ITERATOR_DECLARATION

#ifndef VECTOR
#include "vector.h"
#endif // !VECTOR

namespace my_template {

	/**
	* @brief Константный итератор (при разыменовании нельзя изменять адрессат)
	*/
	template<typename T>
	class vector_const_it
	{

	protected:

		T* _pointer = nullptr;

		vector_const_it() {}

		vector_const_it(T* pointer) : _pointer(pointer) {}

	public:

		vector_const_it(const vector_const_it& src);

		vector_const_it(vector_const_it&& src);

		vector_const_it& operator= (const vector_const_it& src);

		vector_const_it& operator= (vector_const_it&& src);

		bool operator== (const vector_const_it& other) const;

		bool operator!= (const vector_const_it& other) const;

		bool operator< (const vector_const_it& other) const;

		bool operator> (const vector_const_it& other) const;

		bool operator<= (const vector_const_it& other) const;

		bool operator>= (const vector_const_it& other) const;

		const T& operator* () const;

		vector_const_it& operator++ ();

		vector_const_it& operator-- ();

		vector_const_it& operator++ (int value);

		vector_const_it& operator-- (int value);

		vector_const_it& operator+= (int value);

		vector_const_it& operator-= (int value);

		friend vector_const_it operator+ (const vector_const_it& it, int value);

		friend vector_const_it operator+ (int value, const vector_const_it& it);

		friend vector_const_it operator- (const vector_const_it& it, int value);

		friend vector_const_it operator- (int value, const vector_const_it& it);
	};

	/**
	* @brief Неконстантный итератор (при разыменовании можно изменять адрессат)
	*/
	template<typename T>
	class vector_it : public vector_const_it<T>
	{

	private:

	public:

		T& operator* () const;

	};


}
