#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;

const size_t STR_MAX_LEN = 10;
const size_t MAX_VERTICES = 128;

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

// Used for reading a vertex. If no extensibility is needed it could be omitted.
Vertex readVertex() 
{
	Vertex ver;
	cin >> ver.name;

	return ver;
}

// Slower way to find a concrete vertex in the graph
//Vertex* getVertex(Edge*& edges, size_t edgesCount, char* vertexName)
//{
//	if (!vertexName || !edges)
//	{
//		return nullptr;
//	}
//
//	for (size_t i = 0; i < edgesCount; i++)
//	{
//		if (strcmp(edges[i].start.name, vertexName) == 0)
//		{
//			return &(edges[i].start);
//		}
//		else if (strcmp(edges[i].end.name, vertexName) == 0)
//		{
//			return &(edges[i].end);
//		}
//	}
//
//	return nullptr;
//}

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

unsigned getVerticesCount(Edge& edges)
{
	// Counting unique vertices
	char uniqueVertices[MAX_VERTICES][STR_MAX_LEN + 1];
	unsigned uniqueVerticesCount = 0;

	for (size_t i = 0; i < edges; i++) {
		bool foundStart = false;
		bool foundEnd = false;

		// Check if the start vertex is unique
		for (unsigned j = 0; j < uniqueVerticesCount; j++) {
			if (strcmp(graph.edges[i].start.name, uniqueVertices[j]) == 0) {
				foundStart = true;
				break;
			}
		}

		// Add start vertex if it's unique
		if (!foundStart) {
			strcpy(uniqueVertices[uniqueVerticesCount], graph.edges[i].start.name);
			uniqueVerticesCount++;
		}

		// Check if the end vertex is unique
		for (unsigned j = 0; j < uniqueVerticesCount; j++) {
			if (strcmp(graph.edges[i].end.name, uniqueVertices[j]) == 0) {
				foundEnd = true;
				break;
			}
		}

		// Add end vertex if it's unique
		if (!foundEnd) {
			strcpy(uniqueVertices[uniqueVerticesCount], graph.edges[i].end.name);
			uniqueVerticesCount++;
		}
	}
}

// A function for initializing the graph
Graph initializeGraph(unsigned edgesCount)
{
	Edge* edges = initializeEdges(edgesCount);

	Graph graph;
	graph.edges = edges;
	graph.edgesCount = edgesCount;
	
	uniqueVerticesCount = getUniqueVerticesCount(edges, graph.edgesCount);

	graph.verticesCount = uniqueVerticesCount;

	return graph;
}

// Function for creating a deep copy of the struct edges
void deepCopyEdges(const Edge*& source, size_t edgesCount, Edge*& target) 
{
	for (size_t i = 0; i < edgesCount; i++)
	{
		target[i] = source[i];
	}
}

// Delete dinamically set edges
void freeEdges(Edge* edges)
{
	delete[] edges;
}

// Take edge as an argument
void addEdgeToGraph(Edge& edge, Graph& graph) 
{
	Edge* newEdges = new Edge[graph.edgesCount + 1];
	deepCopyEdges(graph.edges, graph.edgesCount, newEdges);

	freeEdges(graph.edges);
	graph.edges = newEdges;

	Edge additionalEdge;
	additionalEdge.start = edge.start;
	additionalEdge.end = edge.end;

	graph.edges[graph.edgesCount] = additionalEdge;
	graph.edgesCount++;
}

// A function for clearing the dinamically allocated memory of the graph
void freeGraphMemory(Graph& graph) 
{
	freeEdges(graph.edges);
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