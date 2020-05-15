#include <iostream>
#include <string>
#include <vector>


namespace
{
	struct Node
	{
		std::string value;
		Node* next;

		Node(std::string value) :value(value), next(nullptr) {}
	};
}


class Stack
{
private:
	Node* top;
	int totalNodes;

public:
	Stack() : top(nullptr), totalNodes(0) {}

	int getTotalNodes() { return totalNodes; }

	void push(std::string num)
	{
		Node* newNode = new Node(num);
		totalNodes++;

		if (top == nullptr)
		{
			top = newNode;
			return;
		}
		Node* temp = top;

		top = newNode;
		top->next = temp;
	}

	std::string pop()
	{
		Node* temp = top;

		top = top->next;
		totalNodes--;

		return temp->value;
	}

	std::string peek()
	{
		if (top == nullptr)
			return 0;
		return top->value;
	}

	void printStack()
	{
		std::vector <std::string> values(10);

		Node* temp = top;

		std::cout << "  ----------------------\n";

		int i = totalNodes - 1;
		while (temp != nullptr)
		{
			values[i] = temp->value;
			temp = temp->next;
			i--;
		}

		for (int i = 9; i >= 0; i--)
		{
			spaces(values[i]);
		}

		return;
	}

	void spaces(const std::string& value)
	{
		int left = value.size() / 2;
		int right = value.size() - left;

		left = 10 - left;
		right = 10 - right;

		std::cout << "\t\t|";
		for (int i = 0; i < left; i++)
			std::cout << " ";

		std::cout << value;

		for (int i = 0; i < right; i++)
			std::cout << " ";
		std::cout << "|\n";
		std::cout << "\t\t----------------------\n";
	}

	void overflow()
	{
		for (int i = 0; i < 5; i++)
		{
			std::cout << "\n\tStack overflow!\n";
		}
		std::cout << "\n\n\n\t";
		system("pause");
	}
};


void stack()
{
	int option;
	std::string value;
	Stack myStack;

	while (true)
	{
		system("cls");
		if (myStack.getTotalNodes() > 10)
		{
			myStack.overflow();
			return;
		}
		std::cout << "\n\n\tChoose an option:"
			<< "\n\t\t1 - Add node - .push()"
			<< "\n\t\t2 - Remove node - .pop()"
			<< "\n\t\t3 - .top()"
			<< "\n\t\t10 - Back";
		std::cout << "\n\n\tStack:";
		myStack.printStack();
		std::cout << "\n\n\t\tOption: ";
		std::cin >> option;
		std::cin.ignore();

		if (option == 1)
		{
			std::cout << "\n\t\tEnter the data: ";
			getline(std::cin, value);
			myStack.push(value);
		}
		else if (option == 2)
		{
			if (myStack.getTotalNodes() == 0)
				std::cout << "\n\t\tStack is empty!";
			else
				std::cout << "\n\t\tTo be removed data: " << myStack.pop();
			std::cout << "\n\n\t\t";
			system("pause");
		}
		else if (option == 3)
		{
			if (myStack.getTotalNodes() == 0)
				std::cout << "\n\t\tStack is empty!";
			else
				std::cout << "\n\t\tData at the top of the stack: " << myStack.peek();
			std::cout << "\n\n\t\t";
			system("pause");
		}
		else if (option == 10)
			return;
		else
		{
			std::cout << "\n\t\tInvalid option!\n\n";
			system("pause");
		}
	}
}