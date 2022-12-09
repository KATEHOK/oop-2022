#ifndef GROUPS_TABLE
#include "groups_table.h"
#endif // !GROUPS_TABLE

namespace group {

	// class GroupsTableItem

	GroupsTableItem::GroupsTableItem(int group_id, std::shared_ptr<Group> group_ptr) {
		if (group_ptr.get() != nullptr) {
			_group_id = group_id;
			_group_ptr = group_ptr;
		}
	}

	GroupsTableItem& GroupsTableItem::operator= (const GroupsTableItem& src) {
		_group_id = src._group_id;
		_group_ptr = src._group_ptr;
		return *this;
	}

	GroupsTableItem& GroupsTableItem::operator= (GroupsTableItem&& src) {
		if (this != &src) {
			_group_id = src._group_id;
			_group_ptr = src._group_ptr;

			src._group_ptr = nullptr;
		}
		return *this;
	}

	bool GroupsTableItem::operator== (int group_id) const {
		return (_group_id == group_id);
	}

	bool GroupsTableItem::operator== (const std::shared_ptr<Group> group_ptr) const {
		return (_group_ptr == group_ptr);
	}

	bool GroupsTableItem::operator== (const Group* group_ptr) const {
		return (_group_ptr.get() == group_ptr);
	}

	std::ostream& operator<< (std::ostream& out, const GroupsTableItem& gti) {
		out << '[' << gti._group_id << ", " << gti._group_ptr << ']';
		return out;
	}

	// class GroupsTable

	GroupsTable::GroupsTable(int group_id, std::shared_ptr<Group> group_ptr) {
		if (group_ptr.get() != nullptr) {
			_items.push_back(GroupsTableItem(group_id, group_ptr));
		}
	}

	GroupsTable::GroupsTable(Group& group) {
		_items.push_back(GroupsTableItem(group));
	}

	GroupsTable::GroupsTable(GroupsTableItem& item) {
		_items.push_back(item);
	}

	GroupsTable::GroupsTable(const GroupsTable& src) {
		_items = src._items;
	}

	GroupsTable::GroupsTable(GroupsTable&& src) {
		if (this != &src) {
			_items = src._items;
			src._items.clear();
		}
	}

	GroupsTable& GroupsTable::operator= (const GroupsTable& src) {
		_items = src._items;
		return *this;
	}

	GroupsTable& GroupsTable::operator= (GroupsTable&& src) {
		if (this != &src) {
			_items = src._items;
			src._items.clear();
		}
		return *this;
	}

	size_t GroupsTable::size() const {
		return _items.size();
	}

	void GroupsTable::insert(Group& group) {
		if (find(group._id) >= 0 || find(&group) >= 0) return;

		for (auto it = _items.begin(); it != _items.end(); ++it) {

			if ((*it)._group_id > group._id || (it + 1) == _items.end()) {
				_items.insert(it, GroupsTableItem(group));
				break;
			}

		}
	}

	void GroupsTable::insert(GroupsTableItem& item) {
		if (find(item._group_id) >= 0 || find(item._group_ptr) >= 0) return;

		for (auto it = _items.begin(); it != _items.end(); ++it)

			if ((*it)._group_id > item._group_id || (it + 1) == _items.end()) {
				_items.insert(it, item);
				break;
			}
	}

	void GroupsTable::insert(int group_id, std::shared_ptr<Group> group_ptr) {
		if (group_ptr.get() == nullptr || find(group_id) >= 0 || find(group_ptr) >= 0 ||
			group_ptr->_id != group_id) return;

		for (auto it = _items.begin(); it != _items.end(); ++it)

			if ((*it)._group_id > group_id || (it + 1) == _items.end()) {
				_items.insert(it, GroupsTableItem(group_id, group_ptr));
				break;
			}
	}

	void GroupsTable::output() const {
		std::cout << std::endl;
		for (auto i : _items) std::cout << i._group_id << " : " << i._group_ptr << std::endl;
		std::cout << std::endl;
	}

	std::ostream& operator<< (std::ostream& out, const GroupsTable& gt) {
		out << '{';
		for (int i = 0; i < gt._items.size(); ++i) {
			out << gt._items[i];
			if (i < gt._items.size() - 1) out << ", ";
		}
		out << '}';
		return out;
	}

}