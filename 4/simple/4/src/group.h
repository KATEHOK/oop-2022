#pragma once

#ifndef SAME
#include "same.h"
#endif // !SAME

#define GROUP

namespace group {

	/**
	* @brief Абстрактный класс, описывающий группу
	*/
	class Group {

		friend class GroupsTableItem;
		friend class GroupsTable;

	protected:

		//! @brief Номер группы (уникален в рамках одной таблицы)
		int _id = 0;

		//! @brief Количество студентов группы
		size_t _size = 0;

		//! @brief Номер профилирующей кафедры
		int _department_id = 0;

		//! @brief Срок обучения
		int _study_duration = 0;

		/**
		* @brief Функция вывода абстрактной группы в стандартный поток вывода
		* @param out Ссылка на стандартный поток вывода
		*/
		void out(std::ostream& out) const;

		/**
		* @brief Копирует параметры абстрактной группы
		* @param src Ссылка на объект с которого копируются параметры
		*/
		void copy_from(const Group& src);

		/**
		* @brief Перемещает параметры абстрактной группы
		* @param src Ссылка на объект с которого перемещаются параметры
		*/
		void move_from(Group&& src);

		/**
		* @brief Для перегрузки вывода в выходной поток по указателю базового класса
		*/
		virtual void output() const {}

	public:

		/**
		* @brief Конструктор по умолчанию (везде нули)
		*/
		Group() {}

		/**
		* @brief Конструктор по значениям полей
		* @param id Номер группы
		* @param size Количество студентов группы
		* @param department_id Номер профилирующей кафедры
		* @param study_duration Срок обучения
		*/
		Group(int id, int size, int department_id, int study_duration) :
			_id(id),
			_size(size),
			_department_id(department_id),
			_study_duration(study_duration) {}

		/**
		* @brief Копирующий конструктор
		* @param src Ссылка на копируемый объект абстрактной группы
		*/
		Group(const Group& src);

		/**
		* @brief Перемещающий конструктор
		* @param src Ссылка на перемещаемый объект абстрактной группы
		*/
		Group(Group&& src);

		/**
		* @brief Геттер номера группы
		* @return Номер группы
		*/
		int id() const;

		/**
		* @brief Геттер количества студентов группы
		* @return Количество студентов группы
		*/
		size_t size() const;

		/**
		* @brief Сеттер количества студентов группы
		* @param size Новое количество студентов группы
		* @return Количество студентов группы
		*/
		size_t size(size_t size);

		/**
		* @brief Геттер номера профилирующей кафедры
		* @return Номер профилирующей кафедры
		*/
		int department_id() const;

		/**
		* @brief Геттер срока обучения
		* @return Срок обучения
		*/
		int study_duration() const;

		friend std::ostream& operator<< (std::ostream& out, const Group& group);

	};

	/**
	* @brief Класс дневной группы
	*/
	class DayGroup : public Group {
	private:

		//! @brief Специализация группы
		std::string _specialization = "";

		//! @brief Размер стипендии в группе
		float _stipend = 0;

		//! @brief Количество стипендиатов в группе
		int _fellows_amount = 0;

		/**
		* @brief Копирует параметры группы
		* @param src Ссылка на объект с которого копируются параметры
		*/
		void copy_from(const DayGroup& src);

		/**
		* @brief Перемещает параметры группы
		* @param src Ссылка на объект с которого перемещаются параметры
		*/
		void move_from(DayGroup&& src);

		virtual void output() const {
			std::cout << *this;
		}

	public:

		/**
		* @brief Конструктор по умолчанию (везде нули)
		*/
		DayGroup() : Group() {}

		/**
		* @brief Конструктор по значениям полей
		* @param id Номер группы
		* @param size Количество студентов группы
		* @param department_id Номер профилирующей кафедры
		* @param study_duration Срок обучения
		* @param specialization Специализация группы
		* @param stipend Размер стипендии в группе
		* @param fellows_amount Количество стипендиатов в группе
		*/
		DayGroup(int id, int size, int department_id, int study_duration,
			std::string specialization, float stipend, int fellows_amount) :
			Group(id, size, department_id, study_duration),
			_specialization(specialization),
			_stipend(stipend),
			_fellows_amount(fellows_amount) {}

		/**
		* @brief Копирующий конструктор
		* @param src Ссылка на копируемый объект группы
		*/
		DayGroup(const DayGroup& src);

		/**
		* @brief Перемещающий конструктор
		* @param src Ссылка на перемещаемый объект группы
		*/
		DayGroup(DayGroup&& src);

		/**
		* @brief Копирующий оператор присваивания
		* @param src Ссылка на копируемый объект группы
		* @return Ссылка на скопированный объект
		*/
		DayGroup& operator= (const DayGroup& src);

		/**
		* @brief Перемещающий оператор присваивания
		* @param src Ссылка на перемещаемый объект группы
		* @return Ссылка на перемещенный объект
		*/
		DayGroup& operator= (DayGroup&& src);

		/**
		* @brief Геттер специализации
		* @return Специализация
		*/
		std::string specialization() const;

		/**
		* @brief Геттер размера стипендии
		* @return Размер стипендии
		*/
		float stipend() const;

		/**
		* @brief Сеттер размера стипендии
		* @param stipend размер стипендии
		* @return Размер стипендии
		*/
		float stipend(float stipend);

		/**
		* @brief Геттер количества стипендиатов
		* @return Количество стипендиатов
		*/
		int fellows_amount() const;

		/**
		* @brief Сеттер количества стипендиатов
		* @param Количество стипендиатов
		* @return Количество стипендиатов
		*/
		int fellows_amount(int amount);

		/**
		* @brief Дружественный оператор вывода дневной группы в стандартный поток вывода
		* @param out Ссылка на стандартный поток вывода
		* @param dg Ссылка на объект дневной группы
		* @return Ссылка на стандартный поток вывода
		*/
		friend std::ostream& operator<< (std::ostream& out, const DayGroup& dg);
	};

	/**
	* @brief Класс вечерней группы
	*/
	class EveningGroup : public Group {
	private:

		//! @brief Контингент
		std::string _contingent = "";

		//! @brief Квалификация
		std::string _qualification = "";

		/**
		* @brief Копирует параметры группы
		* @param src Ссылка на объект с которого копируются параметры
		*/
		void copy_from(const EveningGroup& src);

		/**
		* @brief Перемещает параметры группы
		* @param src Ссылка на объект с которого перемещаются параметры
		*/
		void move_from(EveningGroup&& src);

		virtual void output() const {
			std::cout << *this;
		}

	public:

		/**
		* @brief Конструктор по умолчанию (везде нули)
		*/
		EveningGroup() : Group() {}

		/**
		* @brief Конструктор по значениям полей
		* @param id Номер группы
		* @param size Количество студентов группы
		* @param department_id Номер профилирующей кафедры
		* @param study_duration Срок обучения
		* @param contingent Контингент группы
		* @param qualification Квалификация группы
		*/
		EveningGroup(int id, int size, int department_id, int study_duration,
			std::string contingent, std::string qualification) :
			Group(id, size, department_id, study_duration),
			_contingent(contingent),
			_qualification(qualification) {}

		/**
		* @brief Копирующий конструктор
		* @param src Ссылка на копируемый объект группы
		*/
		EveningGroup(const EveningGroup& src);

		/**
		* @brief Перемещающий конструктор
		* @param src Ссылка на перемещаемый объект группы
		*/
		EveningGroup(EveningGroup&& src);

		/**
		* @brief Копирующий оператор присваивания
		* @param src Ссылка на копируемый объект группы
		* @return Ссылка на скопированный объект
		*/
		EveningGroup& operator= (const EveningGroup& src);

		/**
		* @brief Перемещающий оператор присваивания
		* @param src Ссылка на перемещаемый объект группы
		* @return Ссылка на перемещенный объект
		*/
		EveningGroup& operator= (EveningGroup&& src);

		/**
		* @brief Геттер контингента
		* @return Контингент
		*/
		std::string contingent() const;

		/**
		* @brief Геттер квалификации
		* @return Квалификация
		*/
		std::string qualification() const;

		/**
		* @brief Дружественный оператор вывода вечерней группы в стандартный поток вывода
		* @param out Ссылка на стандартный поток вывода
		* @param eg Ссылка на объект вечерней группы
		* @return Ссылка на стандартный поток вывода
		*/
		friend std::ostream& operator<< (std::ostream& out, const EveningGroup& eg);
	};

	/**
	* @brief Класс платной группы
	*/
	class PaidGroup : public Group {
	private:

		//! @brief Номер контракта
		int _contract_id = 0;

		//! @brief Размер оплаты
		float _payment_size = 0;

		/**
		* @brief Копирует параметры группы
		* @param src Ссылка на объект с которого копируются параметры
		*/
		void copy_from(const PaidGroup& src);

		/**
		* @brief Перемещает параметры группы
		* @param src Ссылка на объект с которого перемещаются параметры
		*/
		void move_from(PaidGroup&& src);

		virtual void output() const {
			std::cout << *this;
		}

	public:

		/**
		* @brief Конструктор по умолчанию (везде нули)
		*/
		PaidGroup() : Group() {}

		/**
		* @brief Конструктор по значениям полей
		* @param id Номер группы
		* @param size Количество студентов группы
		* @param department_id Номер профилирующей кафедры
		* @param study_duration Срок обучения
		* @param contract_id Номер контракта
		* @param payment_size Размер оплаты
		*/
		PaidGroup(int id, int size, int department_id, int study_duration,
			int contract_id, float payment_size) :
			Group(id, size, department_id, study_duration),
			_contract_id(contract_id),
			_payment_size(payment_size) {}

		/**
		* @brief Копирующий конструктор
		* @param src Ссылка на копируемый объект группы
		*/
		PaidGroup(const PaidGroup& src);

		/**
		* @brief Перемещающий конструктор
		* @param src Ссылка на перемещаемый объект группы
		*/
		PaidGroup(PaidGroup&& src);

		/**
		* @brief Копирующий оператор присваивания
		* @param src Ссылка на копируемый объект группы
		* @return Ссылка на скопированный объект
		*/
		PaidGroup& operator= (const PaidGroup& src);

		/**
		* @brief Перемещающий оператор присваивания
		* @param src Ссылка на перемещаемый объект группы
		* @return Ссылка на перемещенный объект
		*/
		PaidGroup& operator= (PaidGroup&& src);

		/**
		* @brief Геттер номера контракта
		* @return Номер контракта
		*/
		int contract_id() const;

		/**
		* @brief Геттер размера оплаты
		* @return Размер оплаты
		*/
		float payment_size() const;

		/**
		* @brief Сеттер размера оплаты
		* @param payment_size Новое значение размера оплаты
		* @return Размер оплаты
		*/
		float payment_size(float payment_size);

		/**
		* @brief Дружественный оператор вывода платной группы в стандартный поток вывода
		* @param out Ссылка на стандартный поток вывода
		* @param pg Ссылка на объект платной группы
		* @return Ссылка на стандартный поток вывода
		*/
		friend std::ostream& operator<< (std::ostream& out, const PaidGroup& pg);
	};
}
