#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


namespace
{
	struct Edge
	{
		int vertex1, vertex2;
		int weight;

		Edge(int x, int y, int w) : vertex1(x), vertex2(y), weight(w) {}
	};

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
				sets[y] = x;
				rank[x]++;
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

		void insertionSort(std::vector <Edge>& edges)
		{
			for (int i = 1; i < edges.size(); i++)
			{
				int j = i - 1;
				Edge current = edges[i];

				while (j > -1 and edges[j].weight > current.weight)
				{
					edges[j + 1] = edges[j];
					j--;
				}

				edges[j + 1] = current;
			}
		}

		std::vector <std::vector <int>> turnIntoAdjacencyMatrix(bool directed)
		{
			std::vector <std::vector <int>> adjMatrix(vertices.size(), std::vector <int>(vertices.size(), -1));

			for (const Edge& edge : edges)
			{
				if (edge.weight >= 0)
				{
					if (edge.weight > adjMatrix[edge.vertex1][edge.vertex2])
						adjMatrix[edge.vertex1][edge.vertex2] = edge.weight;

					if (!directed)
						if (edge.weight > adjMatrix[edge.vertex2][edge.vertex1])
							adjMatrix[edge.vertex2][edge.vertex1] = edge.weight;
				}
				else
				{
					std::cout << "\n\n\t\tEdge: "
						<< "\tVertices: " << edge.vertex1 + 1 << " --> " << edge.vertex2 + 1 << ", "
						<< "Weight: " << edge.weight
						<< "\n\t\tHas a negative weight and therefore will not be taken into account"
						<< "\n\t\tsince Dijkstra's algorithm is not accurate with negative weights.";
				}
			}

			return adjMatrix;
		}


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

			insertionSort(sortedEdges);

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
				std::cout << "\n\n\tMinimum cost spanning tree total weight: " << totalWeight;
			else
				std::cout << "\n\n\tMinimum spanning tree could not be formed using the entered edges!";
			pause();

			delete Dset;
		}

		void Dijkstra(int source, bool directed)
		{
			int MAX = std::numeric_limits <int>::max();
			std::vector <std::vector <int>> adjMatrix = turnIntoAdjacencyMatrix(directed);
			std::vector <int> dist(vertices.size(), MAX);
			std::vector <bool> visited(vertices.size(), false);

			dist[source] = 0;

			for (int i = 0; i < vertices.size() - 1; i++)
			{
				int min = MAX;
				int minIndex = 0;

				for (int v = 0; v < vertices.size(); v++)
				{
					if (visited[v] == false && dist[v] <= min)
					{
						min = dist[v];
						minIndex = v;
					}
				}
				int u = minIndex;

				visited[u] = true;

				for (int v = 0; v < vertices.size(); v++)
				{
					if (!visited[v] and adjMatrix[u][v] >= 0 && dist[u] != MAX and dist[u] + adjMatrix[u][v] < dist[v])
						dist[v] = dist[u] + adjMatrix[u][v];
				}
			}

			std::cout << "\n\n\tDijkstra's algorithm result:";
			for (int i = 0; i < vertices.size(); i++)
			{
				if (dist[i] == MAX)
					std::cout << "\n\t\tVertex " << i + 1 << " and source are not connected.";
				else
					std::cout << "\n\t\tVertex " << i + 1 << " distance from source: " << dist[i];
			}
			pause();
		}

		int breadthFirstSearch(int source, int destination)
		{
			std::vector <std::vector <int>> adjMatrix = turnIntoAdjacencyMatrix(false);	// false == undirected graph

			std::queue <std::pair<int, int>> queue;
			std::vector <bool> visited(vertices.size(), false);
			std::pair <int, int> current;
			queue.push(std::make_pair(source, 0));
			visited[source] = true;

			while (!queue.empty())
			{
				current = queue.front();
				queue.pop();

				if (current.first == destination)
				{
					return current.second;
				}

				for (int i = 0; i < vertices.size(); i++)
				{
					if (adjMatrix[current.first][i] >= 0 and visited[i] == false)
					{
						queue.push(std::make_pair(i, current.second + 1));
						visited[i] = true;
					}
				}
			}

			return -1;
		}

		void printEdges()
		{
			for (int i = 0; i < edges.size(); i++)
			{
				std::cout << "\n\t\tEdge " << i + 1 << ": "
					<< "\tVertices: " << edges[i].vertex1 + 1 << " --> " << edges[i].vertex2 + 1 << ", "
					<< "Weight: " << edges[i].weight;
			}
		}

		bool isValidVertex(int vertex)
		{
			return vertex > 0 and vertex <= vertices.size();
		}

		void pause()
		{
			std::cout << "\n\n\t\t";
			system("pause");
		}
	};
}

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

void enterSource(int& vertex)
{
	std::cout << "\n\t\tEnter source vertex: ";
	std::cin >> vertex;
}

void enterDestination(int& vertex)
{
	std::cout << "\n\t\tEnter destination vertex: ";
	std::cin >> vertex;
}

void graph()
{
	int option;
	int vertex1;
	int vertex2;
	int weight;
	Graph* myGraph = new Graph;

	while (true)
	{
		system("cls");
		std::cout << "\n\n\tGraph:\n";
		std::cout << "\n\tNumber of vertices:  " << myGraph->getTotalVertices();
		std::cout << "\n\tEdges:";
		myGraph->printEdges();
		std::cout << "\n\n\tChoose an option:"
			<< "\n\t\t1 - Add vertex"
			<< "\n\t\t2 - Remove vertex (also removes its edges)"
			<< "\n\t\t3 - Add edge"
			<< "\n\t\t4 - Remove edges with entered information"
			<< "\n\t\t5 - Minimum cost spanning tree | Kruskal's algorithm | undirected graph only"
			<< "\n\t\t6 - Shortest path from source to earch other vertex | Dijkstra's algorithm | directed or undirected graph"
			<< "\n\t\t7 - Shortest path from source to destination without weights | Breadth First Search | undirected graph only"
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
				myGraph->pause();
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
			myGraph->pause();
		}
		else if (option == 4)
		{
			enterEdgeInfo(vertex1, vertex2, weight);
			vertex1--;
			vertex2--;
			if (myGraph->removeEdge(vertex1, vertex2, weight))
				continue;

			std::cout << "\n\t\tNo edges with that information found!";
			myGraph->pause();
		}
		else if (option == 5)
		{
			myGraph->Kruskal();
		}
		else if (option == 6)
		{
			enterSource(vertex1);

			if (myGraph->isValidVertex(vertex1))
			{
				std::cout << "\n\t\tCompute the graph as directed or undirected?\n\t\t\t(undirected = 0; directed = any other number): ";
				std::cin >> option;
				myGraph->Dijkstra(vertex1 - 1, option);
				continue;
			}
			std::cout << "\n\t\tEntered vertex is not in the graph";
			myGraph->pause();
		}
		else if (option == 7)
		{
			enterSource(vertex1);
			enterDestination(vertex2);
			if (myGraph->isValidVertex(vertex1) and myGraph->isValidVertex(vertex2))
			{
				int result = myGraph->breadthFirstSearch(vertex1 - 1, vertex2 - 1);
				if (result == -1)
					std::cout << "\n\n\tVertex " << vertex1 << " is not connected to vertex " << vertex2;
				else
					std::cout << "\n\n\tVertex " << vertex1 << " is " << result << " vertices away from vertex " << vertex2;
			}
			else
			{
				std::cout << "\n\t\tOne of the entered vertices is not in the graph";
			}
			myGraph->pause();
		}
		else if (option == 10)
		{
			break;
		}
		else
		{
			std::cout << "\n\t\tInvalid option!";
			myGraph->pause();
		}
	}
	delete myGraph;
}