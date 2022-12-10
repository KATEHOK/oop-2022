#pragma once

#ifndef VECTOR
#include "vector.h"
#endif // !VECTOR

namespace my_template {

	/**
	* @brief Базовый шаблон класса итератора для вектора
	*/
	template<class T, class returnedT>
	class vector_iterator
	{

		friend class vector<T>;

	protected:

		//! @brief Указатель на вектор - хозяин итератора
		vector<T>* _owner = nullptr;

		//! @brief Индекс элемента (для end(), cend() равен vector.size) 
		size_t _id = 0;

		/**
		* @brief Проверяет и при необходимости корректирует индекс
		*/
		void _correct_id()
		{
			if (_id < 0) _id = 0;
			if (_owner != nullptr && _id > _owner->_size) _id = _owner->_size;
		}

		/**
		* @brief Конструктор по умолчанию (никуда не указывает)
		*/
		vector_iterator() {}

		/**
		* @brief Конструктор по значениям полей
		* @param owner Указатель на объект - хозяин
		* @param id Индекс элемента
		*/
		vector_iterator(const vector<T>* owner, size_t id = 0) :
			_owner(const_cast<vector<T>*>(owner)), _id(id)
		{
			_correct_id();
		}

		/**
		* @brief Копирующий конструктор
		* @param src Ссылка на копируемый итератор
		*/
		vector_iterator(const vector_iterator& src) : _owner(src._owner), _id(src._id)
		{
			_correct_id();
		}

		/**
		* @brief Перемещающий конструктор
		* @param src Ссылка на перемещаемый итератор
		*/
		vector_iterator(vector_iterator&& src) : _owner(src._owner), _id(src._id)
		{
			if (this != &src)
			{
				src._owner = nullptr;
				src._id = 0;
			}
			_correct_id();
		}

	public:

		/**
		* @brief Копирующий оператор присваивания
		* @param src Ссылка на копируемый итератор
		* @return Ссылка на скопированный итератор
		*/
		vector_iterator& operator= (const vector_iterator& src)
		{
			_owner = src._owner;
			_id = src._id;
			_correct_id();
			return *this;
		}

		/**
		* @brief Перемещающий оператор присваивания
		* @param src Ссылка на перемещаемый итератор
		* @return Ссылка на перемещенный итератор
		*/
		vector_iterator& operator= (vector_iterator&& src)
		{
			if (this != &src)
			{
				_owner = src._owner;
				_id = src._id;

				src._owner = nullptr;
				src._id = 0;
			}
			_correct_id();
			return *this;
		}

		/**
		* @brief Оператор разыменования
		* @return Cсылка на элемент (неконстантная, если returnedT == const T)
		*/
		returnedT& operator* () const
		{
			if (_owner == nullptr)
				throw std::exception("Iterator has not owner");
			if (_id >= _owner->_size)
				throw std::out_of_range("Iterator points outside the vector");
			return _owner->_items[_id];
		}

		/**
		* @brief Геттер индекса элемента
		* @return Индекс элемента
		*/
		size_t id() const
		{
			if (_owner == nullptr)
				throw std::exception("Iterator has not owner");
			return _id;
		}

		/**
		* @brief Оператор сравнения двух итераторов одного хозяина
		* @param other Ссылка на итератор, с которым необходимо сравнение
		* @return true в случае равенства индексов, false в случае их различия
		* (выбрасывает исключение, если разные хозяева)
		*/
		bool operator== (const vector_iterator& other) const
		{
			if (_owner == nullptr || other._owner == nullptr)
				throw std::exception("Iterator has not owner");
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id == other._id;
		}

		/**
		* @brief Оператор сравнения двух итераторов одного хозяина
		* @param other Ссылка на итератор, с которым необходимо сравнение
		* @return true в случае различия индексов, false в случае их равенства
		* (выбрасывает исключение, если разные хозяева)
		*/
		bool operator!= (const vector_iterator& other) const
		{
			if (_owner == nullptr || other._owner == nullptr)
				throw std::exception("Iterator has not owner");
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id != other._id;
		}

		/**
		* @brief Оператор сравнения двух итераторов одного хозяина
		* @param other Ссылка на итератор, с которым необходимо сравнение
		* @return true если индекс левого операнда меньше индекса правого,
		* false в противном случае
		* (выбрасывает исключение, если разные хозяева)
		*/
		bool operator< (const vector_iterator& other) const
		{
			if (_owner == nullptr || other._owner == nullptr)
				throw std::exception("Iterator has not owner");
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id < other._id;
		}

		/**
		* @brief Оператор сравнения двух итераторов одного хозяина
		* @param other Ссылка на итератор, с которым необходимо сравнение
		* @return true если индекс левого операнда больше индекса правого,
		* false в противном случае
		* (выбрасывает исключение, если разные хозяева)
		*/
		bool operator> (const vector_iterator& other) const
		{
			if (_owner == nullptr || other._owner == nullptr)
				throw std::exception("Iterator has not owner");
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id > other._id;
		}

		/**
		* @brief Оператор сравнения двух итераторов одного хозяина
		* @param other Ссылка на итератор, с которым необходимо сравнение
		* @return true если индекс левого операнда меньше или равен индексу правого,
		* false в противном случае
		* (выбрасывает исключение, если разные хозяева)
		*/
		bool operator<= (const vector_iterator& other) const
		{
			if (_owner == nullptr || other._owner == nullptr)
				throw std::exception("Iterator has not owner");
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id <= other._id;
		}

		/**
		* @brief Оператор сравнения двух итераторов одного хозяина
		* @param other Ссылка на итератор, с которым необходимо сравнение
		* @return true если индекс левого операнда больше или равен индексу правого,
		* false в противном случае
		* (выбрасывает исключение, если разные хозяева)
		*/
		bool operator>= (const vector_iterator& other) const
		{
			if (_owner == nullptr || other._owner == nullptr)
				throw std::exception("Iterator has not owner");
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id >= other._id;
		}

		/**
		* @brief Постфиксный инкремент
		* @return Итератор
		*/
		vector_iterator operator++ (int value)
		{
			if (_owner == nullptr)
				throw std::exception("Iterator has not owner");
			_correct_id();
			vector_iterator copy(*this);
			if (_id < _owner->_size) _id++;
			return copy;
		}

		/**
		* @brief Постфиксный декремент
		* @return Итератор
		*/
		vector_iterator operator-- (int value)
		{
			if (_owner == nullptr)
				throw std::exception("Iterator has not owner");
			_correct_id();
			vector_iterator copy(*this);
			if (_id > 0) _id--;
			return copy;
		}

		/**
		* @brief Префиксный инкремент
		* @return Итератор
		*/
		vector_iterator& operator++ ()
		{
			if (_owner == nullptr)
				throw std::exception("Iterator has not owner");
			_correct_id();
			if (_id < _owner->_size) _id++;
			return *this;
		}

		/**
		* @brief Префиксный декремент
		* @return Итератор
		*/
		vector_iterator& operator-- ()
		{
			if (_owner == nullptr)
				throw std::exception("Iterator has not owner");
			_correct_id();
			if (_id > 0) _id--;
			return *this;
		}

		/**
		* @brief Оператор увеличения итератора на число позиций
		* @param value Желаемое смещение
		* @return Смещенный итератор
		*/
		vector_iterator& operator+= (int value)
		{
			if (_owner == nullptr)
				throw std::exception("Iterator has not owner");
			_correct_id();
			for (int i = 0; i < value; ++i) ++(*this);
			return *this;
		}

		/**
		* @brief Оператор уменьшения итератора на число позиций
		* @param value Желаемое смещение
		* @return Смещенный итератор
		*/
		vector_iterator& operator-= (int value)
		{
			if (_owner == nullptr)
				throw std::exception("Iterator has not owner");
			_correct_id();
			for (int i = 0; i < value; ++i) --(*this);
			return *this;
		}

		/**
		* @brief Оператор увеличения итератора на другой итератор
		* @param other Другой итератор
		* @return Смещенный итератор
		*/
		vector_iterator& operator+= (const vector_iterator& other)
		{
			if (_owner == nullptr || other._owner == nullptr)
				throw std::exception("Iterator has not owner");
			if (_owner != other._owner) 
				throw std::exception("Cannot aperate with diferent vectors iterators");

			for (int i = 0; i < other._id; ++i) ++(*this);
			_correct_id();
			return *this;
		}

		/**
		* @brief Оператор уменьшения итератора на другой итератор
		* @param other Другой итератор
		* @return Смещенный итератор
		*/
		vector_iterator& operator-= (const vector_iterator& other)
		{
			if (_owner == nullptr || other._owner == nullptr)
				throw std::exception("Iterator has not owner");
			if (_owner != other._owner)
				throw std::exception("Cannot aperate with diferent vectors iterators");

			for (int i = 0; i < other._id; ++i) --(*this);
			_correct_id();
			return *this;
		}

		/**
		* @brief Оператор сложения итератора и целого числа
		* @param it Ссылка на итератор
		* @param value Число
		* @return Новый итератор, указывающий на элемент, смещенный на value позиций относительно it
		*/
		friend vector_iterator operator+ (const vector_iterator& it, int value)
		{
			if (it._owner == nullptr)
				throw std::exception("Iterator has not owner");

			vector_iterator result(it);
			result += value;

			result._correct_id();
			return result;
		}

		/**
		* @brief Оператор сложения итератора и целого числа
		* @param value Число
		* @param it Ссылка на итератор
		* @return Новый итератор, указывающий на элемент, смещенный на value позиций относительно it
		*/
		friend vector_iterator operator+ (int value, const vector_iterator& it)
		{
			if (it._owner == nullptr)
				throw std::exception("Iterator has not owner");

			vector_iterator result(it);
			result += value;

			result._correct_id();
			return result;
		}

		/**
		* @brief Оператор вычитания из итератора целого числа
		* @param it Ссылка на итератор
		* @param value Число
		* @param it Ссылка на итератор
		* @return Новый итератор, указывающий на элемент, смещенный на value позиций относительно it
		*/
		friend vector_iterator operator- (const vector_iterator& it, int value)
		{
			if (it._owner == nullptr)
				throw std::exception("Iterator has not owner");

			vector_iterator result(it);
			result -= value;

			result._correct_id();
			return result;
		}

		/**
		* @brief Оператор вычитания из итератора целого числа
		* @param value Число
		* @param it Ссылка на итератор
		* @return Новый итератор, указывающий на элемент, смещенный на value позиций относительно it
		*/
		friend vector_iterator operator- (int value, const vector_iterator& it)
		{
			if (it._owner == nullptr)
				throw std::exception("Iterator has not owner");

			vector_iterator result(it);
			result -= value;

			result._correct_id();
			return result;
		}

		/**
		* @brief Оператор сложения двух итераторов
		* @param left Ссыдка на левый итератор
		* @param right Ссылка на правый итератор
		* @return Новый итератор, указывающий на элемент под индексом = сумме индексов операндов
		*/
		friend vector_iterator operator+ (
			const vector_iterator& left,
			const vector_iterator& right)
		{
			if (left._owner == nullptr || right._owner == nullptr)
				throw std::exception("Iterator has not owner");
			if (left._owner != right._owner)
				throw std::exception("Cannot aperate with diferent vectors iterators");

			vector_iterator result(left);
			result += right;

			result._correct_id();
			return result;
		}

		/**
		* @brief Оператор вычитания одного итератора из другого
		* @param left Ссыдка на левый итератор
		* @param right Ссылка на правый итератор
		* @return Новый итератор, указывающий на элемент под индексом = разности индексов операндов
		*/
		friend vector_iterator operator- (
			const vector_iterator& left,
			const vector_iterator& right)
		{
			if (left._owner == nullptr || right._owner == nullptr)
				throw std::exception("Iterator has not owner");
			if (left._owner != right._owner)
				throw std::exception("Cannot aperate with diferent vectors iterators");

			vector_iterator result(left);
			result -= right;

			result._correct_id();
			return result;
		}

	};

	/**
	* @brief Шаблон неконстантного итератора
	*/
	template<class T>
	class vector_it : public vector_iterator<T, T> {

		friend class vector<T>;
		friend class vector_const_it<T>;

	private:

		/**
		* @brief Конструктор по умолчанию (никуда не указывает)
		*/
		vector_it() : vector_iterator<T, T>() {}

		/**
		* @brief Конструктор по значениям полей
		* @param owner Указатель на объект - хозяин
		* @param id Индекс элемента
		*/
		vector_it(const vector<T>* owner, size_t id) :
			vector_iterator<T, T>(owner, id) {}

	public:

		/**
		* @brief Копирующий конструктор
		* @param src Ссылка на копируемый итератор
		*/
		vector_it(const vector_iterator<T, T>& src) : vector_iterator<T, T>(src) {}

		/**
		* @brief Перемещающий конструктор
		* @param src Ссылка на перемещаемый итератор
		*/
		vector_it(vector_iterator<T, T>&& src) : vector_iterator<T, T>(src) {}

		/**
		* @brief Деструктор устанавливает nullptr для указателя на хозяина и 0 для _id
		*/
		~vector_it()
		{
			this->_id = 0;
			this->_owner = nullptr;
		}

	};

	/**
	* @brief Шаблон константного итератора
	*/
	template<class T>
	class vector_const_it : public vector_iterator<T, const T> {

		friend class vector<T>;

	private:

		/**
		* @brief Конструктор по умолчанию (никуда не указывает)
		*/
		vector_const_it() : vector_iterator<T, const T>() {}

		/**
		* @brief Конструктор по значениям полей
		* @param owner Указатель на объект - хозяин
		* @param id Индекс элемента
		*/
		vector_const_it(const vector<T>* owner, size_t id) :
			vector_iterator<T, const T>(owner, id) {}

	public:

		/**
		* @brief Копирующий конструктор
		* @param src Ссылка на копируемый итератор
		*/
		vector_const_it(const vector_iterator<T, const T>& src) :
			vector_iterator<T, const T>(src) {}

		/**
		* @brief Перемещающий конструктор
		* @param src Ссылка на перемещаемый итератор
		*/
		vector_const_it(vector_iterator<T, const T>&& src) :
			vector_iterator<T, const T>(src) {}

		/**
		* @brief Деструктор устанавливает nullptr для указателя на хозяина и 0 для _id
		*/
		~vector_const_it()
		{
			this->_id = 0;
			this->_owner = nullptr;
		}

		/**
		* @brief Копирующий конструктор на основе неконстантного итератора
		* @param src Ссылка на неконстантный итератор
		*/
		vector_const_it(const vector_it<T>& src) 
		{
			this->_owner = src._owner;
			this->_id = src._id;
			this->_correct_id();
		}

		/**
		* @brief Перемещающий конструктор на основе неконстантного итератора
		* @param src Ссылка на неконстантный итератор
		*/
		vector_const_it(vector_it<T>&& src)
		{
			if (this != &src)
			{
				this->_owner = src._owner;
				this->_id = src._id;

				src._owner = nullptr;
				src._id = 0;
			}
			this->_correct_id();
		}

		/**
		* @brief
		* @param
		* @return
		*/
		vector_const_it& operator= (const vector_it<T>& src)
		{
			this->_owner = src._owner;
			this->_id = src._id;
			this->_correct_id();
			return *this;
		}

		/**
		* @brief
		* @param
		* @return
		*/
		vector_const_it& operator= (vector_it<T>&& src)
		{
			if (this != &src)
			{
				this->_owner = src._owner;
				this->_id = src._id;

				src._owner = nullptr;
				src._id = 0;
			}
			this->_correct_id();
			return *this;
		}

	};


}
