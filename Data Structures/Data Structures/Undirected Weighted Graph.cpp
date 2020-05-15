#include <iostream>
#include <vector>

namespace
{
	struct Edge
	{
		int vertex1, vertex2;
		int weight;

		Edge(int x, int y, int w) : vertex1(x), vertex2(y), weight(w) {}
	};
}

class DisjointSet
{
private:
	std::vector <int> sets;
	std::vector <int> rank;

public:
	DisjointSet(int numOfVertices)
	{
		sets.resize(numOfVertices);
		rank.resize(numOfVertices);
		for (int i = 0; i < numOfVertices; i++)
		{
			sets[i] = i;
		}
	}

	void merge(int vertex1, int vertex2)
	{
		int x = find(vertex1);
		int y = find(vertex2);

		if (rank[x] > rank[y])
		{
			sets[y] = x;
		}
		else if (rank[x] < rank[y])
		{
			sets[x] = y;
		}
		else
		{
			sets[x] = y;
			rank[y]++;
		}
	}


	int find(int vertex)
	{
		while (vertex != sets[vertex])
		{
			vertex = sets[vertex];
		}

		return vertex;
	}
};


class Graph
{
private:
	std::vector <int> vertices;
	std::vector <Edge> edges;

public:
	int getTotalVertices() { return vertices.size(); }

	void addVertex()
	{
		vertices.push_back(vertices.size());
	}

	void removeVertex()
	{
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].vertex1 == vertices.size() - 1 or edges[i].vertex2 == vertices.size() - 1)
			{
				edges.erase(edges.begin() + i);
				i--;
			}
		}
		vertices.pop_back();
	}

	void addEdge(int vertex1, int vertex2, int weight)
	{
		edges.push_back(Edge(vertex1, vertex2, weight));
	}

	bool removeEdge(int vertex1, int vertex2, int weight)
	{
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].vertex1 == vertex1 and edges[i].vertex2 == vertex2 and edges[i].weight == weight)
			{
				edges.erase(edges.begin() + i);
				return true;
			}
		}
		return false;
	}

	void Kruskal()
	{
		std::vector <Edge> sortedEdges = edges;

		for (int i = 0; i < sortedEdges.size(); i++)
		{
			for (int j = 0; j < sortedEdges.size() - 1; j++)
			{
				if (sortedEdges[j].weight > sortedEdges[j + 1].weight)
					std::swap(sortedEdges[j], sortedEdges[j + 1]);
			}
		}

		DisjointSet* Dset = new DisjointSet(vertices.size());
		int vertex1, vertex2, weight;
		int joined = 0;
		int totalWeight = 0;
		bool treeExists = false;

		for (int i = 0; i < edges.size(); i++)
		{
			vertex1 = sortedEdges[i].vertex1;
			vertex2 = sortedEdges[i].vertex2;
			weight = sortedEdges[i].weight;

			if (Dset->find(vertex1) != Dset->find(vertex2))
			{
				totalWeight += sortedEdges[i].weight;
				joined++;
				Dset->merge(vertex1, vertex2);
			}
			if (joined == vertices.size() - 1)
			{
				treeExists = true;
				break;
			}
		}

		if (treeExists)
			std::cout << "\n\n\tMinimum spanning tree total weight: " << totalWeight;
		else
			std::cout << "\n\n\tMinimum spanning tree could not be formed using the entered edges!";
		std::cout << "\n\n\t\t";
		system("pause");

		delete Dset;
	}

	void Prims()
	{

	}

	void printEdges()
	{
		for (int i = 0; i < edges.size(); i++)
		{
			std::cout << "\n\t\tEdge " << i + 1 << ":"
				<< "\tVertices: " << edges[i].vertex1 + 1 << " <--> " << edges[i].vertex2 + 1 << ", "
				<< "Weight: " << edges[i].weight;
		}
	}

	bool isValidVertex(int vertex)
	{
		return vertex > 0 and vertex <= vertices.size();
	}
};

void enterEdgeInfo(int& vertex1, int& vertex2, int& weight)
{
	std::cout << "\n\tEnter edge information:\n";
	std::cout << "\n\t\tEnter first vertex: ";
	std::cin >> vertex1;
	std::cout << "\n\t\tEnter second vertex: ";
	std::cin >> vertex2;
	std::cout << "\n\t\tEnter edge weight: ";
	std::cin >> weight;
}


void undirectedWeightedGraph()
{
	int option;
	int vertex1;
	int vertex2;
	int weight;
	Graph* myGraph = new Graph;

	while (true)
	{
		system("cls");
		std::cout << "\n\n\tUndirected Weighted Graph:\n";
		std::cout << "\n\tNumber of vertices:  " << myGraph->getTotalVertices();
		std::cout << "\n\tEdges:\n";
		myGraph->printEdges();
		std::cout << "\n\n\tChoose an option:"
			<< "\n\t\t1 - Add vertex"
			<< "\n\t\t2 - Remove vertex (also removes its edges)"
			<< "\n\t\t3 - Add edge"
			<< "\n\t\t4 - Remove edges with entered information"
			<< "\n\t\t5 - Use Kruskal's algorithm to determine minimum spanning tree total weight"
			<< "\n\t\t6 - "
			<< "\n\t\t10 - Back";
		std::cout << "\n\n\t\tOption: ";
		std::cin >> option;

		if (option == 1)
		{
			myGraph->addVertex();
		}
		else if (option == 2)
		{
			if (myGraph->getTotalVertices() == 0)
			{
				std::cout << "\n\t\tNo vertices to remove!";
				std::cout << "\n\n\t\t";
				system("pause");
				continue;
			}

			myGraph->removeVertex();
		}
		else if (option == 3)
		{
			enterEdgeInfo(vertex1, vertex2, weight);
			if (myGraph->isValidVertex(vertex1) and myGraph->isValidVertex(vertex2))
			{
				myGraph->addEdge(vertex1 - 1, vertex2 - 1, weight);
				continue;
			}

			std::cout << "\n\t\tInvalid edge information!";
			std::cout << "\n\n\t\t";
			system("pause");
		}
		else if (option == 4)
		{
			enterEdgeInfo(vertex1, vertex2, weight);
			vertex1--;
			vertex2--;
			if (myGraph->removeEdge(vertex1, vertex2, weight))
				continue;

			std::cout << "\n\t\tNo edges with that information found!";
			std::cout << "\n\n\t\t";
			system("pause");
		}
		else if (option == 5)
		{
			myGraph->Kruskal();
		}
		else if (option == 6)
		{
			myGraph->Prims();
		}
		else if (option == 10)
		{
			delete myGraph;
			return;
		}
		else
		{
			std::cout << "\n\t\tInvalid option!\n\n";
			system("pause");
		}
	}
}