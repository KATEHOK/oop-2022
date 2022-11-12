#pragma once

#ifndef SAME
#include "same.h"
#endif // !SAME

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
		GroupsTableItem(int group_id, Group* group_ptr);

		GroupsTableItem(Group& group) : GroupsTableItem(group._id, &group) {}

		GroupsTableItem(const GroupsTableItem& src) :
			GroupsTableItem(src._group_id, src._group_ptr) {}

		GroupsTableItem(GroupsTableItem&& src) : GroupsTableItem(src._group_id, src._group_ptr) {
			if (this != &src) src._group_ptr = nullptr;
		}

		~GroupsTableItem();

		GroupsTableItem& operator= (const GroupsTableItem& src);

		GroupsTableItem& operator= (GroupsTableItem&& src);

		bool operator== (int group_id) const;

		bool operator== (Group* group_ptr) const;

		template<typename T>
		bool operator!= (T id_or_ptr) const {
			return !(operator==(id_or_ptr));
		}

		friend std::ostream& operator<< (std::ostream& out, const GroupsTableItem& gti);
	};

	class GroupsTable {
	private:

		std::vector<GroupsTableItem> _items;

	public:

		GroupsTable() {}

		GroupsTable(int group_id, Group* group_ptr);

		GroupsTable(Group& group);

		GroupsTable(GroupsTableItem& item);

		GroupsTable(const GroupsTable& src);

		GroupsTable(GroupsTable&& src);

		~GroupsTable();

		GroupsTable& operator= (const GroupsTable& src);

		GroupsTable& operator= (GroupsTable&& src);

		int size() const;

		void insert(int group_id, Group* group_ptr);

		void insert(Group& group);

		void insert(GroupsTableItem& item);

		// вернет индекс в векторе или -1
		template<typename T>
		int find(T group_id_or_ptr) const {
			for (int i = 0; i < _items.size(); ++i)
				if (_items[i] == group_id_or_ptr) return i;
			return -1;
		}

		template<typename T>
		void erase(T group_id_or_ptr) {
			int id = find(group_id_or_ptr);
			if (id < 0) return;

			auto it = _items.begin() + id;
			_items.erase(it);
		}

		void output() const;

		friend std::ostream& operator<< (std::ostream& out, const GroupsTable& gt);
	};
}