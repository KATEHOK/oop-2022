#ifndef APP
#include "app.h"
#endif


namespace dialog {

	int getNum(int* pNum) {
		if (pNum == nullptr) throw std::invalid_argument("pNum == nullptr in getNum()");
		int status = FAIL;

		std::cin >> *pNum;
		if (std::cin.good()) status = SUCCESS;
		else std::cin.clear();

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return status;
	}

	int getNum(const char* pFMsg, const char* pSMsg) {
		int value = 0;
		std::cout << pFMsg;
		while (getNum(&value) == FAIL)
			std::cout << std::endl << pSMsg;
		std::cout << std::endl;
		return value;
	}

	int confirm() {
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
		if (choice == 'N') return FAIL;
		return SUCCESS;
	}

	int exit(Sequence* pS) { return FAIL; }

	int initFree(Sequence* pS) {
		if (pS == nullptr) throw std::invalid_argument("pS == nullptr in initFree()");
		Sequence free;
		*pS = free;
		std::cout << *pS << std::endl;
		return SUCCESS;
	}

	int initOne(Sequence* pS) {
		if (pS == nullptr) throw std::invalid_argument("pS == nullptr in initOne()");

		int value = getNum("Enter integer: ", "Invalid value! Enter integer: ");
		*pS = value;

		std::cout << *pS << std::endl;
		return SUCCESS;
	}

	int initByArray(Sequence* pS) {
		if (pS == nullptr) throw std::invalid_argument("pS == nullptr in initByArray()");

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

		Sequence res(i, pArr);
		*pS = res;

		std::cout << *pS << std::endl;
		return SUCCESS;
	}

	int printSize(Sequence* pS) {
		if (pS == nullptr) throw std::invalid_argument("pS == nullptr in printSize()");
		std::cout << "Size of current sequence: " << pS->getSize() << std::endl;
		return SUCCESS;
	}

	int printMaxSize(Sequence* pS) {
		if (pS == nullptr) throw std::invalid_argument("pS == nullptr in printMaxSize()");
		std::cout << "Max size of current sequence: " << pS->getMaxSize() << std::endl;
		return SUCCESS;
	}

	int printElement(Sequence* pS) {
		if (pS == nullptr) throw std::invalid_argument("pS == nullptr in printElement()");
		if (pS->getSize() == 0) {
			std::cout << "Sequence is free!" << std::endl;
			return SUCCESS;
		}

		int value = 0;
		std::cout << "Enter id (extended natural from 0 to "
			<< pS->getSize() - 1 << "): ";

		while (getNum(&value) == FAIL || value < 0 || value >= pS->getSize())
			std::cout << std::endl << "Invalid value! Enter extended natural: ";
		std::cout << std::endl;

		std::cout << "[" << value << "] " << (*pS)[value] << std::endl;
		return SUCCESS;
	}

	int input(Sequence* pS) {
		if (pS == nullptr) throw std::invalid_argument("pS == nullptr in input()");
		std::cout << "Enter via space integer or something else if you want to stop: ";
		std::cin >> *pS;

		std::cout << std::endl << "Current sequence: " << *pS << std::endl;
		return SUCCESS;
	}

	int output(Sequence* pS) {
		if (pS == nullptr) throw std::invalid_argument("pS == nullptr in output()");
		std::cout << "Current sequence: " << *pS << std::endl;
		return SUCCESS;
	}

	int plus(Sequence* pS) {
		if (pS == nullptr) throw std::invalid_argument("pS == nullptr in plus()");
		Sequence other;

		std::cout << "Making the second sequence" << std::endl;
		std::cout << "Enter via space integer or something else if you want to stop: ";

		std::cin >> other;
		std::cout << std::endl;

		Sequence res = *pS + other;
		std::cout << std::endl << *pS << " + " << other << " = " << res << std::endl;

		std::cout << "Do you want to replace your current sequence?" << std::endl;
		if (confirm() == SUCCESS) (*pS) = res;
		return SUCCESS;
	}

	int findMonotonicity(Sequence* pS) {
		if (pS == nullptr) throw std::invalid_argument("pS == nullptr in findMonotonicity()");
		int order = 0;

		std::cout << "Enter 0 to find ascending subsequence "
			<< "or 1 to find descending subsequence: ";
		while (getNum(&order) == FAIL || (order != 0 && order != 1))
			std::cout << std::endl << "Invalid value! Try again: ";
		std::cout << std::endl;

		Sequence sub = pS->findMonotonicity(order);
		std::cout << "Subsequence: " << sub << std::endl;

		std::cout << "Do you want to replace your current sequence?" << std::endl;
		if (confirm() == SUCCESS) *pS = sub;
		return SUCCESS;
	}

	int insert(Sequence* pS) {
		if (pS == nullptr) throw std::invalid_argument("pS == nullptr in insert()");
		int value = getNum("Enter new value (integer): ", "Invalid value! Try again: ");
		
		*pS += value;
		return SUCCESS;
	}

	int printGroupsCount(Sequence* pS) {
		if (pS == nullptr) throw std::invalid_argument("pS == nullptr in printGroupsCount()");
		std::cout << "There are " << pS->getGroupsCount()
			<< " groups in the sequence" << std::endl;
		return SUCCESS;
	}

	int printSameCount(Sequence* pS) {
		if (pS == nullptr) throw std::invalid_argument("pS == nullptr in printSameCount()");

		int value = getNum("Enter value (integer): ", "Invalid value! Try again: ");
		std::cout << "There are " << pS->getSameCount(value)
			<< " elements equal " << value << " in the sequence" << std::endl;
		return SUCCESS;
	}
};