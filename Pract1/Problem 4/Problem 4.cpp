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

Vertex readVertex() {
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

bool setToExistingIfNeeded(Vertex& vertex, Edge*& edges, const size_t& index) {
	if (!edges)
	{
		return false;
	}

	Vertex* existingV = getVertex(edges, index, vertex.name);

	if (existingV) {
		vertex = *existingV;
	}

	return true;
}

Edge* initializeEdges(size_t edgesCount)
{
	Edge* edges = new Edge[edgesCount];

	for (size_t i = 0; i < edgesCount; i++)
	{
		Vertex a = readVertex();
		Vertex b = readVertex();

		setToExistingIfNeeded(a, edges, i);
		setToExistingIfNeeded(b, edges, i);

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
	graph.verticesCount = edgesCount * 2;

	return graph;
}

void deepCopyEdges(const Edge*& source, size_t edgesCount, Edge*& target) {
	for (size_t i = 0; i < edgesCount; i++)
	{
		target[i].start = source[i].start;
		target[i].end = source[i].end;
	}
}

void addEdgeToGraph(Vertex& start, Vertex& end, Graph& graph) {
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

void freeGraphMemory(Graph& graph) {
	delete[] graph.edges;
}

// currently here
unsigned findVertexDegree(Vertex& vertex, Graph& graph) {
	for (size_t i = 0; i < graph.edgesCount; i++)
	{
		getVertex(graph.edges, graph.edgesCount, vertex.name);
	}
}

int main()
{
	cout << "Enter m: " << endl;
	// m is the number of edges of the graph we would like to create
	unsigned m = 0;
	cin >> m;

	Graph graph = initializeGraph(m);

	freeGraphMemory(graph);

	return 0;
}