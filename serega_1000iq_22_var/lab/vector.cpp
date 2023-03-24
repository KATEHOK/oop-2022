#include "vector.h"

namespace my_vector
{

	void vector::_copy_arr(int size, const int arr[])
	{
		for (int i = 0; i < size && _size < _quantity; ++i) insert(arr[i]);
	}

	void vector::_move_arr(int size, int arr[])
	{
		for (int i = 0; i < size; ++i) {
			if (_size < _quantity) insert(arr[i]);
			arr[i] = 0;
		}
	}

	vector::vector(int item)
	{
		insert(item);
	}

	vector::vector(int size, const int vector[])
	{
		_copy_arr(size, vector);
	}

	vector::vector(const vector& src)
	{
		if (this != &src) _copy_arr(src._size, src._vector);
	}

	vector::vector(vector&& src)
	{
		if (this != &src) {
			_move_arr(src._size, src._vector);
			src._size = 0;
		}
	}

	vector& vector::operator=(const vector& src)
	{
		if (this != &src) {
			_size = 0;
			_copy_arr(src._size, src._vector);
		}
		return *this;
	}

	vector& vector::operator=(vector&& src)
	{
		if (this != &src) {
			_size = 0;
			_move_arr(src._size, src._vector);
			src._size = 0;
		}
		return *this;
	}

	vector vector::extract(int first_item, int size) const
	{
		vector vec;

		if (first_item + size <= _size) vec._copy_arr(size, _vector + first_item);
		else vec._copy_arr(_size - first_item, _vector + first_item);

		return vec;
	}

	void vector::insert(int item)
	{
		insert(item, _size);
	}

	void vector::insert(int item, int position)
	{
		if (_size == _quantity || position < 0 || position > _size) return;
		for (int i = _size; i > position; --i) _vector[i] = _vector[i - 1];
		_vector[position] = item;
		++_size;
	}

	void vector::sort()
	{
		// http://cppstudio.com/post/891/ - УДАЛИТЬ!!!
		std::qsort(_vector, _size, sizeof(int),
			[](const void* left, const void* right) { return (*(int*)left) - (*(int*)right); }	// лямбда-функция для сравнения чисел
		);
	}

	int vector::get_max() const
	{
		int max = INT_MIN;
		for (int i = 0; i < _size; ++i) if (_vector[i] > max) max = _vector[i];
		return max;
	}

	std::ostream& operator<<(std::ostream& out, const vector& vec)
	{
		out << "{";
		for (int i = 0; i < vec._size; ++i) {
			out << " " << vec._vector[i];
			if (i + 1 < vec._size) out << ",";
		}
		if (vec._size > 0) out << " ";
		out << "}";
		return out;
	}

	std::istream& operator>>(std::istream& in, vector& vec)
	{
		int value;

		while (true) {
			if (vec._size == vec._quantity) break;	// ловим переполнение

			in >> value;
			if (!in.good()) {	// если ошибка ввода
				in.clear();		// возвращаем "нормальный" режим работы
				break;
			}

			vec._vector[vec._size] = value;
			++vec._size;
		}
		// очищаем буфер ввода
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		return in;
	}

	vector operator+(const vector& left, const vector& right)
	{
		int min_size = left._size;
		if (min_size > right._size) min_size = right._size;

		vector vec(left);
		for (int i = 0; i < min_size; ++i) vec._vector[i] += right._vector[i];

		if (right._size > min_size)
			for (int i = min_size; i < right._size; ++i) vec.insert(right._vector[i]);

		return vec;
	}

	vector operator-(const vector& left, const vector& right)
	{
		int min_size = left._size;
		if (min_size > right._size) min_size = right._size;

		vector vec(left);
		for (int i = 0; i < min_size; ++i) vec._vector[i] -= right._vector[i];

		if (right._size > min_size)
			for (int i = min_size; i < right._size; ++i) vec.insert(-right._vector[i]);

		return vec;
	}

}