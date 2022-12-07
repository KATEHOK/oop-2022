#pragma once

#define VECTOR_DEFINITION

#ifndef VECTOR
#include "vector.h"
#endif // !VECTOR

namespace my_template {

	// private

	template<class T>
	T* vector<T>::_get_items(size_t max_count) const
	{
		T* result = new T[max_count];
		if (_size < max_count) max_count = _size;
		for (int i = 0; i < max_count; ++i) result[i] = _items[i];
		return result;
	}

	template<class T>
	void vector<T>::_set_moved_items(T* items, size_t moving, size_t capacity)
	{
		if (_items != nullptr) return;
		if (capacity < moving) capacity = moving;

		_items = new T[capacity];
		_capacity = capacity;
		_size = moving;
		for (int i = 0; i < moving; ++i) _items[i] = std::move(items[i]);
	}

	template<class T>
	size_t vector<T>::_resize(size_t capacity)
	{
		T* old_vector = _items;
		size_t moving = _size < capacity ? _size : capacity;

		_set_moved_items(old_vector, moving, capacity);
		_capacity = capacity;
		_size = moving;

		delete[] old_vector;
		return _capacity;
	}

	template<class T>
	size_t vector<T>::_add_block()
	{
		_resize(_capacity + _block);
		return _capacity;
	}

	template<class T>
	size_t vector<T>::_remove_block()
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

	template<class T>
	void vector<T>::_set_items(T (&static_arr)[])
	{
		size_t N = _get_static_array_size(static_arr);
		delete[] _items;
		_capacity = N;
		_size = N;
		_items = new T[N];
		for (int i = 0; i < N; ++i) _items[i] = static_arr[i];
	}

	// public

	template<class T>
	vector<T>::vector(T (&static_arr)[])
	{
		_set_items(static_arr);
	}

	template<class T>
	vector<T>::vector(T* items, size_t moving)
	{
		_set_moved_items(items, moving);
	}

	template<class T>
	vector<T>::vector(const vector& src)
	{
		_size = src._size;
		_capacity = src._capacity;
		_items = src._get_items(_size);
	}

	template<class T>
	vector<T>::vector(vector&& src)
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

	template<class T>
	vector<T>::~vector()
	{
		delete[] _items;
		_items = nullptr;
	}

	template<class T>
	vector<T>& vector<T>::operator= (T (&static_arr)[])
	{
		_set_items(static_arr);
		return *this;
	}

	template<class T>
	vector<T>& vector<T>::operator= (const vector<T>& src)
	{
		_size = src._size;
		_capacity = src._capacity;
		_items = src._get_items(_size);
		return *this;
	}

	template<class T>
	vector<T>& vector<T>::operator= (vector<T>&& src)
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

	template<class T>
	size_t vector<T>::size() const
	{
		return _size;
	}

	template<class T>
	size_t vector<T>::capacity() const
	{
		return _capacity;
	}

	template<class T>
	void vector<T>::push_back(const T& value)
	{
		if (_size == _capacity) _add_block();
		_items[_size] = value;
		_size++;
	}

	template<class T>
	void vector<T>::push_back(T&& value)
	{
		if (_size == _capacity) _add_block();
		_items[_size] = value;
		_size++;
	}

	template<class T>
	void vector<T>::clear()
	{
		_size = 0;
		_capacity = 0;
		delete[] _items;
		_items = nullptr;
	}

	template<class T>
	T& vector<T>::operator[] (int id) const
	{
		if (id < 0 || id >= _size) throw std::out_of_range("Invalid index in vector::operator[]");
		return _items[id];
	}

	template<class T>
	vector_it<T> vector<T>::begin() const
	{
		return iterator(_items);
	}

	template<class T>
	vector_it<T> vector<T>::end() const
	{
		return iterator(_items + _size);
	}

	template<class T>
	vector_const_it<T> vector<T>::cbegin() const
	{
		return const_iterator(_items);
	}

	template<class T>
	vector_const_it<T> vector<T>::cend() const
	{
		return const_iterator(_items + _size);
	}

	template<class T>
	vector_it<T> vector<T>::insert(const vector<T>::const_iterator position, const T& value)
	{
		int id = position._pointer - _items;
		if (id >= _capacity) _add_block();
		for (int i = _size; i > id; --i) _items[i] = std::move(_items[i - 1]);
		_items[id] = value;
		_size++;
		return iterator(_items + id);
	}

	template<class T>
	vector_it<T> vector<T>::insert(const vector<T>::const_iterator position, T&& value)
	{
		int id = position._pointer - _items;
		if (id >= _capacity) _add_block();
		for (int i = _size; i > id; --i) _items[i] = std::move(_items[i - 1]);
		_items[id] = value;
		_size++;
		return iterator(_items + id);
	}

	// QUESTION
	template<class T>
	vector_it<T> vector<T>::erase(const vector<T>::const_iterator position)
	{
		int id = position._pointer - _items;
		if (id == _size) throw std::out_of_range("Iterator is out of range in vector::erase()");

		if (id < _size - 1)	for (int i = id; i < _size; ++i) _items[i] = std::move(_items[i + 1]);
		if (id == _size - 1)
		{
			try { _items[id].~T(); } // ?
			catch (...);
		}
		_size--;

		if (_capacity - _size >= _block) _remove_block();
		return iterator(_items + id);
	}

}

