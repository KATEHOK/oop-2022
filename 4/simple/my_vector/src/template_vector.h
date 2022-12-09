#pragma once

#ifndef VECTOR
#include "vector.h"
#endif // !VECTOR

namespace my_template
{
	template<class T, class returnedT>
	class vector_iterator;

	template<class T>
	class vector_it;

	template<class T>
	class vector_const_it;

	template<class T>
	class vector
	{		

		friend class vector_iterator<T, T>;
		friend class vector_iterator<T, const T>;
		friend class vector_it<T>;
		friend class vector_const_it<T>;

	public:

		//! @brief Константный итератор (при разыменовании нельзя изменять адрессат)
		typedef vector_it<T> iterator;

		//! @brief Неконстантный итератор (при разыменовании можно изменять адрессат)
		typedef vector_const_it<T> const_iterator;

	private:

		//! @brief Массив элементов типа T
		T* _items = nullptr;

		//! @brief Количество элементов
		size_t _size = 0;

		//! @brirf Предел количества элементов для текущего размера вектора
		size_t _capacity = 0;

		//! @brief Количество элементов, под которое за раз выделяется память
		static const size_t _block = 10;

		/**
		* @brief Создает массив - копию элементов вектора
		* @param max_count Максимальное количество элементов, которое нужно скопировать
		* @return Указатель на массив
		*/
		T* _get_items(size_t max_count) const
		{
			T* result = new T[max_count];
			if (_size < max_count) max_count = _size;
			for (int i = 0; i < max_count; ++i) result[i] = _items[i];
			return result;
		}

		/**
		* @brief Функция инициализирует вектор, перемещая элементы динамического массива
		* (только для изначально пустого вектора)
		* @param items Массив (динамический)
		* @param moving Количество перемещаемых элементов
		* @param capacity Желаемая вместимость вектора (по умолчанию = count, capacity >= count)
		*/
		void _set_moved_items(T* items, size_t moving, size_t capacity = 0)
		{
			if (_items != nullptr) return;
			if (capacity < moving) capacity = moving;

			_items = new T[capacity];
			_capacity = capacity;
			_size = moving;
			for (int i = 0; i < moving; ++i) _items[i] = std::move(items[i]);
		}

		/**
		* @brief Перевыделяет память с сохранением помещающихся данных
		* @param capacity Предел количества элементов для желаемого размера вектора
		* @return Предел количества элементов для нового размера вектора
		*/
		size_t _resize(size_t capacity)
		{
			T* old_vector = _items;
			size_t moving = _size < capacity ? _size : capacity;

			_set_moved_items(old_vector, moving, capacity);
			_capacity = capacity;
			_size = moving;

			delete[] old_vector;
			return _capacity;
		}

		/**
		* @brief Выделяет дополнительный блок памяти с сохранением данных
		* @return Предел количества элементов для нового размера вектора
		*/
		size_t _add_block()
		{
			_resize(_capacity + _block);
			return _capacity;
		}

		/**
		* @brief Очищает один блок памяти с сохранением помещающихся данных
		* @return Предел количества элементов для нового размера вектора
		*/
		size_t _remove_block()
		{
			if (_capacity <= _block)
			{
				_capacity = 0;
				_size = 0;
				delete[] _items;
				_items = nullptr;
			}
			else _resize(_capacity - _block);

			return _capacity;
		}

		/**
		* @brief Функция, инициализирующая вектор по статическому массиву
		* @param static_arr Массив (статический)
		* @param N количествоо копируемых объектов
		*/
		void _set_items(T static_arr[], size_t N)
		{
			delete[] _items;
			_capacity = N;
			_size = N;
			_items = new T[N];
			for (int i = 0; i < N; ++i) _items[i] = static_arr[i];
		}

	public:

		/**
		* @brief Консттруктор по умолчанию (пустой вектор)
		*/
		vector() {}

		/**
		* @brief Конструктор по статическому массиву (копирует элементы)
		* @param static_arr Статический массив
		*/
		template<size_t N>
		vector(T (&static_arr)[N])
		{
			_set_items(static_arr, N);
		}

		// initializer_list<T> для статического массива

		/**
		* @brief Конструктор по динамическому массиву (перемещает элементы из массива)
		* @param items Динамический массив
		* @param moving Количество перемещаемых элементов
		*/
		vector(T* items, size_t moving)
		{
			_set_moved_items(items, moving);
		}

		/**
		* @brief Копирующий конструктор
		* @param src Ссылка на копируемый вектор
		*/
		vector(const vector& src)
		{
			_size = src._size;
			_capacity = src._capacity;
			_items = src._get_items(_size);
		}

		/**
		* @brief Перемещающий конструктор
		* @param src Ссылка на перемещаемый вектор
		*/
		vector(vector&& src)
		{
			if (this != &src)
			{
				_size = src._size;
				_capacity = src._capacity;
				_items = src._items;

				src._size = 0;
				src._capacity = 0;
				src._items = nullptr;
			}
		}

		/**
		* @brief Деструктор
		*/
		~vector()
		{
			delete[] _items;
			_items = nullptr;
		}

		/**
		* @brief Оператор присваивания по статическому массиву
		* @param static_arr Статический массив
		* @return Ссылка на получившийся вектор
		*/
		template<size_t N>
		vector& operator= (T (&static_arr)[N])
		{
			_set_items(static_arr, N);
			return *this;
		}

		/**
		* @brief Копирующий оператор присваивания
		* @param src Ссылка на копируемый вектор
		* @return Ссылка на скопированный вектор
		*/
		vector& operator= (const vector& src)
		{
			_size = src._size;
			_capacity = src._capacity;
			_items = src._get_items(_size);
			return *this;
		}

		/**
		* @brief Перемещающий оператор присваивания
		* @param src Ссылка на перемещаемый вектор
		* @return Ссылка на перемещенный вектор
		*/
		vector& operator= (vector&& src)
		{
			if (this != &src)
			{
				_size = src._size;
				_capacity = src._capacity;
				_items = src._items;

				src._size = 0;
				src._capacity = 0;
				src._items = nullptr;
			}
			return *this;
		}

		/**
		* @brief Геттер размера вектора
		* @return Количество элементов в векторе
		*/
		size_t size() const
		{
			return _size;
		}

		/**
		* @brief Геттер вместимости вектора
		* @return Максимально возможное количество элементов в векторе на данный момент
		*/
		size_t capacity() const
		{
			return _capacity;
		}

		/**
		* @brief Копирующая функция добавления элемента в конец вектора
		* @param value Добавляемый элемент
		*/
		void push_back(const T& value)
		{
			if (_size == _capacity) _add_block();
			_items[_size] = value;
			_size++;
		}

		/**
		* @brief Перемещающая функция добавления элемента в конец вектора
		* @param value Добавляемый элемент
		*/
		void push_back(T&& value)
		{
			if (_size == _capacity) _add_block();
			_items[_size] = value;
			_size++;
		}

		/**
		* @brief Очищает вектор
		*/
		void clear()
		{
			_size = 0;
			_capacity = 0;
			delete[] _items;
			_items = nullptr;
		}

		/**
		* @brief Оператор индексирования
		* @param Индекс элемента
		* @return Ссылка на элемент
		*/
		T& operator[] (int id) const
		{
			if (id < 0 || id >= _size)
				throw std::out_of_range("Invalid index in vector::operator[]");
			return _items[id];
		}

		/**
		* @brief Создает итератор, указывающий на первый элемент вектора
		* @return Итератор
		*/
		iterator begin()
		{
			return iterator(this, 0);
		}

		/**
		* @brief Создает итератор, указывающий за предел вектора
		* @return Итератор
		*/
		iterator end()
		{
			return iterator(this, _size);
		}

		/**
		* @brief Создает итератор, указывающий на первый элемент вектора
		* @return Итератор
		*/
		const_iterator begin() const
		{
			return const_iterator(this, 0);
		}

		/**
		* @brief Создает итератор, указывающий за предел вектора
		* @return Итератор
		*/
		const_iterator end() const
		{
			return const_iterator(this, _size);
		}

		/**
		* @brief Создает константный итератор, указывающий на первый элемент вектора
		* @return Итератор
		*/
		const_iterator cbegin() const
		{
			return const_iterator(this, 0);
		}

		/**
		* @brief Создает константный итератор, указывающий за предел вектора
		* @return Итератор
		*/
		const_iterator cend() const
		{
			return const_iterator(this, _size);
		}
		
		/**
		* @brief Вставляет копию элемента по итератору
		* @param position Итератор
		* @param value Ссылка на вставляемый элемент
		* @return Итератор на вставленный элемент
		*/
		iterator insert(const_iterator position, const T& value)
		{
			if (position._id >= _capacity) _add_block();
			for (int i = _size; i > position._id; --i) _items[i] = std::move(_items[i - 1]);
			_items[position._id] = value;
			_size++;
			return iterator(position._owner, position._id);
		}

		/**
		* @brief Вставляет элемент по итератору
		* @param position Итератор
		* @param value Ссылка на вставляемый элемент
		* @return Итератор на вставленный элемент
		*/
		iterator insert(const_iterator position, T&& value)
		{
			if (position._id >= _capacity) _add_block();
			for (int i = _size; i > position._id; --i) _items[i] = std::move(_items[i - 1]);
			_items[position._id] = value;
			_size++;
			return iterator(position._owner, position._id);
		}

		/**
		* @brief Удаляет элемент из вектора по итератору
		* @param position Итератор
		* @return Итератор на удаленный элемент
		*/
		iterator erase(const_iterator position)
		{
			if (position._id >= _size)
				throw std::out_of_range("Iterator is out of range in vector::erase()");

			if (position._id < _size - 1)
				for (int i = position._id; i < _size; ++i) _items[i] = std::move(_items[i + 1]);

			if (position._id == _size - 1)
			{
				try { _items[position._id].~T(); } // Нужно ли вызывать деструктор или забить?
				catch (...) {};
			}
			_size--;

			if (_capacity - _size >= _block) _remove_block();
			return iterator(position._owner, position._id);
		}

	};

}

