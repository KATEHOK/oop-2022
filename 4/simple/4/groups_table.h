#pragma once

#ifndef PRECOMPILED
#include "precompiled.h"
#endif // !PRECOMPILED

#ifndef GROUP
#include "group.h"
#endif // !GROUP

#define GROUPS_TABLE

namespace group {

	class GroupsTableItem {

		friend class GroupsTable;

	private:
		int _group_id;
		Group* _group_ptr = nullptr;

	public:
		GroupsTableItem(int group_id, Group* group_ptr) :
			_group_id(group_id), _group_ptr(group_ptr) {}

		GroupsTableItem(Group& group) :	_group_id(group.id()), _group_ptr(&group) {}

		GroupsTableItem(const GroupsTableItem& src) :
			_group_id(src._group_id), _group_ptr(src._group_ptr) {}

		GroupsTableItem(GroupsTableItem&& src) noexcept :
			_group_id(src._group_id), _group_ptr(src._group_ptr)
		{
			if (this != &src) src._group_ptr = nullptr;
		}

		~GroupsTableItem()
		{
			delete _group_ptr;
			_group_ptr = nullptr;
		}

		bool compare(int group_id) const
		{
			return _group_id == group_id;
		}

		bool compare(Group* group_ptr) const
		{
			return _group_ptr == group_ptr;
		}

		void output(std::ostream& out) const
		{
			out << '{' << _group_id << ", " << _group_ptr << '}';
		}
	};

	class GroupsTable {
	private:
		std::vector<GroupsTableItem> _items;

	public:
		GroupsTable() {}

		GroupsTable(int group_id, Group* group_ptr)
		{
			insert(group_id, group_ptr);
		}

		GroupsTable(Group& group)
		{
			insert(group);
		}

		GroupsTable(GroupsTableItem& item)
		{
			insert(item);
		}

		GroupsTable(const GroupsTable& src)
		{
			_items.clear();
			for (auto it = src._items.cbegin(); it != src._items.cend(); ++it) {
				_items.push_back(*it);
			}
		}

		GroupsTable(GroupsTable&& src) noexcept
		{
			if (this != &src) _items.clear();
			for (auto it = src._items.cbegin(); it != src._items.cend(); ++it) {
				_items.push_back(*it);
			}
			if (this != &src) src._items.clear();
		}

		~GroupsTable()
		{
			for (auto it = _items.begin(); it != _items.end(); ++it) {
				(*it).~GroupsTableItem();
			}
			_items.clear();
		}

		void insert(int group_id, Group* group_ptr) {
			if (find(group_ptr) < 0) _items.push_back(GroupsTableItem(group_id, group_ptr));
		}

		void insert(Group& group) {
			if (find(&group) < 0) _items.push_back(GroupsTableItem(group));
		}

		void insert(GroupsTableItem& item) {
			if (find(item._group_ptr) < 0) _items.push_back(item);
		}

		int find(int group_id) const;

		int find(Group* group_ptr) const;

		void erase(int group_id);

		void erase(int group_ptr);

		void output(std::ostream& out) const
		{
			for (auto it = _items.cbegin(); it != _items.cend(); ++it)
			{
				(*it).output(out);
				out << std::endl;
			}
		}
	};
}