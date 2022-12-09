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

		//! @brief ����������� �������� (��� ������������� ������ �������� ��������)
		typedef vector_it<T> iterator;

		//! @brief ������������� �������� (��� ������������� ����� �������� ��������)
		typedef vector_const_it<T> const_iterator;

	private:

		//! @brief ������ ��������� ���� T
		T* _items = nullptr;

		//! @brief ���������� ���������
		size_t _size = 0;

		//! @brirf ������ ���������� ��������� ��� �������� ������� �������
		size_t _capacity = 0;

		//! @brief ���������� ���������, ��� ������� �� ��� ���������� ������
		static const size_t _block = 10;

		/**
		* @brief ������� ������ - ����� ��������� �������
		* @param max_count ������������ ���������� ���������, ������� ����� �����������
		* @return ��������� �� ������
		*/
		T* _get_items(size_t max_count) const
		{
			T* result = new T[max_count];
			if (_size < max_count) max_count = _size;
			for (int i = 0; i < max_count; ++i) result[i] = _items[i];
			return result;
		}

		/**
		* @brief ������� �������������� ������, ��������� �������� ������������� �������
		* (������ ��� ���������� ������� �������)
		* @param items ������ (������������)
		* @param moving ���������� ������������ ���������
		* @param capacity �������� ����������� ������� (�� ��������� = count, capacity >= count)
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
		* @brief ������������ ������ � ����������� ������������ ������
		* @param capacity ������ ���������� ��������� ��� ��������� ������� �������
		* @return ������ ���������� ��������� ��� ������ ������� �������
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
		* @brief �������� �������������� ���� ������ � ����������� ������
		* @return ������ ���������� ��������� ��� ������ ������� �������
		*/
		size_t _add_block()
		{
			_resize(_capacity + _block);
			return _capacity;
		}

		/**
		* @brief ������� ���� ���� ������ � ����������� ������������ ������
		* @return ������ ���������� ��������� ��� ������ ������� �������
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
		* @brief �������, ���������������� ������ �� ������������ �������
		* @param static_arr ������ (�����������)
		* @param N ����������� ���������� ��������
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
		* @brief ������������ �� ��������� (������ ������)
		*/
		vector() {}

		/**
		* @brief ����������� �� ������������ ������� (�������� ��������)
		* @param static_arr ����������� ������
		*/
		template<size_t N>
		vector(T (&static_arr)[N])
		{
			_set_items(static_arr, N);
		}

		// initializer_list<T> ��� ������������ �������

		/**
		* @brief ����������� �� ������������� ������� (���������� �������� �� �������)
		* @param items ������������ ������
		* @param moving ���������� ������������ ���������
		*/
		vector(T* items, size_t moving)
		{
			_set_moved_items(items, moving);
		}

		/**
		* @brief ���������� �����������
		* @param src ������ �� ���������� ������
		*/
		vector(const vector& src)
		{
			_size = src._size;
			_capacity = src._capacity;
			_items = src._get_items(_size);
		}

		/**
		* @brief ������������ �����������
		* @param src ������ �� ������������ ������
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
		* @brief ����������
		*/
		~vector()
		{
			delete[] _items;
			_items = nullptr;
		}

		/**
		* @brief �������� ������������ �� ������������ �������
		* @param static_arr ����������� ������
		* @return ������ �� ������������ ������
		*/
		template<size_t N>
		vector& operator= (T (&static_arr)[N])
		{
			_set_items(static_arr, N);
			return *this;
		}

		/**
		* @brief ���������� �������� ������������
		* @param src ������ �� ���������� ������
		* @return ������ �� ������������� ������
		*/
		vector& operator= (const vector& src)
		{
			_size = src._size;
			_capacity = src._capacity;
			_items = src._get_items(_size);
			return *this;
		}

		/**
		* @brief ������������ �������� ������������
		* @param src ������ �� ������������ ������
		* @return ������ �� ������������ ������
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
		* @brief ������ ������� �������
		* @return ���������� ��������� � �������
		*/
		size_t size() const
		{
			return _size;
		}

		/**
		* @brief ������ ����������� �������
		* @return ����������� ��������� ���������� ��������� � ������� �� ������ ������
		*/
		size_t capacity() const
		{
			return _capacity;
		}

		/**
		* @brief ���������� ������� ���������� �������� � ����� �������
		* @param value ����������� �������
		*/
		void push_back(const T& value)
		{
			if (_size == _capacity) _add_block();
			_items[_size] = value;
			_size++;
		}

		/**
		* @brief ������������ ������� ���������� �������� � ����� �������
		* @param value ����������� �������
		*/
		void push_back(T&& value)
		{
			if (_size == _capacity) _add_block();
			_items[_size] = value;
			_size++;
		}

		/**
		* @brief ������� ������
		*/
		void clear()
		{
			_size = 0;
			_capacity = 0;
			delete[] _items;
			_items = nullptr;
		}

		/**
		* @brief �������� ��������������
		* @param ������ ��������
		* @return ������ �� �������
		*/
		T& operator[] (int id) const
		{
			if (id < 0 || id >= _size)
				throw std::out_of_range("Invalid index in vector::operator[]");
			return _items[id];
		}

		/**
		* @brief ������� ��������, ����������� �� ������ ������� �������
		* @return ��������
		*/
		iterator begin()
		{
			return iterator(this, 0);
		}

		/**
		* @brief ������� ��������, ����������� �� ������ �������
		* @return ��������
		*/
		iterator end()
		{
			return iterator(this, _size);
		}

		/**
		* @brief ������� ��������, ����������� �� ������ ������� �������
		* @return ��������
		*/
		const_iterator begin() const
		{
			return const_iterator(this, 0);
		}

		/**
		* @brief ������� ��������, ����������� �� ������ �������
		* @return ��������
		*/
		const_iterator end() const
		{
			return const_iterator(this, _size);
		}

		/**
		* @brief ������� ����������� ��������, ����������� �� ������ ������� �������
		* @return ��������
		*/
		const_iterator cbegin() const
		{
			return const_iterator(this, 0);
		}

		/**
		* @brief ������� ����������� ��������, ����������� �� ������ �������
		* @return ��������
		*/
		const_iterator cend() const
		{
			return const_iterator(this, _size);
		}
		
		/**
		* @brief ��������� ����� �������� �� ���������
		* @param position ��������
		* @param value ������ �� ����������� �������
		* @return �������� �� ����������� �������
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
		* @brief ��������� ������� �� ���������
		* @param position ��������
		* @param value ������ �� ����������� �������
		* @return �������� �� ����������� �������
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
		* @brief ������� ������� �� ������� �� ���������
		* @param position ��������
		* @return �������� �� ��������� �������
		*/
		iterator erase(const_iterator position)
		{
			if (position._id >= _size)
				throw std::out_of_range("Iterator is out of range in vector::erase()");

			if (position._id < _size - 1)
				for (int i = position._id; i < _size; ++i) _items[i] = std::move(_items[i + 1]);

			if (position._id == _size - 1)
			{
				try { _items[position._id].~T(); } // ����� �� �������� ���������� ��� ������?
				catch (...) {};
			}
			_size--;

			if (_capacity - _size >= _block) _remove_block();
			return iterator(position._owner, position._id);
		}

	};

}

