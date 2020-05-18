#include <iostream>


namespace
{
	struct Node
	{
		int value;
		Node* next;

		Node(int value) :value(value), next(nullptr) {}
	};
}


class Queue
{
private:
	Node* first;
	Node* last;
	int totalNodes;

public:
	Queue() : first(nullptr), last(nullptr), totalNodes(0) {}

	int getTotalNodes() { return totalNodes; }

	void enqueue(int value)
	{
		Node* newNode = new Node(value);
		totalNodes++;

		if (first == nullptr)
		{
			first = newNode;
			last = newNode;
			return;
		}

		last->next = newNode;
		last = newNode;
	}

	int dequeue()
	{
		if (first == nullptr)
			return 0;

		if (first == last)
			last = nullptr;

		first = first->next;
		totalNodes--;
	}

	int peek()
	{
		if (first == nullptr)
			return 0;
		return first->value;
	}

	bool isEmpty()
	{
		return totalNodes == 0;
	}

	void printQueue()
	{
		if (totalNodes == 0)
		{
			std::cout << "  [empty]";
		}
		else
		{
			Node* temp = first;
			std::cout << temp->value;
			temp = temp->next;

			while (temp != nullptr)
			{
				std::cout << " <- " << temp->value;
				temp = temp->next;
			}
		}
	}

	~Queue()
	{
		Node* toDelete = first;

		while (first != nullptr)
		{
			first = first->next;
			delete toDelete;
			toDelete = first;
		}
	}
};


void queue()
{
	int option;
	int value;
	Queue myQueue;

	while (true)
	{
		system("cls");
		std::cout << "\n\n\tQueue:    ";
		myQueue.printQueue();
		std::cout << "\n\n\tChoose an option:"
			<< "\n\t\t1 - .dequeue()"
			<< "\n\t\t2 - .enqueue()"
			<< "\n\t\t3 - .top()"
			<< "\n\t\t10 - Exit";
		std::cout << "\n\n\t\tOption: ";
		std::cin >> option;

		if (option == 1)
		{
			std::cout << "\n\t\tEnter the number: ";
			std::cin >> value;
			myQueue.enqueue(value);
		}
		else if (option == 2)
		{
			if (myQueue.isEmpty())
			{
				std::cout << "\n\t\tQueue is empty!";
				std::cout << "\n\n\t\t";
				system("pause");
			}
			myQueue.dequeue();
		}
		else if (option == 3)
		{
			if (myQueue.isEmpty())
				std::cout << "\n\t\tQueue is empty!";
			else
				std::cout << "\n\t\tFirst in queue: " << myQueue.peek();
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