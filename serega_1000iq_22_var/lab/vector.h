#pragma once

#include <iostream>
#include <limits>

#ifndef QUANTITY
#define QUANTITY 100
#endif // !QUANTITY

#ifndef INT_MIN
#define INT_MIN -2147483648
#endif // !INT_MIN


namespace my_vector
{
	// вектор
	class vector
	{
		// перегрузка оператора вывода в stdout
		friend std::ostream& operator<<(std::ostream& out, const vector& vec);
		// перегрузка оператора ввода из stdin (для завершения ввода нужно ввести "не число")
		friend std::istream& operator>>(std::istream& in, vector& vec);

		// перегрузка оператора сложения для двух векторов
		friend vector operator+ (const vector& left, const vector& right);
		// перегрузка оператора вычитания для двух векторов
		friend vector operator- (const vector& left, const vector& right);

	private:

		static const int _quantity = QUANTITY;	// предельный размер вектора
		int _size = 0;							// текущий размер вектора
		int _vector[_quantity] = { 0 };			// массив целых чисел (вектор)

		// копирует size элементов массива arr[] и вставляет их в конец текущего вектора
		void _copy_arr(int size, const int arr[]);
		// копирует size элементов массива arr[], встраивает их в конец текущего вектора и зануляет arr[] (типа перемещает)
		void _move_arr(int size, int arr[]);

	public:
		
		// конструктор по умолчанию (пустой вектор)
		vector() {}
		// конструктор по значению первого элемента
		vector(int item);
		// конструктор по размеру и значениям вектора
		vector(int size, const int vector[]);

		// копирующий конструктор
		vector(const vector& src);
		// перемещающий конструктор
		vector(vector&& src);

		// перегрузка копирующего оператора присваивания
		vector& operator=(const vector& src);
		// перегрузка перемещающего оператора присваивания
		vector& operator=(vector&& src);

		// возвращает текущий размер вектора
		int size() const { return _size; }
		// возвращает предельный размер вектора
		int quantity() const { return _quantity; }

		// создает новый вектор по части данного (параметры: индекс первого элемента и длина вектора)
		vector extract(int first_item, int size) const;

		// вставляет новый элемент в конец вектора (если вектор не переполнен)
		void insert(int item);
		// вставляет новый элемент в вектор по заданной позиции (если вектор не переполнен)
		void insert(int item, int position);

		// сортирует элементы вектора по возрастанию
		void sort();

		// находит максимальный элемент в векторе
		int get_max() const;
	};
}


