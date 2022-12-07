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

		//! @brief Массив элементов типа T
		T* _items = nullptr;

		//! @brief Количество элементов
		size_t _size = 0;

		//! @brirf Предел количества элементов для текущего размера вектора
		size_t _capacity = 0;

		//! @brief Количество элементов, под которое за раз выделяется память
		static const size_t _block = 10;

		/**
		* @brief Шаблон статической функции, определяющей размер статического массива
		* @param Статический массив
		* @return Количество элементов массива
		*/
		template<size_t N>
		size_t _get_static_array_size(T(&)[N]) const
		{
			return N;
		}

		/**
		* @brief Создает массив - копию элементов вектора
		* @param max_count Максимальное количество элементов, которое нужно скопировать
		* @return Указатель на массив
		*/
		T* _get_items(size_t max_count) const;

		/**
		* @brief Функция инициализирует вектор, перемещая элементы динамического массива
		* (только для изначально пустого вектора)
		* @param items Массив (динамический)
		* @param moving Количество перемещаемых элементов
		* @param capacity Желаемая вместимость вектора (по умолчанию = count, capacity >= count)
		*/
		void _set_moved_items(T* items, size_t moving, size_t capacity = 0);

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

		/**
		* @brief Функция, инициализирующая вектор по статическому массиву
		* @param static_arr Массив (статический)
		*/
		void _set_items(T (&static_arr)[]);

	public:

		/**
		* @brief Консттруктор по умолчанию (пустой вектор)
		*/
		vector() {}

		/**
		* @brief Конструктор по статическому массиву (копирует элементы)
		* @param static_arr Статический массив
		*/
		vector(T (&static_arr)[]);

		/**
		* @brief Конструктор по динамическому массиву (перемещает элементы из массива)
		* @param items Динамический массив
		* @param moving Количество перемещаемых элементов
		*/
		vector(T* items, size_t moving);

		/**
		* @brief Копирующий конструктор
		* @param src Ссылка на копируемый вектор
		*/
		vector(const vector& src);

		/**
		* @brief Перемещающий конструктор
		* @param src Ссылка на перемещаемый вектор
		*/
		vector(vector&& src);

		/**
		* @brief Деструктор
		*/
		~vector();

		/**
		* @brief Оператор присваивания по статическому массиву
		* @param static_arr Статический массив
		* @return Ссылка на получившийся вектор
		*/
		vector& operator= (T (&static_arr)[]);

		/**
		* @brief Копирующий оператор присваивания
		* @param src Ссылка на копируемый вектор
		* @return Ссылка на скопированный вектор
		*/
		vector& operator= (const vector& src);

		/**
		* @brief Перемещающий оператор присваивания
		* @param src Ссылка на перемещаемый вектор
		* @return Ссылка на перемещенный вектор
		*/
		vector& operator= (vector&& src);

		/**
		* @brief Геттер размера вектора
		* @return Количество элементов в векторе
		*/
		size_t size() const;

		/**
		* @brief Геттер вместимости вектора
		* @return Максимально возможное количество элементов в векторе на данный момент
		*/
		size_t capacity() const;

		/**
		* @brief Копирующая функция добавления элемента в конец вектора
		* @param value Добавляемый элемент
		*/
		void push_back(const T& value);

		/**
		* @brief Перемещающая функция добавления элемента в конец вектора
		* @param value Добавляемый элемент
		*/
		void push_back(T&& value);

		/**
		* @brief Удаление последнего элемента
		*/
		//void pop_back(); // не используется

		/**
		* @brief Очищает вектор
		*/
		void clear();

		/**
		* @brief Оператор индексирования
		* @param Индекс элемента
		* @return Ссылка на элемент
		*/
		T& operator[] (int id) const;

		/**
		* @brief Константный итератор (при разыменовании нельзя изменять адрессат)
		*/
		typedef vector_const_it<T> const_iterator;

		/**
		* @brief Неконстантный итератор (при разыменовании можно изменять адрессат)
		*/
		typedef vector_it<T> iterator;

		/**
		* @brief Создает итератор, указывающий на первый элемент вектора
		* @return Итератор
		*/
		iterator begin() const;

		/**
		* @brief Создает итератор, указывающий за предел вектора
		* @return Итератор
		*/
		iterator end() const;

		/**
		* @brief Создает константный итератор, указывающий на первый элемент вектора
		* @return Итератор
		*/
		const_iterator cbegin() const;

		/**
		* @brief Создает константный итератор, указывающий за предел вектора
		* @return Итератор
		*/
		const_iterator cend() const;
		
		/**
		* @brief Вставляет копию элемента по итератору
		* @param position Итератор
		* @param value Ссылка на вставляемый элемент
		* @return Итератор на вставленный элемент
		*/
		iterator insert(const const_iterator position, const T& value);

		/**
		* @brief Вставляет элемент по итератору
		* @param position Итератор
		* @param value Ссылка на вставляемый элемент
		* @return Итератор на вставленный элемент
		*/
		iterator insert(const const_iterator position, T&& value);

		/**
		* @brief Удаляет элемент из вектора по итератору
		* @param position Итератор
		* @return Итератор на удаленный элемент
		*/
		iterator erase(const const_iterator position);
	};

}

