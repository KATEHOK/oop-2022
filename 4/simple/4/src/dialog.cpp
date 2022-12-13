#ifndef DIALOG
#include "dialog.h"
#endif // !DIALOG

using namespace my_template;
using namespace department;
using namespace group;

namespace dialog {

	bool confirm()
	{
		char choice = '\0';

		ask_input_persistently_and_conditionally(
			choice,	"Enter Y or N",
			[&]() { return choice != 'Y' && choice != 'N'; });

		return choice == 'Y';
	}

	void print_greeting()
	{
		std::cout <<
			"Hello world!"
			<< std::endl;
	}

	void print_farewell()
	{
		std::cout <<
			"Good bye world!"
			<< std::endl;
	}

	void print_options(const vector<std::string>& options)
	{
		int len = 0;
		for (auto i : options) if (i.size() > len) len = i.size();
		len += 15;

		for (int i = 0; i < len; ++i) std::cout << '=';
		std::cout << std::endl;

		for (auto it = options.cbegin(); it < options.cend(); ++it)
			std::cout << it.id() << ")\t" << *it << std::endl;

		for (int i = 0; i < len; ++i) std::cout << '=';
		std::cout << std::endl;
	}

	void ask_choice(int& choice, size_t count)
	{
		ask_input_persistently_and_conditionally(
			choice, "Make choice (0 - " + std::to_string(count - 1) + ')',
			[&]() { return choice < 0 || choice >= count; }
		);
	}

	// departments_table

	bool ask_input_departments_param(int& department_id, std::string& department_name)
	{
		int choice = 0;

		std::cout << "What do you want to do?" << std::endl;
		vector<std::string> options = {
			"Cancel",
			"Select department by id",
			"Select department by name"
		};

		print_options(options);
		ask_choice(choice, options.size());

		if (choice == 0)
		{
			std::cout << "Canceling..." << std::endl;
			return false;
		}
		if (choice == 1)
		{
			ask_input_persistently_and_conditionally(
				department_id,
				"Enter id of target department",
				[&]() {return department_id < 0 || department_id > MAX_INT; }
			);
		}
		else ask_input_persistently(department_name, "Enter name of target department");

		return true;
	}

	bool add_department(GroupsTable&, DepartmentsTable& departments_table)
	{
		int department_id = 0;
		ask_input_persistently_and_conditionally(
			department_id, "Enter unique id of new department",
			[&]() { return department_id < 0 || department_id > MAX_INT; });

		std::string department_name;
		ask_input_persistently(department_name, "Enter unique name of new department");

		Department department(department_id, department_name);

		if (departments_table.push_back(std::move(department)))
				std::cout << "Success!" << std::endl;
		else	std::cout << "Department with the same id or name is already exist!" << std::endl;

		return true;
	}

	bool erase_department(GroupsTable& groups_table, DepartmentsTable& departments_table)
	{
		int department_id = -1;
		std::string department_name;

		if (!ask_input_departments_param(department_id, department_name)) return true;

		std::cout << "Groups of this department will also be deleted! Are you sure? " << std::endl;
		if (confirm())
		{
			try
			{
				if (department_id == -1) department_id = departments_table[department_name].id();
			}
			catch (std::out_of_range err)
			{
				std::cout << "This department is not exist! Canceling..." << std::endl;
				return true;
			}

			departments_table.erase(department_id);
			groups_table.erase_by_department_id(department_id);

			std::cout << "Success!" << std::endl;
		}
		else std::cout << "Canceling..." << std::endl;

		return true;
	}

	bool output_groups_by_department(GroupsTable& groups_table, DepartmentsTable& departments_table)
	{
		int department_id = -1;
		std::string department_name;

		if (!ask_input_departments_param(department_id, department_name)) return true;

		try
		{
			if (department_id == -1) department_id = departments_table[department_name].id();
			department_id = departments_table[department_id].id();
			department_name = departments_table[department_id].name();
		}
		catch (std::out_of_range err)
		{
			std::cout << "This department is not exist! Canceling..." << std::endl;
			return true;
		}

		std::cout << std::endl << "Groups of department: [" <<
			department_id << ", " << department_name << ']' << std::endl;

		for (int i = 0; i < 57; ++i) std::cout << '=';
		std::cout << std::endl;

		vector<const GroupsTableItem*> targets;
		groups_table.find_by_department_id(department_id, targets);

		if (targets.size() > 0) {
			std::cout << "|Type\t|Id\t|Size\t|Department id\t|Study duration\t|" << std::endl;
			for (int i = 0; i < 57; ++i) std::cout << '-';
			std::cout << std::endl;
		}

		for (auto target_ptr : targets) std::cout << '|' <<
			target_ptr->group_ptr()->type() << "\t|" <<
			target_ptr->group_ptr()->id() << "\t|" <<
			target_ptr->group_ptr()->size() << "\t|" <<
			target_ptr->group_ptr()->department_id() << "\t\t|" <<
			target_ptr->group_ptr()->study_duration() << "\t\t|" << std::endl;

		for (int i = 0; i < 57; ++i) std::cout << '=';
		std::cout << std::endl;

		return true;
	}

	bool output_departments_table(GroupsTable&, DepartmentsTable& departments_table)
	{
		std::cout << "Departments table" << std::endl;
		departments_table.output();
		return true;
	}

	bool clear_departments_table(GroupsTable& groups_table, DepartmentsTable& departments_table)
	{
		// ни одна группа не может существовать без профилирующей кафедры
		std::cout << "All groups will also be deleted! Are you sure?" << std::endl;
		if (confirm())
		{
			departments_table.clear();
			groups_table.clear();
			std::cout << "All departments and groups were deleted!" << std::endl;
		}
		else std::cout << "Canceling..." << std::endl;
		return true;
	}

	// groups_table

	Group* make_pseudo_clone(
		const Group& group,
		int department_id,
		int study_duration,
		std::string specialization,
		std::string contingent)
	{
		Group* clone = nullptr;
		if (group.type() == "Day")
		{
			clone = new DayGroup(
				group.id(),
				group.size(),
				department_id,
				study_duration,
				specialization,
				group.stipend(),
				group.fellows_amount()
			);
		}
		else if (group.type() == "Evening")
		{
			clone = new EveningGroup(
				group.id(),
				group.size(),
				department_id,
				study_duration,
				contingent,
				group.qualification()
			);
		}
		else
		{
			clone = new PaidGroup(
				group.id(),
				group.size(),
				department_id,
				study_duration,
				group.contract_id(),
				group.payment_size()
			);
		}
		return clone;
	}

	bool find_item(GroupsTableItem& result, const GroupsTable& groups_table)
	{
		int group_id = 0;
		ask_input_persistently(group_id, "Enter group id");

		try { result = groups_table[group_id]; }
		catch (std::out_of_range)
		{
			std::cout << "This group is not exist!" << std::endl;
			return false;
		}
		return true;
	}

	bool add_group(GroupsTable& groups_table, DepartmentsTable& departments_table)
	{
		int choice = 0;
		const vector<std::string> options = {
			"Cancel",
			"Day group",
			"Evening group",
			"Paid group"
		};

		std::cout << "Select group type or cancel" << std::endl;
		print_options(options);
		ask_choice(choice, options.size());

		if (choice == 0) return true;
		
		size_t size = 0;
		int id = 0, department_id = 0, study_duration = 0;

		std::cout << std::endl;
		ask_positive_groups_param(id, "id");
		ask_positive_groups_param(size, "size");

		ask_positive_groups_param(department_id, "department id");
		while (departments_table.find(department_id) == -1)
		{
			std::cout << "This department is not exist... Try again!" << std::endl;
			ask_positive_groups_param(department_id, "department id");
		}

		ask_positive_groups_param(study_duration, "study duration");

		if (choice == 1)
		{
			std::string specialization;
			float stipend = 0;
			int fellows_emount = 0;

			ask_input_persistently(specialization, "Enter specialization of new group");
			ask_positive_groups_param(stipend, "stipend");
			ask_positive_groups_param(fellows_emount, "fellows emount");

			std::shared_ptr<DayGroup> day_group(new DayGroup(
				id, size, department_id, study_duration, specialization, stipend, fellows_emount));

			groups_table.insert(GroupsTableItem(day_group));
		}

		if (choice == 2)
		{
			std::string contingent, qualification;

			ask_input_persistently(contingent, "Enter contingent of new group");
			ask_input_persistently(qualification, "Enter qualification of new group");

			std::shared_ptr<EveningGroup> evening_group(new EveningGroup(
				id, size, department_id, study_duration, contingent, qualification));

			groups_table.insert(GroupsTableItem(evening_group));
		}

		if (choice == 3)
		{
			int contract_id = 0;
			float payment_size = 0;

			ask_positive_groups_param(contract_id, "contract id");
			ask_positive_groups_param(payment_size, "payment size");

			std::shared_ptr<PaidGroup> paid_group(new PaidGroup(
				id, size, department_id, study_duration, contract_id, payment_size));

			groups_table.insert(GroupsTableItem(paid_group));
		}

		std::cout << "Success!" << std::endl;
		return true;
	}

	bool find_item(GroupsTable& groups_table, DepartmentsTable&)
	{
		GroupsTableItem item;
		if (find_item(item, groups_table)) std::cout << "Item = " << item << std::endl;
		return true;
	}

	bool output_group(GroupsTable& groups_table, DepartmentsTable&)
	{
		GroupsTableItem item;
		if (find_item(item, groups_table))
			std::cout << "Group = " << *(item.group_ptr()) << std::endl;
		return true;
	}

	bool output_group_info(GroupsTable& groups_table, DepartmentsTable&)
	{
		GroupsTableItem item;
		if (!find_item(item, groups_table)) return true;

		const vector<std::string> options = {
			"Cancel",			// 0
			"Type",				// 1
			"Id",				// 2
			"Size",				// 3
			"Department id",	// 4
			"Study duration",	// 5
			"Specialization",	// 6
			"Stipend",			// 7
			"Fellows amount",	// 8
			"Contingent",		// 9
			"Qualification",	// 10
			"Contract id",		// 11
			"Payment size"		// 12
		};

		int choice = 1;
		while (choice > 0)
		{
			std::cout << std::endl << "What information of " << item.group_id() <<
						" group do you want to see?" << std::endl;

			print_options(options);
			ask_choice(choice, options.size());

			switch (choice)
			{
			case 0:
				std::cout << "Canceling..." << std::endl;
				break;

			case 1:
				std::cout << "Group type: " << item.group_ptr()->type() << " group" << std::endl;
				break;

			case 2:
				std::cout << "Group id: " << item.group_ptr()->id() << std::endl;
				break;

			case 3:
				std::cout << "Group size: " << item.group_ptr()->size() << std::endl;
				break;

			case 4:
				std::cout << "Groups department id: " << item.group_ptr()->department_id() << std::endl;
				break;

			case 5:
				std::cout << "Groups study duration: " << item.group_ptr()->study_duration() << std::endl;
				break;

			case 6:
				std::cout << "Groups specialization: " << item.group_ptr()->specialization() << std::endl;
				break;

			case 7:
				std::cout << "Groups stipend: " << item.group_ptr()->stipend() << std::endl;
				break;

			case 8:
				std::cout << "Groups fellows amount: " << item.group_ptr()->fellows_amount() << std::endl;
				break;

			case 9:
				std::cout << "Groups contingent: " << item.group_ptr()->contingent() << std::endl;
				break;

			case 10:
				std::cout << "Groups qualification: " << item.group_ptr()->qualification() << std::endl;
				break;

			case 11:
				if (item.group_ptr()->type() == "Paid")
					std::cout << "Groups contract id: " << item.group_ptr()->contract_id() << std::endl;
				else std::cout << "This group has not contract" << std::endl;
				break;

			case 12:
				std::cout << "Groups payment size: " << item.group_ptr()->payment_size() << std::endl;
				break;
			}
		}
		return true;
	}

	bool change_group(GroupsTable& groups_table, DepartmentsTable& departments_table)
	{
		GroupsTableItem item;
		if (!find_item(item, groups_table)) return true;

		const vector<std::string> options = {
			"Cancel",			// 0
			"Size",				// 1
			"Stipend",			// 2
			"Fellows amount",	// 3
			"Payment size",		// 4
			"Department id",	// 5 - new group
			"Study duration",	// 6 - new group
			"Specialization",	// 7 - new group
			"Contingent",		// 8 - new group
		};

		int choice = 1;
		while (choice > 0)
		{
			std::cout << std::endl << "What information of " << item.group_id() <<
				" group do you want to change?" << std::endl;

			print_options(options);
			ask_choice(choice, options.size());

			Group* new_group = nullptr;
			size_t size;
			float stipend;
			int fellows_amount;
			float payment_size;
			int department_id;
			int study_duration;
			std::string specialization;
			std::string contingent;

			switch (choice)
			{
			case 0:
				std::cout << "Canceling..." << std::endl;
				break;

			case 1:
				ask_positive_groups_param(size, "size");
				std::cout << "New group size: " << item.group_ptr()->size(size) << std::endl;
				break;

			case 2:
				if (item.group_ptr()->type() != "Day")
				{
					std::cout << "You can not change stipend if type of group is not \"Day\"!" << std::endl;
					break;
				}
				ask_positive_groups_param(stipend, "stipend");
				std::cout << "New groups stipend: " << item.group_ptr()->stipend(stipend) << std::endl;
				break;

			case 3:
				if (item.group_ptr()->type() != "Day")
				{
					std::cout << "You can not change fellows amount if type of group is not \"Day\"!" <<
						std::endl;
					break;
				}
				ask_positive_groups_param(fellows_amount, "fellows amount");
				std::cout << "New groups fellows amount: " <<
					item.group_ptr()->fellows_amount(fellows_amount) << std::endl;
				break;

			case 4:
				if (item.group_ptr()->type() != "Paid")
				{
					std::cout << "You can not change payment size if type of group is not \"Paid\"!" <<
						std::endl;
					break;
				}
				ask_positive_groups_param(payment_size, "payment size");
				std::cout << "New groups payment size: " <<
					item.group_ptr()->payment_size(payment_size) << std::endl;
				break;

			case 5:
				ask_positive_groups_param(department_id, "department id");

				try { departments_table[department_id]; }
				catch (std::out_of_range)
				{
					std::cout << "This department is not exist!" << std::endl;
					break;
				}

				new_group = make_pseudo_clone(
					*item.group_ptr(),
					department_id,
					item.group_ptr()->study_duration(),
					item.group_ptr()->specialization(),
					item.group_ptr()->contingent()
				);

				groups_table.erase(item.group_id());
				groups_table.insert(GroupsTableItem(std::shared_ptr<Group>(new_group)));

				std::cout << "New groups department id: " <<
					new_group->department_id() << std::endl;
				choice = 0;
				break;

			case 6:
				ask_positive_groups_param(study_duration, "study duration");

				new_group = make_pseudo_clone(
					*item.group_ptr(),
					item.group_ptr()->department_id(),
					study_duration,
					item.group_ptr()->specialization(),
					item.group_ptr()->contingent()
				);

				groups_table.erase(item.group_id());
				groups_table.insert(GroupsTableItem(std::shared_ptr<Group>(new_group)));

				std::cout << "New groups study duration: " <<
					new_group->study_duration() << std::endl;
				choice = 0;
				break;

			case 7:
				if (item.group_ptr()->type() != "Day")
				{
					std::cout << "You can not change specialization if type of group is not \"Day\"!" <<
						std::endl;
					break;
				}

				ask_input_persistently(specialization, "Enter specialization of group");

				new_group = make_pseudo_clone(
					*item.group_ptr(),
					item.group_ptr()->department_id(),
					item.group_ptr()->study_duration(),
					specialization,
					item.group_ptr()->contingent()
				);

				groups_table.erase(item.group_id());
				groups_table.insert(GroupsTableItem(std::shared_ptr<Group>(new_group)));

				std::cout << "New groups specialization: " <<
					new_group->specialization() << std::endl;
				choice = 0;
				break;

			case 8:
				if (item.group_ptr()->type() != "Evening")
				{
					std::cout << "You can not change contingent if type of group is not \"Evening\"!" <<
						std::endl;
					break;
				}

				ask_input_persistently(contingent, "Enter contingent of group");

				new_group = make_pseudo_clone(
					*item.group_ptr(),
					item.group_ptr()->department_id(),
					item.group_ptr()->study_duration(),
					item.group_ptr()->specialization(),
					contingent
				);

				groups_table.erase(item.group_id());
				groups_table.insert(GroupsTableItem(std::shared_ptr<Group>(new_group)));

				std::cout << "New groups contingent: " <<
					new_group->contingent() << std::endl;
				choice = 0;
				break;
			}
		}
		return true;
	}

	bool erase_group(GroupsTable& groups_table, DepartmentsTable&)
	{
		GroupsTableItem item;
		if (find_item(item, groups_table)) groups_table.erase(item.group_id());
		return true;
	}

	bool output_groups_table(GroupsTable& groups_table, DepartmentsTable&)
	{
		std::cout << "Groups table" << std::endl;
		groups_table.output();
		return true;
	}

	bool clear_groups_table(GroupsTable& groups_table, DepartmentsTable&)
	{
		groups_table.clear();
		return true;
	}




}