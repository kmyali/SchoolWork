#include <iostream>


template<typename V, typename E>
class Graph
{
public:
	Graph(int size): size_(size)  {}

	using VertexID = size_t;

	VertexID addVertex(V data){
		pos++; //Increment the position to correctly add the new vertex to the array
		Vertex v; // Create a Vertex
		v.data_ = std::move(data); // Move the data into it
		VertexArray[pos] = std::move(v); // Add the vertex in the next available position in the array
		return pos;
	}
	Graph& addEdge(VertexID posFrom, VertexID posTo, E relation) {
		adjMatrix[size * posTo + posFrom] = relation; // Adding the relation in the correct place in the adjacency matrix. 
		return *this;
	}

private:
	struct Vertex {
		V data_;
	};

	struct Edge {
		VertexID from_;
		VertexID to_;
		E relation_;

	}

	int size_; 
	Vertex VertexArray[size];
	int pos = -1; // Indicates where the vertex will be added in the VertexArray

	Edge adjMatrix[size * size];

};

