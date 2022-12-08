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

		//! @brief Указатель на вектор - хозяин итератора
		T* _owner = nullptr;

		//! @brief Индекс элемента (для end(), cend() равен vector.size) 
		size_t _id = 0;

		/**
		* @brief Конструктор по умолчанию (никуда не указывает)
		*/
		vector_const_it() {}

		/**
		* @brief Конструктор по значениям полей
		* @param owner Ссылка на объект - хозяин
		* @param id Индекс элемента
		*/
		vector_const_it(vector<T>& owner, size_t id = 0) : _owner(owner), _id(id) {}

	public:

		/**
		* @brief Копирующий конструктор
		* @param src Ссылка на копируемый итератор
		*/
		vector_const_it(const vector_const_it& src) : _owner(src._owner), _id(src._id) {}

		/**
		* @brief Перемещающий конструктор
		* @param src Ссылка на перемещаемый итератор
		*/
		vector_const_it(vector_const_it&& src) : _owner(src._owner), _id(src._id)
		{
			if (this != &src)
			{
				src._owner = nullptr;
				src._id = 0;
			}
		}

		/**
		* @brief Копирующий оператор присваивания
		* @param src Ссылка на копируемый итератор
		* @return Ссылка на скопированный итератор
		*/
		vector_const_it& operator= (const vector_const_it& src)
		{
			_owner = src._owner;
			_id = src._id;
			return *this;
		}

		/**
		* @brief Перемещающий оператор присваивания
		* @param src Ссылка на перемещаемый итератор
		* @return Ссылка на перемещенный итератор
		*/
		vector_const_it& operator= (vector_const_it&& src)
		{
			if (this != &src)
			{
				_owner = src._owner;
				_id = src._id;

				src._owner = nullptr;
				src._id = 0;
			}
			return *this;
		}

		/**
		* @brief Оператор сравнения двух итераторов одного хозяина
		* @param other Ссылка на оператор, с которым необходимо сравнение
		* @return true в случае равенства индексов, false в случае их различия
		* (выбрасывает исключение, если разные хозяева)
		*/
		bool operator== (const vector_const_it& other) const
		{
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id == other._id;
		}

		/**
		* @brief Оператор сравнения двух итераторов одного хозяина
		* @param other Ссылка на оператор, с которым необходимо сравнение
		* @return true в случае различия индексов, false в случае их равенства
		* (выбрасывает исключение, если разные хозяева)
		*/
		bool operator!= (const vector_const_it& other) const
		{
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id != other._id;
		}

		/**
		* @brief Оператор сравнения двух итераторов одного хозяина
		* @param other Ссылка на оператор, с которым необходимо сравнение
		* @return true если индекс левого операнда меньше индекса правого,
		* false в противном случае
		* (выбрасывает исключение, если разные хозяева)
		*/
		bool operator< (const vector_const_it& other) const
		{
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id < other._id;
		}

		/**
		* @brief Оператор сравнения двух итераторов одного хозяина
		* @param other Ссылка на оператор, с которым необходимо сравнение
		* @return true если индекс левого операнда больше индекса правого,
		* false в противном случае
		* (выбрасывает исключение, если разные хозяева)
		*/
		bool operator> (const vector_const_it& other) const
		{
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id > other._id;
		}

		/**
		* @brief Оператор сравнения двух итераторов одного хозяина
		* @param other Ссылка на оператор, с которым необходимо сравнение
		* @return true если индекс левого операнда меньше или равен индексу правого,
		* false в противном случае
		* (выбрасывает исключение, если разные хозяева)
		*/
		bool operator<= (const vector_const_it& other) const
		{
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id <= other._id;
		}

		/**
		* @brief Оператор сравнения двух итераторов одного хозяина
		* @param other Ссылка на оператор, с которым необходимо сравнение
		* @return true если индекс левого операнда больше или равен индексу правого,
		* false в противном случае
		* (выбрасывает исключение, если разные хозяева)
		*/
		bool operator>= (const vector_const_it& other) const
		{
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id >= other._id;
		}

		/**
		* @brief Оператор разыменования
		* @return Константная ссылка на элемент
		*/
		const T& operator* () const
		{
			if (_id >= _owner->_size) throw std::out_of_range("Iterator points outside the vector");
			return _owner->_items[_id];
		}

		/**
		* @brief Постфиксный инкремент
		* @return Константный итератор
		*/
		vector_const_it& operator++ ()
		{
			vector_const_it copy(*this);
			if (_id < _owner->_size) _id++;
			return copy;
		}

		/**
		* @brief Постфиксный декремент
		* @return Константный итератор
		*/
		vector_const_it& operator-- ()
		{
			vector_const_it copy(*this);
			if (_id > 0) _id--;
			return copy;
		}

		/**
		* @brief Префиксный инкремент
		* @return Константный итератор
		*/
		vector_const_it& operator++ (int value)
		{
			if (_id < _owner->_size) _id++;
			return *this;
		}

		/**
		* @brief Префиксный декремент
		* @return Константный итератор
		*/
		vector_const_it& operator-- (int value)
		{
			if (_id > 0) _id--;
			return *this;
		}

		/**
		* @brief Оператор увеличения итератора на число позиций
		* @param value Желаемое смещение
		* @return Смещенный итератор
		*/
		vector_const_it& operator+= (int value)
		{
			for (int i = 0; i < value; ++i) ++(*this);
			return *this;
		}

		/**
		* @brief Оператор уменьшения итератора на число позиций
		* @param value Желаемое смещение
		* @return Смещенный итератор
		*/
		vector_const_it& operator-= (int value)
		{
			for (int i = 0; i < value; ++i) --(*this);
			return *this;
		}

		/**
		* @brief Оператор увеличения итератора на другой итератор
		* @param other Другой итератор
		* @return Смещенный итератор
		*/
		vector_const_it& operator+= (const vector_const_it& other)
		{
			if (_owner != other._owner) 
				throw std::exception("Cannot aperate with diferent vectors iterators");
			for (int i = 0; i < other._id; ++i) ++(*this);
			return *this;
		}

		/**
		* @brief Оператор уменьшения итератора на другой итератор
		* @param other Другой итератор
		* @return Смещенный итератор
		*/
		vector_const_it& operator-= (const vector_const_it& other)
		{
			if (_owner != other._owner)
				throw std::exception("Cannot aperate with diferent vectors iterators");
			for (int i = 0; i < other._id; ++i) --(*this);
			return *this;
		}

		/**
		* @brief Оператор сложения итератора и целого числа
		* @param it Ссылка на итератор
		* @param value Число
		* @return Новый итератор, указывающий на элемент, смещенный на value позиций относительно it
		*/
		friend vector_const_it operator+ (const vector_const_it& it, int value)
		{
			vector_const_it result(it);
			it += value;
			return result;
		}

		/**
		* @brief Оператор сложения итератора и целого числа
		* @param value Число
		* @param it Ссылка на итератор
		* @return Новый итератор, указывающий на элемент, смещенный на value позиций относительно it
		*/
		friend vector_const_it operator+ (int value, const vector_const_it& it)
		{
			vector_const_it result(it);
			it += value;
			return result;
		}

		/**
		* @brief Оператор вычитания из итератора целого числа
		* @param it Ссылка на итератор
		* @param value Число
		* @param it Ссылка на итератор
		* @return Новый итератор, указывающий на элемент, смещенный на value позиций относительно it
		*/
		friend vector_const_it operator- (const vector_const_it& it, int value)
		{
			vector_const_it result(it);
			it -= value;
			return result;
		}

		/**
		* @brief Оператор вычитания из итератора целого числа
		* @param value Число
		* @param it Ссылка на итератор
		* @return Новый итератор, указывающий на элемент, смещенный на value позиций относительно it
		*/
		friend vector_const_it operator- (int value, const vector_const_it& it)
		{
			vector_const_it result(it);
			it -= value;
			return result;
		}

		/**
		* @brief Оператор сложения двух итераторов
		* @param left Ссыдка на левый итератор
		* @param right Ссылка на правый итератор
		* @return Новый итератор, указывающий на элемент под индексом = сумме индексов операндов
		*/
		friend vector_const_it operator+ (
			const vector_const_it& left,
			const vector_const_it& right)
		{
			vector_const_it result(left);
			result += right;
			return result;
		}

		/**
		* @brief Оператор вычитания одного итератора из другого
		* @param left Ссыдка на левый итератор
		* @param right Ссылка на правый итератор
		* @return Новый итератор, указывающий на элемент под индексом = разности индексов операндов
		*/
		friend vector_const_it operator- (
			const vector_const_it& left,
			const vector_const_it& right)
		{
			vector_const_it result(left);
			result -= right;
			return result;
		}

	};

	/**
	* @brief Неконстантный итератор (при разыменовании можно изменять адрессат)
	*/
	template<typename T>
	class vector_it : public vector_const_it<T>
	{

	private:

	public:

		/**
		* @brief Оператор разыменования
		* @return Ссылка на указваемый элемент
		*/
		T& operator* () const
		{
			if (_id >= _owner->_size) throw std::out_of_range("Iterator points outside the vector");
			return _owner->_items[_id];
		}

		/**
		* @brief Постфиксный инкремент
		* @return Итератор
		*/
		vector_it& operator++ ()
		{
			vector_const_it copy(*this);
			if (_id < _owner->_size) _id++;
			return copy;
		}

		/**
		* @brief Постфиксный декремент
		* @return Итератор
		*/
		vector_it& operator-- ()
		{
			vector_const_it copy(*this);
			if (_id > 0) _id--;
			return copy;
		}

		/**
		* @brief Префиксный инкремент
		* @return Итератор
		*/
		vector_it& operator++ (int value)
		{
			if (_id < _owner->_size) _id++;
			return *this;
		}

		/**
		* @brief Префиксный декремент
		* @return Итератор
		*/
		vector_it& operator-- (int value)
		{
			if (_id > 0) _id--;
			return *this;
		}

		/**
		* @brief Оператор увеличения итератора на число позиций
		* @param value Желаемое смещение
		* @return Смещенный итератор
		*/
		vector_it& operator+= (int value)
		{
			for (int i = 0; i < value; ++i) ++(*this);
			return *this;
		}

		/**
		* @brief Оператор уменьшения итератора на число позиций
		* @param value Желаемое смещение
		* @return Смещенный итератор
		*/
		vector_it& operator-= (int value)
		{
			for (int i = 0; i < value; ++i) --(*this);
			return *this;
		}

		/**
		* @brief Оператор увеличения итератора на другой итератор
		* @param other Другой итератор
		* @return Смещенный итератор
		*/
		vector_it& operator+= (const vector_const_it& other)
		{
			if (_owner != other._owner)
				throw std::exception("Cannot aperate with diferent vectors iterators");
			for (int i = 0; i < other._id; ++i) ++(*this);
			return *this;
		}

		/**
		* @brief Оператор уменьшения итератора на другой итератор
		* @param other Другой итератор
		* @return Смещенный итератор
		*/
		vector_it& operator-= (const vector_const_it& other)
		{
			if (_owner != other._owner)
				throw std::exception("Cannot aperate with diferent vectors iterators");
			for (int i = 0; i < other._id; ++i) --(*this);
			return *this;
		}

		/**
		* @brief Оператор сложения итератора и целого числа
		* @param it Ссылка на итератор
		* @param value Число
		* @return Новый итератор, указывающий на элемент, смещенный на value позиций относительно it
		*/
		friend vector_it operator+ (const vector_const_it& it, int value)
		{
			vector_const_it result(it);
			it += value;
			return result;
		}

		/**
		* @brief Оператор сложения итератора и целого числа
		* @param value Число
		* @param it Ссылка на итератор
		* @return Новый итератор, указывающий на элемент, смещенный на value позиций относительно it
		*/
		friend vector_it operator+ (int value, const vector_const_it& it)
		{
			vector_const_it result(it);
			it += value;
			return result;
		}

		/**
		* @brief Оператор вычитания из итератора целого числа
		* @param it Ссылка на итератор
		* @param value Число
		* @param it Ссылка на итератор
		* @return Новый итератор, указывающий на элемент, смещенный на value позиций относительно it
		*/
		friend vector_it operator- (const vector_const_it& it, int value)
		{
			vector_const_it result(it);
			it -= value;
			return result;
		}

		/**
		* @brief Оператор вычитания из итератора целого числа
		* @param value Число
		* @param it Ссылка на итератор
		* @return Новый итератор, указывающий на элемент, смещенный на value позиций относительно it
		*/
		friend vector_it operator- (int value, const vector_const_it& it)
		{
			vector_it result(it);
			it -= value;
			return result;
		}

		/**
		* @brief Оператор сложения двух итераторов
		* @param left Ссыдка на левый итератор
		* @param right Ссылка на правый итератор
		* @return Новый итератор, указывающий на элемент под индексом = сумме индексов операндов
		*/
		friend vector_it operator+ (
			const vector_const_it& left,
			const vector_const_it& right)
		{
			vector_it result(left);
			result += right;
			return result;
		}

		/**
		* @brief Оператор вычитания одного итератора из другого
		* @param left Ссыдка на левый итератор
		* @param right Ссылка на правый итератор
		* @return Новый итератор, указывающий на элемент под индексом = разности индексов операндов
		*/
		friend vector_it operator- (
			const vector_const_it& left,
			const vector_const_it& right)
		{
			vector_it result(left);
			result -= right;
			return result;
		}

	};


}
