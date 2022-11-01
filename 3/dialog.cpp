#ifndef APP
#include "app.h"
#endif


namespace dialog {

	int askNum(const std::string fMsg, const std::string sMsg) {
		int value = 0;
		std::cout << fMsg;
		while (getNum(&value) == FAIL)
			std::cout << std::endl << sMsg;
		std::cout << std::endl;
		return value;
	}

	bool confirm() {
		char choice = '\0';
		std::cout << "Enter Y or N: ";
		std::cin >> choice;

		while ((choice != 'Y' && choice != 'N') || !std::cin.good()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << std::endl << "Enter Y or N: ";
			std::cin >> choice;
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (choice == 'N') return false;
		return true;
	}

	bool exit(Sequence& seq) { return false; }

	bool initFree(Sequence& seq) {
		Sequence free;
		seq = free;
		std::cout << seq << std::endl;
		return true;
	}

	bool initOne(Sequence& seq) {
		int value = askNum("Enter integer: ", "Invalid value! Enter integer: ");
		seq = value;

		std::cout << seq << std::endl;
		return true;
	}

	bool initByArray(Sequence& seq) {
		int i;
		const int MAX_SIZE = 100;
		int pArr[MAX_SIZE];
		std::cout << "Enter not more 100 numbers via space: ";

		for (i = 0; i < MAX_SIZE; i++) {
			std::cin >> pArr[i];
			if (!std::cin.good()) {
				std::cin.clear();
				break;
			}
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		seq = Sequence(i, pArr);
		std::cout << seq << std::endl;
		return true;
	}

	bool printSize(Sequence& seq) {
		std::cout << "Size of current sequence: " << seq.getSize() << std::endl;
		return true;
	}

	bool printMaxSize(Sequence& seq) {
		std::cout << "Max size of current sequence: " << seq.getMaxSize() << std::endl;
		return true;
	}

	bool printElement(Sequence& seq) {
		if (seq.getSize() == 0) {
			std::cout << "Sequence is free!" << std::endl;
			return true;
		}

		int value = 0;
		std::cout << "Enter id (extended natural from 0 to "
			<< seq.getSize() - 1 << "): ";

		while (getNum(&value) == FAIL || value < 0 || value >= seq.getSize())
			std::cout << std::endl << "Invalid value! Enter extended natural: ";
		std::cout << std::endl;

		std::cout << "[" << value << "] " << seq[value] << std::endl;
		return true;
	}

	bool input(Sequence& seq) {
		std::cout << "Enter via space integer or something else if you want to stop: ";
		std::cin >> seq;

		std::cout << std::endl << "Current sequence: " << seq << std::endl;
		return true;
	}

	bool output(Sequence& seq) {
		std::cout << "Current sequence: " << seq << std::endl;
		return true;
	}

	bool plus(Sequence& seq) {
		Sequence other;

		std::cout << "Making the second sequence" << std::endl;
		std::cout << "Enter via space integer or something else if you want to stop: ";

		std::cin >> other;
		std::cout << std::endl;

		Sequence res = seq + other;
		std::cout << std::endl << seq << " + " << other << " = " << res << std::endl;

		std::cout << "Do you want to replace your current sequence?" << std::endl;
		if (confirm()) seq = res;
		return true;
	}

	bool findMonotonicity(Sequence& seq) {
		int order = 0;

		std::cout << "Enter 0 to find ascending subsequence "
			<< "or 1 to find descending subsequence: ";
		while (getNum(&order) == FAIL || (order != 0 && order != 1))
			std::cout << std::endl << "Invalid value! Try again: ";
		std::cout << std::endl;

		Sequence sub = seq.findMonotonicity(order);
		std::cout << "Subsequence: " << sub << std::endl;

		std::cout << "Do you want to replace your current sequence?" << std::endl;
		if (confirm()) seq = sub;
		return true;
	}

	bool insert(Sequence& seq) {
		int value = askNum("Enter new value (integer): ", "Invalid value! Try again: ");
		seq += value;
		return true;
	}

	bool printGroupsCount(Sequence& seq) {
		std::cout << "There are " << seq.getGroupsCount()
			<< " groups in the sequence" << std::endl;
		return true;
	}

	bool printSameCount(Sequence& seq) {
		int value = askNum("Enter value (integer): ", "Invalid value! Try again: ");
		std::cout << "There are " << seq.getSameCount(value)
			<< " elements equal " << value << " in the sequence" << std::endl;
		return true;
	}

	void printVars(const std::vector<std::string> vars) {
		std::cout << std::endl;
		for (auto it = vars.begin(); it != vars.end(); ++it)
			std::cout << " " << (it - vars.begin()) << ") " << *it << std::endl;
	}

	int getChoice(const int mCount) {
		int choice = FAIL;
		std::cout << std::endl << "Choose point: ";
		while (getNum(&choice) == FAIL || choice < 0 || choice > mCount)
			std::cout << std::endl << "Wrong value! Choose point: ";
		std::cout << std::endl;
		return choice;
	}
};