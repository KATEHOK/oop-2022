#ifndef GROUPS_TABLE
#include "groups_table.h"
#endif // !GROUPS_TABLE

namespace group {

	// class GroupsTableItem

	GroupsTableItem::GroupsTableItem(int group_id, const std::shared_ptr<Group>& group_ptr) {
		if (group_ptr.get() != nullptr) {
			_group_id = group_id;
			_group_ptr = group_ptr;
		}
	}

	GroupsTableItem::GroupsTableItem(int group_id, std::shared_ptr<Group>&& group_ptr) {
		if (group_ptr.get() != nullptr) {
			_group_id = group_id;
			_group_ptr = group_ptr;

			group_ptr = nullptr;
		}
	}

	GroupsTableItem::GroupsTableItem(const std::shared_ptr<Group>& group_ptr) {
		if (group_ptr.get() != nullptr) {
			_group_id = group_ptr->_id;
			_group_ptr = group_ptr;
		}
	}

	GroupsTableItem::GroupsTableItem(std::shared_ptr<Group>&& group_ptr) {
		if (_group_ptr.get() != group_ptr.get() && group_ptr.get() != nullptr) {
			_group_id = group_ptr->_id;
			_group_ptr = std::move(group_ptr);
		}
	}

	GroupsTableItem::GroupsTableItem(const GroupsTableItem& src) {
		copy_from(src);
	}

	GroupsTableItem::GroupsTableItem(GroupsTableItem&& src) {
		move_from(std::move(src));
	}

	GroupsTableItem& GroupsTableItem::operator= (const GroupsTableItem& src) {
		copy_from(src);
		return *this;
	}

	GroupsTableItem& GroupsTableItem::operator= (GroupsTableItem&& src) {
		move_from(std::move(src));
		return *this;
	}

	void GroupsTableItem::copy_from(const GroupsTableItem& src) {
		_group_id = src._group_id;
		_group_ptr = src._group_ptr;
	}

	void GroupsTableItem::move_from(GroupsTableItem&& src) {
		if (this == &src) return;
		copy_from(src);

		src._group_id = 0;
		src._group_ptr = nullptr; // DANGER
	}

	bool GroupsTableItem::operator== (int group_id) const {
		return (_group_id == group_id);
	}

	bool GroupsTableItem::operator== (const std::shared_ptr<Group>& group_ptr) const {
		return (_group_ptr.get() == group_ptr.get());
	}

	bool GroupsTableItem::operator== (const Group* group_ptr) const {
		return (_group_ptr.get() == group_ptr);
	}

	bool GroupsTableItem::operator!= (const std::shared_ptr<Group>& group_ptr) const {
		return !(operator==(group_ptr));
	}

	std::ostream& operator<< (std::ostream& out, const GroupsTableItem& gti) {
		out << '[' << gti._group_id << ", " << gti._group_ptr << ']';
		return out;
	}

	// class GroupsTable

	GroupsTable::GroupsTable(int group_id, const std::shared_ptr<Group>& group_ptr) {
		if (group_ptr.get() != nullptr) {
			_items.push_back(GroupsTableItem(group_id, group_ptr));
		}
	}

	GroupsTable::GroupsTable(int group_id, std::shared_ptr<Group>&& group_ptr) {
		if (group_ptr.get() != nullptr) {
			_items.push_back(GroupsTableItem(group_id, std::move(group_ptr)));
		}
	}

	GroupsTable::GroupsTable(Group& group) {
		_items.push_back(GroupsTableItem(group));
	}

	GroupsTable::GroupsTable(const GroupsTableItem& item) {
		_items.push_back(item);
	}

	GroupsTable::GroupsTable(GroupsTableItem&& item) {
		_items.push_back(std::move(item));
	}

	GroupsTable::GroupsTable(const GroupsTable& src) {
		copy_from(src);
	}

	GroupsTable::GroupsTable(GroupsTable&& src) {
		move_from(std::move(src));
	}

	GroupsTable& GroupsTable::operator= (const GroupsTable& src) {
		copy_from(src);
		return *this;
	}

	GroupsTable& GroupsTable::operator= (GroupsTable&& src) {
		move_from(std::move(src));
		return *this;
	}

	void GroupsTable::copy_from(const GroupsTable& src) {
		_items = src._items;
	}

	void GroupsTable::move_from(GroupsTable&& src) {
		if (this == &src) return;
		_items = std::move(src._items);
	}

	size_t GroupsTable::size() const {
		return _items.size();
	}

	void GroupsTable::insert(Group& group) {
		if (find(group._id) >= 0 || find(&group) >= 0) return;
		size_t size = _items.size();

		if (_items.size() > 0)
		{
			for (auto it = _items.cbegin(); it != _items.cend(); ++it)

				if ((*it)._group_id > group._id || (it + 1) == _items.cend()) {
					_items.insert(it, GroupsTableItem(group));
					break;
				}
		}
		if (size == _items.size()) _items.push_back(GroupsTableItem(group));
	}

	void GroupsTable::insert(const GroupsTableItem& item) {
		if (find(item._group_id) >= 0 || find(item._group_ptr) >= 0) return;
		size_t size = _items.size();

		if (_items.size() > 0)
		{
			for (auto it = _items.cbegin(); it != _items.cend(); ++it)

				if ((*it)._group_id > item._group_id || (it + 1) == _items.cend()) {
					_items.insert(it, item);
					break;
				}
		}
		if (size == _items.size()) _items.push_back(item);
	}

	void GroupsTable::insert(GroupsTableItem&& item) {
		if (find(item._group_id) >= 0 || find(item._group_ptr) >= 0) return;
		size_t size = _items.size();

		if (_items.size() > 0)
		{
			for (auto it = _items.cbegin(); it != _items.cend(); ++it)

				if ((*it)._group_id > item._group_id) {
					_items.insert(it, std::move(item));
					break;
				}
		}
		if (size == _items.size()) _items.push_back(std::move(item));
	}

	void GroupsTable::insert(int group_id, const std::shared_ptr<Group>& group_ptr) {
		if (group_ptr.get() == nullptr || find(group_id) >= 0 || find(group_ptr) >= 0 ||
			group_ptr->_id != group_id) return;
		size_t size = _items.size();

		if (_items.size() > 0)
		{
			for (auto it = _items.cbegin(); it != _items.cend(); ++it)

				if ((*it)._group_id > group_id || (it + 1) == _items.cend()) {
					_items.insert(it, GroupsTableItem(group_id, group_ptr));
					break;
				}
		}
		if (size == _items.size()) _items.push_back(GroupsTableItem(group_id, group_ptr));
	}

	void GroupsTable::insert(int group_id, std::shared_ptr<Group>&& group_ptr) {
		if (group_ptr.get() == nullptr || find(group_id) >= 0 || find(group_ptr) >= 0 ||
			group_ptr->_id != group_id) return;
		size_t size = _items.size();

		if (_items.size() > 0)
		{
			for (auto it = _items.cbegin(); it != _items.cend(); ++it)

				if ((*it)._group_id > group_id || (it + 1) == _items.cend()) {
					_items.insert(it, GroupsTableItem(group_id, std::move(group_ptr)));
					break;
				}
		}
		if (size == _items.size())
			_items.push_back(GroupsTableItem(group_id, std::move(group_ptr)));
	}

	int GroupsTable::find(const std::shared_ptr<Group>& group_ptr) const {
		for (int i = 0; i < _items.size(); ++i)
			if (_items[i] == group_ptr) return i;
		return -1;
	}

	void GroupsTable::erase(const std::shared_ptr<Group>& group_ptr) {
		int id = find(group_ptr);
		if (id < 0) return;

		auto it = _items.cbegin() + id;
		_items.erase(it);
	}

	void GroupsTable::find_by_department_id(
		int department_id,
		vector<const GroupsTableItem*>& dest) const
	{
		for (int i = 0; i < _items.size(); ++i)
			if (_items[i]._group_ptr->_department_id == department_id)
				dest.push_back(&(_items[i]));
	}

	void GroupsTable::erase_by_department_id(int department_id)
	{
		vector<const GroupsTableItem*> targets;
		find_by_department_id(department_id, targets);
		for (auto gti : targets) erase(gti->_group_id);

	}

	void GroupsTable::output() const {
		int len_id = 0, len_num, copy_id, len_ptr = 16;
		for (auto i : _items) {

			len_num = 0, copy_id = i._group_id;
			while (copy_id > 0) {
				copy_id /= 10;
				++len_num;
			}

			if (len_num > len_id) len_id = len_num;
		}
		len_id += 8 - len_id % 8;

		for (int i = 0; i < len_id + len_ptr; ++i) std::cout << '=';
		std::cout << std::endl;

		for (auto i : _items) std::cout << i._group_id << '\t' << i._group_ptr << std::endl;

		for (int i = 0; i < len_id + len_ptr; ++i) std::cout << '=';
		std::cout << std::endl;
		
	}

	void GroupsTable::clear()
	{
		_items.clear();
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