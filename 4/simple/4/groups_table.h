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

		GroupsTableItem(Group& group);

		GroupsTableItem(const GroupsTableItem& src);

		GroupsTableItem(GroupsTableItem&& src);

		~GroupsTableItem();

		bool compare(int group_id) const;

		bool compare(Group* group_ptr) const;

		friend std::ostream& operator<< (std::ostream& out, GroupsTableItem& gti);
	};

	class GroupsTable {
	private:
		std::vector<GroupsTableItem> _items;

	public:
		GroupsTable();

		GroupsTable(int group_id, Group* group_ptr);

		GroupsTable(Group& group);

		GroupsTable(GroupsTableItem& item);

		GroupsTable(const GroupsTable& src);

		GroupsTable(GroupsTable&& src);

		~GroupsTable();

		void insert(int group_id, Group* group_ptr);

		void insert(Group& group);

		void insert(GroupsTableItem& item);

		int find(int group_id) const;

		int find(Group* group_ptr) const;

		void erase(int group_id);

		void erase(int group_ptr);

		friend std::ostream& operator<< (std::ostream& out, const GroupsTable& gt);
	};
}