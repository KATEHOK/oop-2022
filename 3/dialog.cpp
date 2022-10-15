#ifndef APP
#include "app.h"
#endif


namespace dialog {

	int getNum(int* pNum) {
		if (pNum == NULL) return WRONG_PARAMS;
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

	int exit(Sequence** ppS) { return FAIL; }

	int initFree(Sequence** ppS) {
		if (ppS == NULL) return WRONG_PARAMS;
		if ((*ppS) != NULL) delete (*ppS);
		try { *ppS = new Sequence;	}
		catch (...) { return MEMORY_ERROR; }
		return SUCCESS;
	}

	int initOne(Sequence** ppS) {
		if (ppS == NULL) return WRONG_PARAMS;
		if ((*ppS) != NULL) delete (*ppS);
		int value = getNum("Enter integer: ", "Invalid value! Enter integer: ");

		try { *ppS = new Sequence(value); }
		catch (...) { return MEMORY_ERROR; }

		(*ppS)->output();
		std::cout << std::endl;
		return SUCCESS;
	}

	int initByArray(Sequence** ppS) {
		if (ppS == NULL) return WRONG_PARAMS;
		if ((*ppS) != NULL) delete (*ppS);

		int i;
		int pArr[MAX_SIZE];
		std::cout << "Enter numbers via space: ";

		for (i = 0; i < MAX_SIZE; i++) {
			std::cin >> pArr[i];
			if (!std::cin.good()) {
				std::cin.clear();
				break;
			}
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		try { *ppS = new Sequence(i, pArr); }
		catch (...) { return MEMORY_ERROR; }

		(*ppS)->output();
		std::cout << std::endl;
		return SUCCESS;
	}

	int printSize(Sequence** ppS) {
		if (ppS == NULL) return WRONG_PARAMS;
		if ((*ppS) == NULL) {
			std::cout << "Sequence was not inited!" << std::endl;
			return SUCCESS;
		}
		std::cout << "Size of current sequence: " << (*ppS)->getSize() << std::endl;
		return SUCCESS;
	}

	int printMaxSize(Sequence** ppS) {
		if (ppS == NULL) return WRONG_PARAMS;
		if ((*ppS) == NULL) {
			std::cout << "Sequence was not inited!" << std::endl;
			return SUCCESS;
		}
		std::cout
			<< "Max size of current sequence: " << (*ppS)->getMaxSize() << std::endl;
		return SUCCESS;
	}

	int printElement(Sequence** ppS) {
		if (ppS == NULL) return WRONG_PARAMS;
		if ((*ppS) == NULL) {
			std::cout << "Sequence was not inited!" << std::endl;
			return SUCCESS;
		}
		if ((*ppS)->getSize() == 0) {
			std::cout << "Sequence is free!" << std::endl;
			return SUCCESS;
		}

		int value = 0;
		std::cout << "Enter id (extended natural from 0 to "
			<< (*ppS)->getSize() - 1 << "): ";

		while (getNum(&value) == FAIL || value < 0 || value >= (*ppS)->getSize())
			std::cout << std::endl << "Invalid value! Enter extended natural: ";
		std::cout << std::endl;

		std::cout << "[" << value << "] " << (*ppS)->getElement(value) << std::endl;
		return SUCCESS;
	}

	int makeClone(Sequence** ppS) {
		if (ppS == NULL) return WRONG_PARAMS;
		if ((*ppS) == NULL) {
			std::cout << "Sequence was not inited!" << std::endl;
			return SUCCESS;
		}

		Sequence* pNew = (*ppS)->makeClone();
		if (pNew == NULL) {
			std::cout << "Something went wrong, clone was not created!" << std::endl;
			return SUCCESS;
		}

		std::cout << "Clone: ";
		pNew->output();
		std::cout << std::endl;

		std::cout << "Do you want to replace your current sequence?" << std::endl;
		if (confirm() == SUCCESS) {
			delete (*ppS);
			(*ppS) = pNew;
		}
		else delete pNew;
		return SUCCESS;
	}

	int input(Sequence** ppS) {
		if (ppS == NULL) return WRONG_PARAMS;
		if ((*ppS) == NULL) {
			std::cout << "Sequence was not inited!" << std::endl;
			return SUCCESS;
		}

		std::cout << "Enter via space integer or something else if you want to stop: ";
		(*ppS)->input();

		std::cout << std::endl << "Current sequence: ";
		(*ppS)->output();
		std::cout << std::endl;
		return SUCCESS;
	}

	int output(Sequence** ppS) {
		if (ppS == NULL) return WRONG_PARAMS;
		if ((*ppS) == NULL) {
			std::cout << "Sequence was not inited!" << std::endl;
			return SUCCESS;
		}

		std::cout << "Current sequence: ";
		(*ppS)->output();
		std::cout << std::endl;
		return SUCCESS;
	}

	int plus(Sequence** ppS) {
		if (ppS == NULL) return WRONG_PARAMS;
		if ((*ppS) == NULL) {
			std::cout << "Sequence was not inited!" << std::endl;
			return SUCCESS;
		}

		Sequence other;
		std::cout << "Making the second sequence" << std::endl;
		std::cout << "Enter via space integer or something else if you want to stop: ";
		other.input();
		std::cout << std::endl;

		Sequence* pRes = (*ppS)->plus(&other);
		if (pRes == NULL) {
			std::cout << "Sequence was not inited!" << std::endl;
			return SUCCESS;
		}

		std::cout << std::endl;
		(*ppS)->output();
		std::cout << " + ";
		other.output();
		std::cout << " = ";
		pRes->output();
		std::cout << std::endl;
		
		std::cout << "Do you want to replace your current sequence?" << std::endl;
		if (confirm() == SUCCESS) {
			delete (*ppS);
			(*ppS) = pRes;
		}
		else delete pRes;
		return SUCCESS;
	}

	int findMonotonicity(Sequence** ppS) {
		if (ppS == NULL) return WRONG_PARAMS;
		if ((*ppS) == NULL) {
			std::cout << "Sequence was not inited!" << std::endl;
			return SUCCESS;
		}

		int order = 0;
		std::cout << "Enter 0 to find ascending subsequence "
			<< "or 1 to find descending subsequence: ";
		while (getNum(&order) == FAIL || (order != 0 && order != 1))
			std::cout << std::endl << "Invalid value! Try again: ";
		std::cout << std::endl;

		Sequence* pNew = (*ppS)->findMonotonicity(order);
		if (pNew == NULL) {
			std::cout
				<< "Subsequence was not found or something went wrong!" << std::endl;
			return SUCCESS;
		}

		std::cout << "Subsequence: ";
		pNew->output();
		std::cout << std::endl;

		std::cout << "Do you want to replace your current sequence?" << std::endl;
		if (confirm() == SUCCESS) {
			delete (*ppS);
			(*ppS) = pNew;
		}
		else delete pNew;
		return SUCCESS;
	}

	int insert(Sequence** ppS) {
		if (ppS == NULL) return WRONG_PARAMS;
		if ((*ppS) == NULL) {
			std::cout << "Sequence was not inited!" << std::endl;
			return SUCCESS;
		}

		int value = getNum("Enter new value (integer): ", "Invalid value! Try again: ");
		value = (*ppS)->insert(value);
		if (value != SUCCESS)
			std::cout << "Value was not inserted! (code: " << value << ")" << std::endl;
		return SUCCESS;
	}

	int printGroupsCount(Sequence** ppS) {
		if (ppS == NULL) return WRONG_PARAMS;
		if ((*ppS) == NULL) {
			std::cout << "Sequence was not inited!" << std::endl;
			return SUCCESS;
		}
		std::cout << "There are " << (*ppS)->getGroupsCount()
			<< " groups in the sequence" << std::endl;
		return SUCCESS;
	}

	int printSameCount(Sequence** ppS) {
		if (ppS == NULL) return WRONG_PARAMS;
		if ((*ppS) == NULL) {
			std::cout << "Sequence was not inited!" << std::endl;
			return SUCCESS;
		}

		int value = getNum("Enter value (integer): ", "Invalid value! Try again: ");
		std::cout << "There are " << (*ppS)->getSameCount(value)
			<< " elements equal " << value << " in the sequence" << std::endl;
		return SUCCESS;
	}
};