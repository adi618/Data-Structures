#include <iostream>
#include <queue>
#include <vector>

namespace {
	struct Node
	{
		int value;
		Node* right;
		Node* left;

		Node(int value) :value(value), right(nullptr), left(nullptr) {}
	};
}

class BinarySearchTree
{
private:
	Node* root;
	int totalNodes;

public:
	BinarySearchTree() : root(nullptr), totalNodes(0) {}

	Node* getRoot() { return root; }

	void insert(int value)
	{
		Node* newNode = new Node(value);
		totalNodes++;

		if (root == nullptr)
		{
			root = newNode;
			return;
		}

		Node* current = root;
		Node* previous = root;

		while (current != nullptr)
		{
			previous = current;
			if (value < current->value)
				current = current->left;
			else
				current = current->right;
		}

		if (value < previous->value)
			previous->left = newNode;
		else
			previous->right = newNode;
	}

	void remove(int value)
	{
		if (root->left == nullptr and root->right == nullptr)
		{
			Node* toDelete = root;
			root = nullptr;
			delete toDelete;
			return;
		}

		Node* current = root;
		Node* previous = root;

		while (current != nullptr)
		{
			if (value < current->value)
			{
				previous = current;			// traverse the tree to find the node
				current = current->left;
			}
			else if (value > current->value)
			{
				previous = current;
				current = current->right;
			}
			else	// if found, current is the node we want to delete, and previous is its parent node
			{
				Node* toDelete = current;

				if (current->left == nullptr and current->right == nullptr)	// the current node is a leaf
				{
					if (previous->left == current)
						previous->left = nullptr;
					else
						previous->right = nullptr;
					delete toDelete;
					return;
				}

				if (current->left == nullptr or current->right == nullptr)	// if the current node is a parent to only one node
				{
					if (previous->left == current)
						previous->left = current->left;
					else
						previous->right = current->right;
					delete toDelete;
					return;
				}

				// the current node has two children
				Node* temp = current->right;		// temp is the current's right child. we only check the right child of current
													// because the left child cannot be a successor
				if (temp->left == nullptr and temp->right == nullptr)	// if temp doesnt have children
				{
					current->value = temp->value;
					current->right = nullptr;
					delete temp;
					return;
				}

				if (temp->left == nullptr and temp->right != nullptr)	// if temp has a right child
				{
					current->value = temp->value;
					current->right = temp->right;
					delete temp;
					return;
				}

				while (temp->left != nullptr)	// if temp has a left child, iterate to the lowest one
				{
					previous = temp;
					temp = temp->left;
				}

				current->value = temp->value;
				previous->left = nullptr;
				delete temp;

			}
		}
	}

	bool lookup(int value)
	{
		if (root == nullptr)
			return false;

		Node* current = root;

		while (current != nullptr)
		{
			if (value < current->value)
				current = current->left;
			else if (value > current->value)
				current = current->right;
			else
				return true;
		}
		return false;
	}

	std::vector <int> BreadthFirstSearch()
	{
		Node* current = root;

		std::vector <int> result;
		std::queue <Node*> queue;

		queue.push(current);

		while (queue.size() > 0)
		{
			current = queue.front();
			queue.pop();

			result.push_back(current->value);

			if (current->left)
				queue.push(current->left);

			if (current->right)
				queue.push(current->right);
		}

		return result;
	}

	int valueSum(Node* current)
	{
		if (current == nullptr)
			return 0;

		return current->value + valueSum(current->left) + valueSum(current->right);
	}

	void DFSpreOrder(Node* current)
	{
		std::cout << current->value << " ";

		if (current->left != nullptr)
			DFSpreOrder(current->left);

		if (current->right != nullptr)
			DFSpreOrder(current->right);
	}

	void DFSinOrder(Node* current)
	{
		if (current->left != nullptr)
			DFSpreOrder(current->left);

		std::cout << current->value << " ";

		if (current->right != nullptr)
			DFSpreOrder(current->right);
	}

	void DFSpostOrder(Node* current)
	{
		if (current->left != nullptr)
			DFSpreOrder(current->left);

		if (current->right != nullptr)
			DFSpreOrder(current->right);

		std::cout << current->value << " ";
	}

	void printTree()
	{
		if (root == nullptr)
			return;

		std::pair<Node*, int> current;

		std::queue <std::pair<Node*, int>> queue;

		queue.push(std::make_pair(root, 0));
		int level = 0;

		std::cout << "\n\t\t\t\t";
		while (queue.size() > 0)
		{
			current = queue.front();
			queue.pop();

			if (level != current.second)
			{
				std::cout << "\n\t\t\t\t";
				level = current.second;
			}

			std::cout << current.first->value << "  ";

			if (current.first->left)
				queue.push(std::make_pair(current.first->left, current.second + 1));

			if (current.first->right)
				queue.push(std::make_pair(current.first->right, current.second + 1));
		}
	}

	void pause()
	{
		std::cout << "\n\n\t\t";
		system("pause");
	}
};

void enterNumber(int& num);		// function defined in Graph.cpp

void enterIndex(int& index);		// function defined in Graph.cpp

void binarySearchTree()
{
	int option;
	int num;
	BinarySearchTree myTree;

	while (true)
	{
		system("cls");
		std::cout << "\n\n\tBinary Search Tree:      ";
		myTree.printTree();
		std::cout << "\n\n\tChoose an option:"
			<< "\n\t\t1 - Insert a number into the tree"
			<< "\n\t\t2 - Remove a number from the tree"
			<< "\n\t\t3 - Check if a number exists in the tree using Binary Search"
			<< "\n\t\t4 - Print the sum of all numbers in the tree"
			<< "\n\t\t5 - Print the numbers in the tree using Depth First Search preorder traversal"
			<< "\n\t\t6 - Print the numbers in the tree using Depth First Search inorder traversal"
			<< "\n\t\t7 - Print the numbers in the tree using Depth First Search postorder traversal"
			<< "\n\t\t10 - Back"
			<< "\n\n\t\tOption: ";

		std::cin >> option;

		if (option == 1)
		{
			enterNumber(num);
			myTree.insert(num);
		}
		else if (option == 2)
		{
			enterNumber(num);
			myTree.remove(num);
		}
		else if (option == 3)
		{
			std::cout << "\n\n\t\tEntered number does " << (myTree.valueSum(myTree.getRoot()) ? "" : "not") << " exist in the tree";
			myTree.pause();
		}
		else if (option == 4)
		{
			std::cout << "\n\n\t\tSum of all numbers in the tree: " << myTree.valueSum(myTree.getRoot());
			myTree.pause();
		}
		else if (option == 5)
		{
			std::cout << "\n\n\t\tDepth First Search preorder traversal result: ";
			myTree.DFSpreOrder(myTree.getRoot());
			myTree.pause();
		}
		else if (option == 6)
		{
			std::cout << "\n\n\t\tDepth First Search inorder traversal result: ";
			myTree.DFSinOrder(myTree.getRoot());
			myTree.pause();
		}
		else if (option == 7)
		{
			std::cout << "\n\n\t\tDepth First Search postorder traversal result: ";
			myTree.DFSpostOrder(myTree.getRoot());
			myTree.pause();
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