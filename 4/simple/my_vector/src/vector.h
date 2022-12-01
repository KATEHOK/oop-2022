#pragma once

#define VECTOR

namespace my_template
{
	template<typename T>
	class vector
	{

		class iterator
		{

		private:

			vector& _owner;

			int _id = 0;

		public:

			iterator() {}

			iterator(const iterator& src);

			iterator(iterator&& src);

			~iterator() {}

			iterator& operator= (const iterator& src);

			iterator& operator= (iterator&& src);

			bool operator== (const iterator& other) const;

			bool operator!= (const iterator& other) const;

			bool operator< (const iterator& other) const;

			bool operator> (const iterator& other) const;

			bool operator<= (const iterator& other) const;

			bool operator>= (const iterator& other) const;

			T& operator* () const;

			const T& operator* () const;

			iterator& operator++ ();

			iterator& operator-- ();

			iterator& operator++ (int value);

			iterator& operator-- (int value);

			iterator& operator+= (int value);

			iterator& operator-= (int value);

			friend iterator operator+ (const iterator& it, int value);

			friend iterator operator+ (int value, const iterator& it);

			friend iterator operator- (const iterator& it, int value);

			friend iterator operator- (int value, const iterator& it);
		};

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
		* @brief Создает массив - копию элементов
		* @return Указатель на массив
		*/
		T* _copy_items() const;

		/**
		* @brief Перевыделяет память с сохранением помещающихся данных
		* @param capacity Предел количества элементов для желаемого размера вектора
		* @return Предел количества элементов для нового размера вектора
		*/
		size_t _resize(size_t capacity);

		/**
		* @brief Выделяет дополнительный блок памяти с сохранением данных
		* @return Предел количества элементов для нового размера вектора
		*/
		size_t _add_block();

		/**
		* @brief Очищает один блок памяти с сохранением помещающихся данных
		* @return Предел количества элементов для нового размера вектора
		*/
		size_t _remove_block();

	public:

		vector();

		vector(const vector& src);

		vector(vector&& src);

		~vector();

		vector& operator= (const vector& src);

		vector& operator= (vector&& src);

		size_t size() const;

		size_t capacity() const;

		void push_back(const T& value);

		void push_back(T&& value);

		void pop_back();

		void clear();

		T& operator[] (int id) const;

		const T& operator[] (int id) const;

		iterator begin() const;

		iterator end() const;

		const iterator cbegin() const;

		const iterator cend() const;
		
		iterator insert(const iterator position, const T& value);

		iterator insert(const iterator position, T&& value);

		iterator erase(const iterator position);
	};
}

