#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;

const size_t STR_MAX_LEN = 10;

struct Vertex
{
	char name[STR_MAX_LEN + 1];
};

struct Edge
{
	Vertex start;
	Vertex end;
};

struct Graph
{
	unsigned verticesCount;
	unsigned edgesCount;
	Edge* edges;
};

Vertex readVertex() 
{
	Vertex ver;
	cin >> ver.name;

	return ver;
}

Vertex* getVertex(Edge*& edges, size_t edgesCount, char* vertexName)
{
	if (!vertexName || !edges)
	{
		return nullptr;
	}

	for (size_t i = 0; i < edgesCount; i++)
	{
		if (strcmp(edges[i].start.name, vertexName) == 0)
		{
			return &(edges[i].start);
		}
		else if (strcmp(edges[i].end.name, vertexName) == 0)
		{
			return &(edges[i].end);
		}
	}

	return nullptr;
}

Edge* initializeEdges(size_t edgesCount)
{
	Edge* edges = new Edge[edgesCount];

	for (size_t i = 0; i < edgesCount; i++)
	{
		Vertex a = readVertex();
		Vertex b = readVertex();

		Edge newEdge = { a, b };

		edges[i] = newEdge;
	}

	return edges;
}

Graph initializeGraph(unsigned edgesCount)
{
	Edge* edges = initializeEdges(edgesCount);

	Graph graph;
	graph.edges = edges;
	graph.edgesCount = edgesCount;
	// FIX
	graph.verticesCount = edgesCount * 2;

	return graph;
}

void deepCopyEdges(const Edge*& source, size_t edgesCount, Edge*& target) 
{
	for (size_t i = 0; i < edgesCount; i++)
	{
		target[i] = source[i];
	}
}

// Take edge as an argument
void addEdgeToGraph(Vertex& start, Vertex& end, Graph& graph) 
{
	Edge* newEdges = new Edge[graph.edgesCount + 1];
	deepCopyEdges(graph.edges, graph.edgesCount, newEdges);

	delete[] graph.edges;
	graph.edges = newEdges;

	Edge additionalEdge;
	additionalEdge.start = start;
	additionalEdge.end = end;

	graph.edges[graph.edgesCount] = additionalEdge;
	graph.edgesCount++;
}

void freeEdges()
{

}

void freeGraphMemory(Graph& graph) 
{
	delete[] graph.edges;
}

// currently here
unsigned findVertexDegree(Vertex& vertex, Graph& graph) 
{
	for (size_t i = 0; i < graph.edgesCount; i++)
	{
		getVertex(graph.edges, graph.edgesCount, vertex.name);
	}
}

int main()
{
	cout << "Enter m: " << endl;
	// m is the number of edges of the graph we would like to create
	unsigned m;
	cin >> m;

	Graph graph = initializeGraph(m);

	freeGraphMemory(graph);

	return 0;
}