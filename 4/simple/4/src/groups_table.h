#pragma once

#ifndef SAME
#include "same.h"
#endif // !SAME

#ifndef GROUP
#include "group.h"
#endif // !GROUP

#define GROUPS_TABLE

#include <memory>

namespace group {

	/**
	* @brief Класс элемента таблицы групп
	*/
	class GroupsTableItem {

		friend class GroupsTable;

	private:

		//! @brief Номер группы
		int _group_id = 0;

		//! @brief Указатель на группу
		std::shared_ptr<Group> _group_ptr = nullptr;

	public:

		/**
		* @brief Конструктор по умолчанию (везде нули)
		*/
		GroupsTableItem() {}

		/**
		* @brief Конструктор по значениям полей
		* @param group_id Номер группы
		* @param group_ptr Умный указатель на группу
		*/
		GroupsTableItem(int group_id, std::shared_ptr<Group> group_ptr);

		/**
		* @brief Конструктор по значениям полей
		* @param group_id Номер группы
		* @param group_ptr Стандартный указатель на группу
		*/
		GroupsTableItem(int group_id, Group* group_ptr) :
			GroupsTableItem(group_id, std::shared_ptr<Group>(group_ptr)) {}

		/**
		* @brief Конструктор по одной группе
		* @param group Ссылка на группу
		*/
		GroupsTableItem(Group& group) : GroupsTableItem(group._id, &group) {}

		/**
		* @brief Копирующий конструктор
		* @param src Ссылка на копируемый объект элемента таблицы
		*/
		GroupsTableItem(const GroupsTableItem& src) :
			GroupsTableItem(src._group_id, src._group_ptr) {}

		/**
		* @brief Перемещающий конструктор
		* @param src Ссылка на перемещаемый объект элемента таблицы
		*/
		GroupsTableItem(GroupsTableItem&& src) : GroupsTableItem(src._group_id, src._group_ptr) {
			if (this != &src) src._group_ptr = nullptr;
		}

		/**
		* @brief Копирующий оператор присваивания
		* @param src Ссылка на копируемый объект элемента таблицы
		* @return Ссылка на скопированный элемент таблицы
		*/
		GroupsTableItem& operator= (const GroupsTableItem& src);

		/**
		* @brief Перемещающий оператор присваивания
		* @param src Ссылка на перемещаемый объект элемента таблицы
		* @return Ссылка на перемещенный элемент таблицы
		*/
		GroupsTableItem& operator= (GroupsTableItem&& src);

		/**
		* @brief Оператор равенства
		* @param group_id Номер сравниваемой группы
		* @return true, если номер совпал с номером данного элемента таблицы, иначе - false
		*/
		bool operator== (int group_id) const;

		/**
		* @brief Оператор равенства
		* @param group_ptr Умный указатель на сравниваемую группу
		* @return true, если указатель совпал с указателем данного элемента таблицы, иначе - false
		*/
		bool operator== (std::shared_ptr<Group> group_ptr) const;

		/**
		* @brief Оператор равенства
		* @param group_ptr Указатель на сравниваемую группу
		* @return true, если указатель совпал с указателем данного элемента таблицы, иначе - false
		*/
		bool operator== (Group* group_ptr) const;

		/**
		* @brief Шаблон оператора неравенства
		* @param id_or_ptr Умный или стандартный указатель или номер сравниваемой группы
		* @return true, если соответствующие значения отличаются, иначе - false
		*/
		template<typename T>
		bool operator!= (T id_or_ptr) const {
			return !(operator==(id_or_ptr));
		}

		int group_id() const {
			return _group_id;
		}

		std::shared_ptr<Group> group_ptr() const {
			return _group_ptr;
		}

		/**
		* @brief Дружественный оператор вывода элемента таблицы групп в стандартный поток вывода
		* @param out Ссылка на стандартный поток вывода
		* @param gti Ссылка на объект элемента таблицы групп
		* @return Ссылка на стандартный поток вывода
		*/
		friend std::ostream& operator<< (std::ostream& out, const GroupsTableItem& gti);
	};

	/**
	* @brief Класс таблицы групп, упорядоченной по их номерам
	*/
	class GroupsTable {
	private:

		//! @brief Вектор из элементов таблицы групп
		std::vector<GroupsTableItem> _items;

	public:

		/**
		* @brief Конструктор по умолчанию - создает пустую таблицу
		*/
		GroupsTable() {}

		/**
		* @brief Конструктор по значениям полей для первого элемента
		* @param group_id Номер группы
		* @param group_ptr Умный указатель на группу
		*/
		GroupsTable(int group_id, std::shared_ptr<Group> group_ptr);

		/**
		* @brief Конструктор по значениям полей для первого элемента
		* @param group_id Номер группы
		* @param group_ptr Стандартный указатель на группу
		*/
		GroupsTable(int group_id, Group* group_ptr) :
			GroupsTable(group_id, std::shared_ptr<Group>(group_ptr)) {}

		/**
		* @brief Конструктор по значению первой группы
		* @param group Ссылка на добавляемую группу
		*/
		GroupsTable(Group& group);

		/**
		* @brief Конструктор по значению первого элемента группы
		* @param item Ссылка на добавляемый элемент
		*/
		GroupsTable(GroupsTableItem& item);

		/**
		* @brief Копирующий конструктор
		* @param src Ссылка на копируемый объект таблицы
		*/
		GroupsTable(const GroupsTable& src);

		/**
		* @brief Перемещающий конструктор
		* @param src Ссылка на перемещаемый объект таблицы
		*/
		GroupsTable(GroupsTable&& src);

		/**
		* @brief Копирующий оператор присваивания
		* @param src Ссылка на копируемый объект таблицы
		* @return Ссылка на скопированный объект таблицы
		*/
		GroupsTable& operator= (const GroupsTable& src);

		/**
		* @brief Перемещающий оператор присваивания
		* @param src Ссылка на перемещаемый объект таблицы
		* @return Ссылка на перемещенный объект таблицы
		*/
		GroupsTable& operator= (GroupsTable&& src);

		/**
		* @brief Геттер количества размера таблицы
		* @return Количество элементов в таблице
		*/
		int size() const;

		/**
		* @brief Функция (корректной) вставки нового элемента по значению группы
		* @param group Ссылка на вставляемы объект группы
		*/
		void insert(Group& group);

		/**
		* @brief Функция (корректной) вставки нового элемента по значению элемента
		* @param item Ссылка на вставляемы объект элемента таблицы
		*/
		void insert(GroupsTableItem& item);

		/**
		* @brief Шаблон функции (корректной) вставки нового элемента по значениям полей элемента
		* @param group_id Номер группы
		* @param group_ptr Указатель на группу
		*/
		template<typename T>
		void insert(int group_id, T group_ptr) {
			if (group_ptr == nullptr || find(group_id) >= 0 || find(group_ptr) >= 0 ||
				group_ptr->_id != group_id) return;

			for (auto it = _items.begin(); it != _items.end(); ++it)

				if ((*it)._group_id > group_id) {
					_items.insert(it, GroupsTableItem(group_id, group_ptr));
					break;
				}
		}

		/**
		* @brief Шаблон функции поиска элемента
		* @param group_id_or_ptr Номер или указатель (умный или стандартный) на искомую группу
		* @return Индекс в векторе, если элемент найден, иначе -1
		*/
		template<typename T>
		int find(T group_id_or_ptr) const {
			for (int i = 0; i < _items.size(); ++i)
				if (_items[i] == group_id_or_ptr) return i;
			return -1;
		}

		/**
		* @brief Шаблон функции исключения элемента из таблицы
		* @param group_id_or_ptr Номер или указатель (умный или стандартный) на искомую группу
		*/
		template<typename T>
		void erase(T group_id_or_ptr) {
			int id = find(group_id_or_ptr);
			if (id < 0) return;

			auto it = _items.begin() + id;
			_items.erase(it);
		}

		/**
		* @brief Функция построчного вывода значений полей элементов таблицы
		*/
		void output() const;

		/**
		* @brief Дружественный оператор вывода таблицы групп в стандартный поток вывода
		* @param out Ссылка на стандартный поток вывода
		* @param gti Ссылка на объект таблицы групп
		* @return Ссылка на стандартный поток вывода
		*/
		friend std::ostream& operator<< (std::ostream& out, const GroupsTable& gt);
	};
}