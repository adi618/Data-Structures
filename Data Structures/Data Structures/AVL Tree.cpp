#include <iostream>
#include <algorithm>
#include <queue>

namespace
{
	struct Node
	{
		Node* left;
		Node* right;
		int value;
		int height;

		Node(int value) : value(value), height(1), right(nullptr), left(nullptr) {}
	};
}

class AVLtree
{
private:
	Node* root;

	void heightAssignment(Node* current, int& leftHeight, int& rightHeight)
	{
		if (current != nullptr)
		{
			if (current->left != nullptr)
				leftHeight = current->left->height;

			if (current->right != nullptr)
				rightHeight = current->right->height;
		}
	}

	int nodeHeight(Node* current)
	{
		int leftHeight = 0;
		int rightHeight = 0;

		heightAssignment(current, leftHeight, rightHeight);

		return std::max(leftHeight, rightHeight) + 1;
	}

	int balanceFactor(Node* current)
	{
		int leftHeight = 0;
		int rightHeight = 0;

		heightAssignment(current, leftHeight, rightHeight);

		return leftHeight - rightHeight;
	}


	Node* LL_Rotation(Node* current)	// LL rotation == when the two nodes forming an imbalance are both on the left side of the node at which
	{									// the imbalance is formed, example:
		Node* currLeft = current->left;							//        50
		Node* currLeftsRight = current->left->right;			//		 /								   40
		// curr == currents										//      40	 	 after LL rotation =>	  /  \
																//     / 								 30  50
		currLeft->right = current;								//	  30
		current->left = currLeftsRight;															

		current->height = nodeHeight(current);
		currLeft->height = nodeHeight(currLeft);

		if (current == root)
			root = currLeft;

		return currLeft;
	}
	//			50
	//		   /								45
	//		 40			after LR =>			   /  \
	//		   \							 40    50
	//          45
	Node* LR_Rotation(Node* current)
	{
		Node* currLeft = current->left;
		Node* currLeftsRight = currLeft->right;

		currLeft->right = currLeftsRight->left;
		current->left = currLeftsRight->right;

		currLeftsRight->left = currLeft;
		currLeftsRight->right = current;

		current->height = nodeHeight(current);
		currLeft->height = nodeHeight(currLeft);
		currLeftsRight->height = nodeHeight(currLeftsRight);

		if (current == root)
			root = currLeftsRight;

		return currLeftsRight;
	}

	//			50
	//		      \								60
	//		      60		after RR =>		   /  \
	//		   		\						  50   70
	//				70
	Node* RR_Rotation(Node* current)
	{
		Node* currRight = current->right;
		Node* currRightsLeft = currRight->left;

		currRight->left = current;
		current->right = currRightsLeft;

		current->height = nodeHeight(current);
		currRight->height = nodeHeight(currRight);

		if (current == root)
			root = currRight;

		return currRight;
	}

	//			50
	//		  	  \								55
	//		 	   60		after RL =>		   /  \
	//		  	  /							 50    60
	//			 55	
	Node* RL_Rotation(Node* current)
	{
		Node* currRight = current->right;
		Node* currRightsLeft = currRight->left;

		currRight->left = currRightsLeft->right;
		current->right = currRightsLeft->left;

		currRightsLeft->right = currRight;
		currRightsLeft->left = current;

		current->height = nodeHeight(current);
		currRight->height = nodeHeight(currRight);
		currRightsLeft->height = nodeHeight(currRightsLeft);

		if (current == root)
			root = currRightsLeft;

		return currRightsLeft;
	}

public:
	AVLtree() : root(nullptr) {}

	Node* getRoot() { return root; }

	Node* insert(Node* current, int value)
	{
		Node* t = nullptr;

		if (current == nullptr)
		{
			t = new Node(value);
			if (this->root == nullptr)
				root = t;
			return t;
		}

		if (value < current->value)
			current->left = insert(current->left, value);
		else if (value >= current->value)
			current->right = insert(current->right, value);

		current->height = nodeHeight(current);

		int BF = balanceFactor(current);
		int BFleft = balanceFactor(current->left);
		int BFright = balanceFactor(current->right);

		if (BF == 2 and BFleft == 1)
			return LL_Rotation(current);

		if (BF == 2 && BFleft == -1)
			return LR_Rotation(current);

		if (BF == -2 && BFright == -1)
			return RR_Rotation(current);

		if (BF == -2 && BFright == 1)
			return RL_Rotation(current);

		return current;
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
				return;
			}
		}
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

	void printBranches()
	{
		if (root == nullptr)
			return;

		Node* current;

		std::queue <Node*> queue;

		queue.push(root);

		std::cout << "\n\n\tBranches: ";
		while (queue.size() > 0)
		{
			current = queue.front();
			queue.pop();

			if (current->left != nullptr)
				std::cout << "\n\t\tParent: " << current->value << " Left Child: " << current->left->value;

			if (current->right != nullptr)
				std::cout << "\n\t\tParent: " << current->value << " Right Child: " << current->right->value;

			if (current->left)
				queue.push(current->left);

			if (current->right)
				queue.push(current->right);
		}
	}

	~AVLtree()
	{
		if (root != nullptr)
			deleteNodes(root);
	}

	void deleteNodes(Node* current)
	{
		if (current->left != nullptr)
			deleteNodes(current->left);

		if (current->right != nullptr)
			deleteNodes(current->right);

		delete current;
	}
};

void enterNumber(int& num);		// function defined in Graph.cpp

void AVL()
{
	int option;
	int num;
	AVLtree myTree;

	while (true)
	{
		system("cls");
		std::cout << "\n\n\tBalanced BST | AVL Tree:";
		myTree.printTree();
		myTree.printBranches();
		std::cout << "\n\n\tChoose an option:"
			<< "\n\t\t1 - Insert a number into the AVL tree"
			<< "\n\t\t2 - Remove a number from the AVL tree"
			<< "\n\t\t10 - Back"
			<< "\n\n\t\tOption: ";

		std::cin >> option;

		if (option == 1)
		{
			enterNumber(num);
			myTree.insert(myTree.getRoot(), num);
		}
		else if (option == 2)
		{
			enterNumber(num);
			myTree.remove(num);
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