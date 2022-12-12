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
		std::cout << "Enter Y or N: ";

		while (!ask_input(choice) || choice != 'Y' && choice != 'N');

		if (choice == 'N') return false;
		return true;
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
		std::cout << "Make choice (0 - " << count - 1 << "): ";
		while (!ask_input(choice) || choice < 0 || choice >= count)
			std::cout	<< "Something went wrong:(" << std::endl
						<< "Make choice (0 - " << count - 1 << "): ";
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
			std::cout << "Enter id of target department: ";
			while (!ask_input(department_id) || department_id < 0 || department_id > MAX_INT)
				std::cout << "Something went wrong:(" << std::endl
				<< "Enter id of target department: ";
		}

		else
		{
			std::cout << "Enter name of target department: ";
			while (!ask_input(department_name))
				std::cout << "Something went wrong:(" << std::endl
				<< "Enter name of target department: ";
		}

		return true;
	}

	bool add_department(GroupsTable&, DepartmentsTable& departments_table)
	{
		int department_id = 0;
		std::cout << "Enter unique id of new department: ";
		while (!ask_input(department_id) || department_id < 0 || department_id > 9999999)
			std::cout	<< "Something went wrong:(" << std::endl
						<< "Enter unique id of new department: ";

		std::string department_name;
		std::cout << "Enter unique name of new department: ";
		while (!ask_input(department_name))
			std::cout	<< "Something went wrong:(" << std::endl
						<< "Enter unique name of new department: ";

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
		for (int i = 0; i < 49; ++i) std::cout << '=';
		std::cout << std::endl;

		vector<const GroupsTableItem*> targets;
		groups_table.find_by_department_id(department_id, targets);

		if (targets.size() > 0) {
			std::cout << "|Id\t|Size\t|Department id\t|Study duration\t|" << std::endl;
			for (int i = 0; i < 49; ++i) std::cout << '-';
			std::cout << std::endl;
		}

		for (auto target_ptr : targets) std::cout << '|' <<
			target_ptr->group_ptr()->id() << "\t|" <<
			target_ptr->group_ptr()->size() << "\t|" <<
			target_ptr->group_ptr()->department_id() << "\t\t|" <<
			target_ptr->group_ptr()->study_duration() << "\t\t|" << std::endl;

		for (int i = 0; i < 49; ++i) std::cout << '=';
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

	// 72 104 32
	// sizeof(DayGroup) sizeof(EveningGroup) sizeof(PaidGroup)

	bool find_item(GroupsTableItem& result, const GroupsTable& groups_table)
	{
		int group_id = 0;
		std::cout << "Enter group id: ";
		while (!ask_input(group_id)) std::cout << "Something went wrong! Enter group id: ";

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

			std::cout << "Enter specialization of new group: ";
			while (!ask_input(specialization))
				std::cout << "Something went wrong! Enter specialization of new group: ";

			ask_positive_groups_param(stipend, "stipend");
			ask_positive_groups_param(fellows_emount, "fellows emount");

			std::shared_ptr<DayGroup> day_group(new DayGroup(
				id, size, department_id, study_duration, specialization, stipend, fellows_emount));

			groups_table.insert(GroupsTableItem(day_group));
		}

		if (choice == 2)
		{
			std::string contingent, qualification;

			std::cout << "Enter contingent of new group: ";
			while (!ask_input(contingent))
				std::cout << "Something went wrong! Enter contingent of new group: ";

			std::cout << "Enter qualification of new group: ";
			while (!ask_input(qualification))
				std::cout << "Something went wrong! Enter qualification of new group: ";

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

	bool change_group(GroupsTable& groups_table, DepartmentsTable&)
	{
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