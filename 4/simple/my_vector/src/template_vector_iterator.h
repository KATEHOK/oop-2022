#pragma once

#define ITERATOR_DECLARATION

#ifndef VECTOR
#include "vector.h"
#endif // !VECTOR

namespace my_template {

	/**
	* @brief ����������� �������� (��� ������������� ������ �������� ��������)
	*/
	template<typename T>
	class vector_const_it
	{

	protected:

		//! @brief ��������� �� ������ - ������ ���������
		T* _owner = nullptr;

		//! @brief ������ �������� (��� end(), cend() ����� vector.size) 
		size_t _id = 0;

		/**
		* @brief ����������� �� ��������� (������ �� ���������)
		*/
		vector_const_it() {}

		/**
		* @brief ����������� �� ��������� �����
		* @param owner ������ �� ������ - ������
		* @param id ������ ��������
		*/
		vector_const_it(vector<T>& owner, size_t id = 0) : _owner(owner), _id(id) {}

	public:

		/**
		* @brief ���������� �����������
		* @param src ������ �� ���������� ��������
		*/
		vector_const_it(const vector_const_it& src) : _owner(src._owner), _id(src._id) {}

		/**
		* @brief ������������ �����������
		* @param src ������ �� ������������ ��������
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
		* @brief ���������� �������� ������������
		* @param src ������ �� ���������� ��������
		* @return ������ �� ������������� ��������
		*/
		vector_const_it& operator= (const vector_const_it& src)
		{
			_owner = src._owner;
			_id = src._id;
			return *this;
		}

		/**
		* @brief ������������ �������� ������������
		* @param src ������ �� ������������ ��������
		* @return ������ �� ������������ ��������
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
		* @brief �������� ��������� ���� ���������� ������ �������
		* @param other ������ �� ��������, � ������� ���������� ���������
		* @return true � ������ ��������� ��������, false � ������ �� ��������
		* (����������� ����������, ���� ������ �������)
		*/
		bool operator== (const vector_const_it& other) const
		{
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id == other._id;
		}

		/**
		* @brief �������� ��������� ���� ���������� ������ �������
		* @param other ������ �� ��������, � ������� ���������� ���������
		* @return true � ������ �������� ��������, false � ������ �� ���������
		* (����������� ����������, ���� ������ �������)
		*/
		bool operator!= (const vector_const_it& other) const
		{
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id != other._id;
		}

		/**
		* @brief �������� ��������� ���� ���������� ������ �������
		* @param other ������ �� ��������, � ������� ���������� ���������
		* @return true ���� ������ ������ �������� ������ ������� �������,
		* false � ��������� ������
		* (����������� ����������, ���� ������ �������)
		*/
		bool operator< (const vector_const_it& other) const
		{
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id < other._id;
		}

		/**
		* @brief �������� ��������� ���� ���������� ������ �������
		* @param other ������ �� ��������, � ������� ���������� ���������
		* @return true ���� ������ ������ �������� ������ ������� �������,
		* false � ��������� ������
		* (����������� ����������, ���� ������ �������)
		*/
		bool operator> (const vector_const_it& other) const
		{
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id > other._id;
		}

		/**
		* @brief �������� ��������� ���� ���������� ������ �������
		* @param other ������ �� ��������, � ������� ���������� ���������
		* @return true ���� ������ ������ �������� ������ ��� ����� ������� �������,
		* false � ��������� ������
		* (����������� ����������, ���� ������ �������)
		*/
		bool operator<= (const vector_const_it& other) const
		{
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id <= other._id;
		}

		/**
		* @brief �������� ��������� ���� ���������� ������ �������
		* @param other ������ �� ��������, � ������� ���������� ���������
		* @return true ���� ������ ������ �������� ������ ��� ����� ������� �������,
		* false � ��������� ������
		* (����������� ����������, ���� ������ �������)
		*/
		bool operator>= (const vector_const_it& other) const
		{
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id >= other._id;
		}

		/**
		* @brief �������� �������������
		* @return ����������� ������ �� �������
		*/
		const T& operator* () const
		{
			if (_id >= _owner->_size) throw std::out_of_range("Iterator points outside the vector");
			return _owner->_items[_id];
		}

		/**
		* @brief ����������� ���������
		* @return ����������� ��������
		*/
		vector_const_it& operator++ ()
		{
			vector_const_it copy(*this);
			if (_id < _owner->_size) _id++;
			return copy;
		}

		/**
		* @brief ����������� ���������
		* @return ����������� ��������
		*/
		vector_const_it& operator-- ()
		{
			vector_const_it copy(*this);
			if (_id > 0) _id--;
			return copy;
		}

		/**
		* @brief ���������� ���������
		* @return ����������� ��������
		*/
		vector_const_it& operator++ (int value)
		{
			if (_id < _owner->_size) _id++;
			return *this;
		}

		/**
		* @brief ���������� ���������
		* @return ����������� ��������
		*/
		vector_const_it& operator-- (int value)
		{
			if (_id > 0) _id--;
			return *this;
		}

		/**
		* @brief �������� ���������� ��������� �� ����� �������
		* @param value �������� ��������
		* @return ��������� ��������
		*/
		vector_const_it& operator+= (int value)
		{
			for (int i = 0; i < value; ++i) ++(*this);
			return *this;
		}

		/**
		* @brief �������� ���������� ��������� �� ����� �������
		* @param value �������� ��������
		* @return ��������� ��������
		*/
		vector_const_it& operator-= (int value)
		{
			for (int i = 0; i < value; ++i) --(*this);
			return *this;
		}

		/**
		* @brief �������� ���������� ��������� �� ������ ��������
		* @param other ������ ��������
		* @return ��������� ��������
		*/
		vector_const_it& operator+= (const vector_const_it& other)
		{
			if (_owner != other._owner) 
				throw std::exception("Cannot aperate with diferent vectors iterators");
			for (int i = 0; i < other._id; ++i) ++(*this);
			return *this;
		}

		/**
		* @brief �������� ���������� ��������� �� ������ ��������
		* @param other ������ ��������
		* @return ��������� ��������
		*/
		vector_const_it& operator-= (const vector_const_it& other)
		{
			if (_owner != other._owner)
				throw std::exception("Cannot aperate with diferent vectors iterators");
			for (int i = 0; i < other._id; ++i) --(*this);
			return *this;
		}

		/**
		* @brief �������� �������� ��������� � ������ �����
		* @param it ������ �� ��������
		* @param value �����
		* @return ����� ��������, ����������� �� �������, ��������� �� value ������� ������������ it
		*/
		friend vector_const_it operator+ (const vector_const_it& it, int value)
		{
			vector_const_it result(it);
			it += value;
			return result;
		}

		/**
		* @brief �������� �������� ��������� � ������ �����
		* @param value �����
		* @param it ������ �� ��������
		* @return ����� ��������, ����������� �� �������, ��������� �� value ������� ������������ it
		*/
		friend vector_const_it operator+ (int value, const vector_const_it& it)
		{
			vector_const_it result(it);
			it += value;
			return result;
		}

		/**
		* @brief �������� ��������� �� ��������� ������ �����
		* @param it ������ �� ��������
		* @param value �����
		* @param it ������ �� ��������
		* @return ����� ��������, ����������� �� �������, ��������� �� value ������� ������������ it
		*/
		friend vector_const_it operator- (const vector_const_it& it, int value)
		{
			vector_const_it result(it);
			it -= value;
			return result;
		}

		/**
		* @brief �������� ��������� �� ��������� ������ �����
		* @param value �����
		* @param it ������ �� ��������
		* @return ����� ��������, ����������� �� �������, ��������� �� value ������� ������������ it
		*/
		friend vector_const_it operator- (int value, const vector_const_it& it)
		{
			vector_const_it result(it);
			it -= value;
			return result;
		}

		/**
		* @brief �������� �������� ���� ����������
		* @param left ������ �� ����� ��������
		* @param right ������ �� ������ ��������
		* @return ����� ��������, ����������� �� ������� ��� �������� = ����� �������� ���������
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
		* @brief �������� ��������� ������ ��������� �� �������
		* @param left ������ �� ����� ��������
		* @param right ������ �� ������ ��������
		* @return ����� ��������, ����������� �� ������� ��� �������� = �������� �������� ���������
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
	* @brief ������������� �������� (��� ������������� ����� �������� ��������)
	*/
	template<typename T>
	class vector_it : public vector_const_it<T>
	{

	private:

	public:

		/**
		* @brief �������� �������������
		* @return ������ �� ���������� �������
		*/
		T& operator* () const
		{
			if (_id >= _owner->_size) throw std::out_of_range("Iterator points outside the vector");
			return _owner->_items[_id];
		}

		/**
		* @brief ����������� ���������
		* @return ��������
		*/
		vector_it& operator++ ()
		{
			vector_const_it copy(*this);
			if (_id < _owner->_size) _id++;
			return copy;
		}

		/**
		* @brief ����������� ���������
		* @return ��������
		*/
		vector_it& operator-- ()
		{
			vector_const_it copy(*this);
			if (_id > 0) _id--;
			return copy;
		}

		/**
		* @brief ���������� ���������
		* @return ��������
		*/
		vector_it& operator++ (int value)
		{
			if (_id < _owner->_size) _id++;
			return *this;
		}

		/**
		* @brief ���������� ���������
		* @return ��������
		*/
		vector_it& operator-- (int value)
		{
			if (_id > 0) _id--;
			return *this;
		}

		/**
		* @brief �������� ���������� ��������� �� ����� �������
		* @param value �������� ��������
		* @return ��������� ��������
		*/
		vector_it& operator+= (int value)
		{
			for (int i = 0; i < value; ++i) ++(*this);
			return *this;
		}

		/**
		* @brief �������� ���������� ��������� �� ����� �������
		* @param value �������� ��������
		* @return ��������� ��������
		*/
		vector_it& operator-= (int value)
		{
			for (int i = 0; i < value; ++i) --(*this);
			return *this;
		}

		/**
		* @brief �������� ���������� ��������� �� ������ ��������
		* @param other ������ ��������
		* @return ��������� ��������
		*/
		vector_it& operator+= (const vector_const_it& other)
		{
			if (_owner != other._owner)
				throw std::exception("Cannot aperate with diferent vectors iterators");
			for (int i = 0; i < other._id; ++i) ++(*this);
			return *this;
		}

		/**
		* @brief �������� ���������� ��������� �� ������ ��������
		* @param other ������ ��������
		* @return ��������� ��������
		*/
		vector_it& operator-= (const vector_const_it& other)
		{
			if (_owner != other._owner)
				throw std::exception("Cannot aperate with diferent vectors iterators");
			for (int i = 0; i < other._id; ++i) --(*this);
			return *this;
		}

		/**
		* @brief �������� �������� ��������� � ������ �����
		* @param it ������ �� ��������
		* @param value �����
		* @return ����� ��������, ����������� �� �������, ��������� �� value ������� ������������ it
		*/
		friend vector_it operator+ (const vector_const_it& it, int value)
		{
			vector_const_it result(it);
			it += value;
			return result;
		}

		/**
		* @brief �������� �������� ��������� � ������ �����
		* @param value �����
		* @param it ������ �� ��������
		* @return ����� ��������, ����������� �� �������, ��������� �� value ������� ������������ it
		*/
		friend vector_it operator+ (int value, const vector_const_it& it)
		{
			vector_const_it result(it);
			it += value;
			return result;
		}

		/**
		* @brief �������� ��������� �� ��������� ������ �����
		* @param it ������ �� ��������
		* @param value �����
		* @param it ������ �� ��������
		* @return ����� ��������, ����������� �� �������, ��������� �� value ������� ������������ it
		*/
		friend vector_it operator- (const vector_const_it& it, int value)
		{
			vector_const_it result(it);
			it -= value;
			return result;
		}

		/**
		* @brief �������� ��������� �� ��������� ������ �����
		* @param value �����
		* @param it ������ �� ��������
		* @return ����� ��������, ����������� �� �������, ��������� �� value ������� ������������ it
		*/
		friend vector_it operator- (int value, const vector_const_it& it)
		{
			vector_it result(it);
			it -= value;
			return result;
		}

		/**
		* @brief �������� �������� ���� ����������
		* @param left ������ �� ����� ��������
		* @param right ������ �� ������ ��������
		* @return ����� ��������, ����������� �� ������� ��� �������� = ����� �������� ���������
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
		* @brief �������� ��������� ������ ��������� �� �������
		* @param left ������ �� ����� ��������
		* @param right ������ �� ������ ��������
		* @return ����� ��������, ����������� �� ������� ��� �������� = �������� �������� ���������
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
