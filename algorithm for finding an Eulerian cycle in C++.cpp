#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



struct Edge {                                                            // Data structure to store a graph edge
	int src, dest;
};

class Graph
{
public:

	vector<vector<int>> adjacent_vectors;

	                                                                    // A vector to store in-degree of each vertex in the graph
	vector<int> in;

	                                                                    // Graph Constructor
	Graph(int n, vector<Edge> const &edges = {})
	{
		                                                                 // resize both vectors to hold `n` elements each
		adjacent_vectors.resize(n);
		in.resize(n);

		                                                                 // add edges to the directed graph, and update in-degree for each edge
		for (auto &edge: edges) {
			addEdge(edge.src, edge.dest);
		}
	}

	                                                                     // Utility function to add an edge (u, v) to the graph
	void addEdge(int u, int v)
	{
		adjacent_vectors[u].push_back(v);
		in[v]++;
	}
};

                                                                         // Utility function to perform DFS traversal on the graph
void DFS(Graph const &graph, int u, vector<bool> &visited)
{
	                                                                     // mark the current node as visited
	visited[u] = true;

	                                                                     // do for every edge (u, v)
	for (int v: graph.adjacent_vectors[u])
	{
                                                                         // recur if `v` is not visited
		if (!visited[v]) {
			DFS(graph, v, visited);
		}
	}
}
                                                                        // Function to create transpose of a graph, i.e., the same graph
                                                                        // with the direction of every edge reversed
Graph buildTranspose(Graph const &graph, int n)
{
	Graph g(n);

	for (int u = 0; u < n; u++)
	{
                                                                       // for every edge (u, v), create a reverse edge (v, u)
                                                                       // in the transpose graph
		for (int v: graph.adjacent_vectors[u]) {
			g.addEdge(v, u);
		}
	}
	return g;
}

                                                                        // Function to check if all vertices of a graph with a non-zero degree are visited
bool isVisited(Graph const &graph, const vector<bool> &visited)
{
	for (int i = 0; i < visited.size(); i++)
	{
		if (graph.adjacent_vectors[i].size() && !visited[i]) {
			return false;
		}
	}
	return true;
}

                                                                        // Function to check if all vertices with a non-zero degree in a graph belong to a
                                                                        // single strongly connected component using Kosaraju’s algorithm
bool isSC(Graph const &graph, int n)
{
	                                                                   // keep track of all previously visited vertices
	vector<bool> visited(n);

	                                                                  // find the first vertex `i` with a non-zero degree, and start DFS from it
	int i;
	for (i = 0; i < n; i++)
	{
		if (graph.adjacent_vectors[i].size())
		{
			DFS(graph, i, visited);
			break;
		}
	}

	                                                                 // return false if DFS couldn't visit all vertices with a non-zero degree
	if (!isVisited(graph, visited)) {
		return false;
	}

	                                                                // reset the visited array
	fill(visited.begin(), visited.end(), false);

                                                                    // create a transpose of the graph
	Graph g = buildTranspose(graph, n);

                                                                    // perform DFS on the transpose graph using the same starting vertex as
                                                                    // used in the previous DFS call
	DFS(g, i, visited);

                                                                    // return true if second DFS also explored all vertices with a non-zero degree;
                                                                    // false otherwise
	return isVisited(g, visited);
}

                                                                    // Function to check if a directed graph has an Eulerian cycle
bool hasEulerianCycle(Graph const &graph, int n)
{
	                                                                // check if every vertex has the same in-degree and out-degree
	for (int i = 0; i < n; i++)
	{
		if (graph.adjacent_vectors[i].size() != graph.in[i]) {
			return false;
		}
	}

                                                                    // check if all vertices with a non-zero degree belong to a single
                                                                    // strongly connected component
	return isSC(graph, n);
}

int main()
{
    vector<Edge> edges = {{0, 1},{0, 6},{0, 2},{0, 4},{1, 6},{1, 5},{1, 3},{2, 3},{2, 4},{2, 7}, {3, 5}, {3, 7},{4, 10},{4, 8},{5, 11},{5, 9},{6, 9},{6, 8},{7, 11},{7, 10},{8, 10},{8, 9},{9, 11},{10, 11}};
	                                                                // vector of graph edges
	/*vector<Edge> edges = {
		{1, 2},
        {1, 7},
        {1, 3},
        {1, 5},
        {2, 7},
        {2, 6},
        {2, 4},
        {3, 4},
        {3, 5},
        {3, 8},
        {4, 6},
        {4, 8},
        {5, 11},
        {5, 9},
        {6, 12},
        {6, 10},
        {7, 10},
        {7, 9},
        {8, 12},
        {8, 11},
        {9, 11},
        {9, 10},
        {10, 12},
        {11, 12}
	};
*/
	                                                                // total number of nodes in the graph (labelled from 0 to 4)
	int n = 12;

	                                                                // build a directed graph from the above edges
	Graph graph(n, edges);

	if (hasEulerianCycle(graph, n)) {
		cout << "The graph has an Eulerian cycle" << endl;
	}
	else {
		cout << "The Graph does not contain Eulerian cycle" << endl;
	}

	return 0;
}
