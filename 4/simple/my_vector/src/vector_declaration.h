#pragma once

#define VECTOR_DECLARATION

#ifndef VECTOR
#include "vector.h"
#endif // !VECTOR

namespace my_template
{

	template<class T>
	class vector_it;

	template<class T>
	class vector_const_it;

	template<class T>
	class vector
	{		

		friend class vector_it<T>;

		friend class vector_const_it<T>;

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
		* @brief ������ ����������� �������, ������������ ������ ������������ �������
		* @param ����������� ������
		* @return ���������� ��������� �������
		*/
		template<size_t N>
		size_t _get_static_array_size(T(&)[N]) const
		{
			return N;
		}

		/**
		* @brief ������� ������ - ����� ��������� �������
		* @param max_count ������������ ���������� ���������, ������� ����� �����������
		* @return ��������� �� ������
		*/
		T* _get_items(size_t max_count) const;

		/**
		* @brief ������� �������������� ������, ��������� �������� ������������� �������
		* (������ ��� ���������� ������� �������)
		* @param items ������ (������������)
		* @param moving ���������� ������������ ���������
		* @param capacity �������� ����������� ������� (�� ��������� = count, capacity >= count)
		*/
		void _set_moved_items(T* items, size_t moving, size_t capacity = 0);

		/**
		* @brief ������������ ������ � ����������� ������������ ������
		* @param capacity ������ ���������� ��������� ��� ��������� ������� �������
		* @return ������ ���������� ��������� ��� ������ ������� �������
		*/
		size_t _resize(size_t capacity);

		/**
		* @brief �������� �������������� ���� ������ � ����������� ������
		* @return ������ ���������� ��������� ��� ������ ������� �������
		*/
		size_t _add_block();

		/**
		* @brief ������� ���� ���� ������ � ����������� ������������ ������
		* @return ������ ���������� ��������� ��� ������ ������� �������
		*/
		size_t _remove_block();

		/**
		* @brief �������, ���������������� ������ �� ������������ �������
		* @param static_arr ������ (�����������)
		*/
		void _set_items(T (&static_arr)[]);

	public:

		/**
		* @brief ������������ �� ��������� (������ ������)
		*/
		vector() {}

		/**
		* @brief ����������� �� ������������ ������� (�������� ��������)
		* @param static_arr ����������� ������
		*/
		vector(T (&static_arr)[]);

		/**
		* @brief ����������� �� ������������� ������� (���������� �������� �� �������)
		* @param items ������������ ������
		* @param moving ���������� ������������ ���������
		*/
		vector(T* items, size_t moving);

		/**
		* @brief ���������� �����������
		* @param src ������ �� ���������� ������
		*/
		vector(const vector& src);

		/**
		* @brief ������������ �����������
		* @param src ������ �� ������������ ������
		*/
		vector(vector&& src);

		/**
		* @brief ����������
		*/
		~vector();

		/**
		* @brief �������� ������������ �� ������������ �������
		* @param static_arr ����������� ������
		* @return ������ �� ������������ ������
		*/
		vector& operator= (T (&static_arr)[]);

		/**
		* @brief ���������� �������� ������������
		* @param src ������ �� ���������� ������
		* @return ������ �� ������������� ������
		*/
		vector& operator= (const vector& src);

		/**
		* @brief ������������ �������� ������������
		* @param src ������ �� ������������ ������
		* @return ������ �� ������������ ������
		*/
		vector& operator= (vector&& src);

		/**
		* @brief ������ ������� �������
		* @return ���������� ��������� � �������
		*/
		size_t size() const;

		/**
		* @brief ������ ����������� �������
		* @return ����������� ��������� ���������� ��������� � ������� �� ������ ������
		*/
		size_t capacity() const;

		/**
		* @brief ���������� ������� ���������� �������� � ����� �������
		* @param value ����������� �������
		*/
		void push_back(const T& value);

		/**
		* @brief ������������ ������� ���������� �������� � ����� �������
		* @param value ����������� �������
		*/
		void push_back(T&& value);

		/**
		* @brief �������� ���������� ��������
		*/
		//void pop_back(); // �� ������������

		/**
		* @brief ������� ������
		*/
		void clear();

		/**
		* @brief �������� ��������������
		* @param ������ ��������
		* @return ������ �� �������
		*/
		T& operator[] (int id) const;

		/**
		* @brief ����������� �������� (��� ������������� ������ �������� ��������)
		*/
		typedef vector_const_it<T> const_iterator;

		/**
		* @brief ������������� �������� (��� ������������� ����� �������� ��������)
		*/
		typedef vector_it<T> iterator;

		/**
		* @brief ������� ��������, ����������� �� ������ ������� �������
		* @return ��������
		*/
		iterator begin() const;

		/**
		* @brief ������� ��������, ����������� �� ������ �������
		* @return ��������
		*/
		iterator end() const;

		/**
		* @brief ������� ����������� ��������, ����������� �� ������ ������� �������
		* @return ��������
		*/
		const_iterator cbegin() const;

		/**
		* @brief ������� ����������� ��������, ����������� �� ������ �������
		* @return ��������
		*/
		const_iterator cend() const;
		
		/**
		* @brief ��������� ����� �������� �� ���������
		* @param position ��������
		* @param value ������ �� ����������� �������
		* @return �������� �� ����������� �������
		*/
		iterator insert(const const_iterator position, const T& value);

		/**
		* @brief ��������� ������� �� ���������
		* @param position ��������
		* @param value ������ �� ����������� �������
		* @return �������� �� ����������� �������
		*/
		iterator insert(const const_iterator position, T&& value);

		/**
		* @brief ������� ������� �� ������� �� ���������
		* @param position ��������
		* @return �������� �� ��������� �������
		*/
		iterator erase(const const_iterator position);
	};

}

