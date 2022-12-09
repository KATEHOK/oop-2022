#pragma once

#ifndef VECTOR
#include "vector.h"
#endif // !VECTOR

namespace my_template {

	/**
	* @brief ������� ������ ������ ��������� ��� �������
	*/
	template<class T, class returnedT>
	class vector_iterator
	{

		friend class vector<T>;

	protected:

		//! @brief ��������� �� ������ - ������ ���������
		vector<T>* _owner = nullptr;

		//! @brief ������ �������� (��� end(), cend() ����� vector.size) 
		size_t _id = 0;

		/**
		* @brief ����������� �� ��������� (������ �� ���������)
		*/
		vector_iterator() {}

		/**
		* @brief ����������� �� ��������� �����
		* @param owner ��������� �� ������ - ������
		* @param id ������ ��������
		*/
		vector_iterator(const vector<T>* owner, size_t id = 0) :
			_owner(const_cast<vector<T>*>(owner)), _id(id) {}

		/**
		* @brief ���������� �����������
		* @param src ������ �� ���������� ��������
		*/
		vector_iterator(const vector_iterator& src) : _owner(src._owner), _id(src._id) {}

		/**
		* @brief ������������ �����������
		* @param src ������ �� ������������ ��������
		*/
		vector_iterator(vector_iterator&& src) : _owner(src._owner), _id(src._id)
		{
			if (this != &src)
			{
				src._owner = nullptr;
				src._id = 0;
			}
		}

	public:

		/**
		* @brief ���������� �������� ������������
		* @param src ������ �� ���������� ��������
		* @return ������ �� ������������� ��������
		*/
		vector_iterator& operator= (const vector_iterator& src)
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
		vector_iterator& operator= (vector_iterator&& src)
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
		* @brief �������� �������������
		* @return C����� �� ������� (�������������, ���� returnedT == const T)
		*/
		returnedT& operator* () const
		{
			if (_id >= _owner->_size)
				throw std::out_of_range("Iterator points outside the vector");
			return _owner->_items[_id];
		}

		/**
		* @brief ������ ������� ��������
		* @return ������ ��������
		*/
		size_t id() const
		{
			return _id;
		}

		/**
		* @brief �������� ��������� ���� ���������� ������ �������
		* @param other ������ �� ��������, � ������� ���������� ���������
		* @return true � ������ ��������� ��������, false � ������ �� ��������
		* (����������� ����������, ���� ������ �������)
		*/
		bool operator== (const vector_iterator& other) const
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
		bool operator!= (const vector_iterator& other) const
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
		bool operator< (const vector_iterator& other) const
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
		bool operator> (const vector_iterator& other) const
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
		bool operator<= (const vector_iterator& other) const
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
		bool operator>= (const vector_iterator& other) const
		{
			if (_owner != other._owner)
				throw std::exception("Cannot compare iterators of different vectors");
			return _id >= other._id;
		}

		/**
		* @brief ����������� ���������
		* @return ��������
		*/
		vector_iterator operator++ (int value)
		{
			vector_iterator copy(*this);
			if (_id < _owner->_size) _id++;
			return copy;
		}

		/**
		* @brief ����������� ���������
		* @return ��������
		*/
		vector_iterator operator-- (int value)
		{
			vector_iterator copy(*this);
			if (_id > 0) _id--;
			return copy;
		}

		/**
		* @brief ���������� ���������
		* @return ��������
		*/
		vector_iterator& operator++ ()
		{
			if (_id < _owner->_size) _id++;
			return *this;
		}

		/**
		* @brief ���������� ���������
		* @return ��������
		*/
		vector_iterator& operator-- ()
		{
			if (_id > 0) _id--;
			return *this;
		}

		/**
		* @brief �������� ���������� ��������� �� ����� �������
		* @param value �������� ��������
		* @return ��������� ��������
		*/
		vector_iterator& operator+= (int value)
		{
			for (int i = 0; i < value; ++i) ++(*this);
			return *this;
		}

		/**
		* @brief �������� ���������� ��������� �� ����� �������
		* @param value �������� ��������
		* @return ��������� ��������
		*/
		vector_iterator& operator-= (int value)
		{
			for (int i = 0; i < value; ++i) --(*this);
			return *this;
		}

		/**
		* @brief �������� ���������� ��������� �� ������ ��������
		* @param other ������ ��������
		* @return ��������� ��������
		*/
		vector_iterator& operator+= (const vector_iterator& other)
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
		vector_iterator& operator-= (const vector_iterator& other)
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
		friend vector_iterator operator+ (const vector_iterator& it, int value)
		{
			vector_iterator result(it);
			result += value;
			return result;
		}

		/**
		* @brief �������� �������� ��������� � ������ �����
		* @param value �����
		* @param it ������ �� ��������
		* @return ����� ��������, ����������� �� �������, ��������� �� value ������� ������������ it
		*/
		friend vector_iterator operator+ (int value, const vector_iterator& it)
		{
			vector_iterator result(it);
			result += value;
			return result;
		}

		/**
		* @brief �������� ��������� �� ��������� ������ �����
		* @param it ������ �� ��������
		* @param value �����
		* @param it ������ �� ��������
		* @return ����� ��������, ����������� �� �������, ��������� �� value ������� ������������ it
		*/
		friend vector_iterator operator- (const vector_iterator& it, int value)
		{
			vector_iterator result(it);
			result -= value;
			return result;
		}

		/**
		* @brief �������� ��������� �� ��������� ������ �����
		* @param value �����
		* @param it ������ �� ��������
		* @return ����� ��������, ����������� �� �������, ��������� �� value ������� ������������ it
		*/
		friend vector_iterator operator- (int value, const vector_iterator& it)
		{
			vector_iterator result(it);
			result -= value;
			return result;
		}

		/**
		* @brief �������� �������� ���� ����������
		* @param left ������ �� ����� ��������
		* @param right ������ �� ������ ��������
		* @return ����� ��������, ����������� �� ������� ��� �������� = ����� �������� ���������
		*/
		friend vector_iterator operator+ (
			const vector_iterator& left,
			const vector_iterator& right)
		{
			vector_iterator result(left);
			result += right;
			return result;
		}

		/**
		* @brief �������� ��������� ������ ��������� �� �������
		* @param left ������ �� ����� ��������
		* @param right ������ �� ������ ��������
		* @return ����� ��������, ����������� �� ������� ��� �������� = �������� �������� ���������
		*/
		friend vector_iterator operator- (
			const vector_iterator& left,
			const vector_iterator& right)
		{
			vector_iterator result(left);
			result -= right;
			return result;
		}

	};

	/**
	* @brief ������ �������������� ���������
	*/
	template<class T>
	class vector_it : public vector_iterator<T, T> {

		friend class vector<T>;
		friend class vector_const_it<T>;

	private:

		/**
		* @brief ����������� �� ��������� (������ �� ���������)
		*/
		vector_it() : vector_iterator<T, T>() {}

		/**
		* @brief ����������� �� ��������� �����
		* @param owner ��������� �� ������ - ������
		* @param id ������ ��������
		*/
		vector_it(const vector<T>* owner, size_t id) :
			vector_iterator<T, T>(owner, id) {}

	public:

		/**
		* @brief ���������� �����������
		* @param src ������ �� ���������� ��������
		*/
		vector_it(const vector_iterator<T, T>& src) : vector_iterator<T, T>(src) {}

		/**
		* @brief ������������ �����������
		* @param src ������ �� ������������ ��������
		*/
		vector_it(vector_iterator<T, T>&& src) : vector_iterator<T, T>(src) {}

		/**
		* @brief ���������� ������������� nullptr ��� ��������� �� ������� � 0 ��� _id
		*/
		~vector_it()
		{
			this->_id = 0;
			this->_owner = nullptr;
		}

	};

	/**
	* @brief ������ ������������ ���������
	*/
	template<class T>
	class vector_const_it : public vector_iterator<T, const T> {

		friend class vector<T>;

	private:

		/**
		* @brief ����������� �� ��������� (������ �� ���������)
		*/
		vector_const_it() : vector_iterator<T, const T>() {}

		/**
		* @brief ����������� �� ��������� �����
		* @param owner ��������� �� ������ - ������
		* @param id ������ ��������
		*/
		vector_const_it(const vector<T>* owner, size_t id) :
			vector_iterator<T, const T>(owner, id) {}

	public:

		/**
		* @brief ���������� �����������
		* @param src ������ �� ���������� ��������
		*/
		vector_const_it(const vector_iterator<T, const T>& src) : vector_iterator<T, const T>(src) {}

		/**
		* @brief ������������ �����������
		* @param src ������ �� ������������ ��������
		*/
		vector_const_it(vector_iterator<T, const T>&& src) : vector_iterator<T, const T>(src) {}

		/**
		* @brief ���������� ������������� nullptr ��� ��������� �� ������� � 0 ��� _id
		*/
		~vector_const_it()
		{
			this->_id = 0;
			this->_owner = nullptr;
		}

		/**
		* @brief ���������� ����������� �� ������ �������������� ���������
		* @param src ������ �� ������������� ��������
		*/
		vector_const_it(const vector_it<T>& src) 
		{
			this->_owner = src._owner;
			this->_id = src._id;
		}

		/**
		* @brief ������������ ����������� �� ������ �������������� ���������
		* @param src ������ �� ������������� ��������
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
			return *this;
		}

	};


}
