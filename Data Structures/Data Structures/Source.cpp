#include <iostream>


void singlyLinkedList();
void stack();
void queue();
void undirectedWeightedGraph();


int main()
{
	int option;

	while (true)
	{
		system("cls");
		std::cout << "\n\tData structure simulator!";

		std::cout << "\n\n\tChoose a data structure to simulate:"
			<< "\n\t\t1 - Singly Linked List"
			<< "\n\t\t2 - Stack"
			<< "\n\t\t3 - Queue"
			<< "\n\t\t4 - "
			<< "\n\t\t5 - "
			<< "\n\t\t6 - Graph"
			<< "\n\t\t7 - "
			<< "\n\t\t8 - "
			<< "\n\t\t10 - Exit"
			<< "\n\n\t\tChoise: ";

		std::cin >> option;

		if (option == 1)
		{
			singlyLinkedList();
		}
		else if (option == 2)
		{
			stack();
		}
		else if (option == 3)
		{
			queue();
		}
		else if (option == 4)
		{
		}
		else if (option == 5)
		{
		}
		else if (option == 6)
		{
			undirectedWeightedGraph();
		}
		else if (option == 7)
		{
		}
		else if (option == 8)
		{
		}
		else if (option == 10)
		{
			std::cout << "\n\n\tThank you for playing!\n\n\n";
			return 0;
		}
		else
		{
			std::cout << "\n\t\tInvalid option!\n\n\t\t";
			system("pause");
		}
	}
}