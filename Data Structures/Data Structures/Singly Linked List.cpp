#include <iostream>


namespace
{
	struct Node
	{
		int value;
		Node* next;

		Node(int value) : value(value), next(nullptr) {}
	};
}

class SinglyLinkedList
{
private:
	Node* head;
	Node* tail;
	int length;

	bool invalidIndex(int index)
	{
		if (index < 0 || index > length)
		{
			std::cout << "\n\t\tInvalid index!\n\n\t\t";
			system("pause");
			return true;
		}
		return false;
	}

	void traverseToIndex(int index, Node** current, Node** previous = nullptr)
	{
		while (*current != nullptr)
		{
			if (index == 1)
				break;

			if (previous != nullptr)
				*previous = *current;
			*current = (*current)->next;

			index--;
		}
	}
	

public:
	SinglyLinkedList() : head(nullptr), tail(nullptr), length(0) {}

	int getLength() { return length; }

	void append(int value)
	{
		Node* newNode = new Node(value);
		length++;

		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
			return;
		}

		tail->next = newNode;
		tail = newNode;
	}

	void prepend(int value)
	{
		Node* newNode = new Node(value);
		length++;

		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
			return;
		}

		newNode->next = head;
		head = newNode;
	}

	void insert(int value, int index)
	{
		if (invalidIndex(index))
		{
			return;
		}

		if (index == length)
		{
			append(value);
			return;
		}

		if (index == 0)
		{
			prepend(value);
			return;
		}

		Node* newNode = new Node(value);
		length++;

		Node* current = head;
		Node* previous = nullptr;

		traverseToIndex(index, &current, &previous);

		newNode->next = current;
		previous->next = newNode;
	}

	void removeFirst()
	{
		Node* toDelete = head;
		head = head->next;
		delete toDelete;
		length--;
	}

	void remove(int index)
	{
		if (invalidIndex(index + 1))
		{
			return;
		}

		if (index == 0)
		{
			removeFirst();
			return;
		}

		Node* previous = head;

		traverseToIndex(index, &previous);

		Node* toDelete = previous->next;
		previous->next = toDelete->next;
		length--;

		delete toDelete;

		if (index == length)
			tail = previous;
	}

	void reverse()
	{
		if (length == 0 || length == 1)
			return;

		Node* fast = head;
		Node* slow = nullptr;
		Node* slowest = nullptr;

		tail = head;

		while (fast != nullptr)
		{
			slowest = slow;
			slow = fast;
			fast = fast->next;
			slow->next = slowest;
		}
		head = slow;
	}

	void removeKValues(int value)
	{
		while (head != nullptr and head->value == value)
		{
			Node* toDelete = head;
			head = head->next;
			delete toDelete;
		}

		Node* current = head;

		while (current != nullptr and current->next != nullptr)
		{
			if (current->next->value == value)
			{
				Node* toDelete = current->next;
				length--;
				if (toDelete == tail)
					tail = current;
				current->next = current->next->next;
				delete toDelete;
			}
			else
				current = current->next;
		}
	}

	void printNodes()
	{
		Node* current = head;

		while (current != nullptr)
		{
			std::cout << current->value << " --> ";
			current = current->next;
		}

		std::cout << ((head == nullptr) ? "[empty]" : "nullptr");

		std::cout << "\n\n\tFirst number in the list: ";
		if (head == nullptr)
			std::cout << "[empty]";
		else
			std::cout << head->value;

		std::cout << "\n\tLast number in the list: ";
		if (head == nullptr)
			std::cout << "[empty]";
		else
			std::cout << tail->value;
	}

	bool isEmpty()
	{
		if (length == 0)
		{
			std::cout << "\n\t\tNothing to remove!\n\n\t\t";
			system("pause");
			return true;
		}
		return false;
	}

	~SinglyLinkedList()
	{
		Node* toDelete = head;

		while (head != nullptr)
		{
			head = head->next;
			delete toDelete;
			toDelete = head;
		}
	}
};


void enterNumber(int& num)
{
	std::cout << "\n\t\tEnter the number: ";
	std::cin >> num;
}

void enterIndex(int& index)
{
	std::cout << "\n\t\tEnter the index: ";
	std::cin >> index;
}

void singlyLinkedList()
{
	int option;
	int index;
	int num;
	SinglyLinkedList myList;

	while (true)
	{
		system("cls");
		std::cout << "\n\n\tLinked List:      ";
		myList.printNodes();

		std::cout << "\n\n\tChoose an option:"
			<< "\n\t\t1 - Add a number to the end of the list"
			<< "\n\t\t2 - Add a number to the beginning of the list"
			<< "\n\t\t3 - Add a number at a specific index of the list"
			<< "\n\t\t4 - Remove the last number of the list"
			<< "\n\t\t5 - Remove the first number of the list"
			<< "\n\t\t6 - Remove the number at a specific index of the list"
			<< "\n\t\t7 - Reverse list"
			<< "\n\t\t8 - Remove all nodes with entered number"
			<< "\n\t\t10 - Back"
			<< "\n\n\t\tOption: ";

		std::cin >> option;

		if (option == 1)
		{
			enterNumber(num);
			myList.append(num);
		}
		else if (option == 2)
		{
			enterNumber(num);
			myList.prepend(num);
		}
		else if (option == 3)
		{
			enterNumber(num);
			enterIndex(index);
			myList.insert(num, index);
		}
		else if (option == 4)
		{
			if (myList.isEmpty())
				continue;

			myList.remove(myList.getLength() - 1);
		}
		else if (option == 5)
		{
			if (myList.isEmpty())
				continue;

			myList.removeFirst();
		}
		else if (option == 6)
		{
			if (myList.isEmpty())
				continue;

			enterIndex(index);
			myList.remove(index);
		}
		else if (option == 7)
		{
			myList.reverse();
		}
		else if (option == 8)
		{
			enterNumber(num);
			myList.removeKValues(num);
		}
		else if (option == 10)
			return;
		else
		{
			std::cout << "\n\t\tInvalid option!\n\n\t\t";
			system("pause");
		}
	}
}