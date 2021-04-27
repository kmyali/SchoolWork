#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h> //atof
using namespace std;

// Template class for weighted, directed graph
template<typename V, typename E>
class Graph
{
public:
	Graph() {}

	using VertexID = size_t;

	VertexID addVertex(V data) {
		Vertex v; // Create a Vertex
		v.data_ = std::move(data); // Move the data into it, to avoid deep copies if data takes large space
		VertexArray.push_back(std::move(v)); // Push the vertex to the end of the vector
		return VertexSize() - 1; //returns the position of the newly added vertex, starting from 0
	}
	Graph& addEdge(E relation) {
		adjMatrix.push_back(relation); // Adding the relation in the correct place in the adjacency matrix. 
	}

	int VertexSize() {
		return VertexArray.size();
	}

	void printVertices() {
		for (int i = 0; i < VertexSize(); i++) {
			std::cout << VertexArray[i].data_ << ", ";
		}
	}
private:
	struct Vertex {
		V data_;
	};

	struct Edge {
		VertexID from_;
		VertexID to_;
		E relation_;

	};

	vector<Edge> adjMatrix; //adjacency list
	vector<Vertex> VertexArray;

};

int main() {
	Graph<string, double> distances;

	ifstream read;
	read.open("road-distances.csv");
	string line;
	getline(read, line); //Read the first line
	int pos = 0, nextPos=0; 

	if (read.is_open()) {

		//Extracting the vertices from the first line
		while (line != "\n") {
			pos = line.find(',', pos);
			nextPos = line.find(',', pos + 1);
			if (nextPos != string::npos) {
				string name = line.substr(pos + 1, nextPos - pos - 1); //extract the name
				distances.addVertex(name);
				pos = nextPos;
			}
			else { //extract last name
				string name = line.substr(pos + 1, line.size() - pos - 1); 
				distances.addVertex(name);
				break;
			}
			
		}

		/*
		//Extracting the edges
		for (int i = 0; i < distances.VertexSize(); i++) {
			int pos = 0, nextPos;
			getline(read, line); //read the next line
			for (int j = 0; j < distances.VertexSize() - i; j++) {
				pos = line.find(',', pos); 
				nextPos = line.find(',', pos+1);
				string number = line.substr(pos + 1, nextPos - pos - 1); //Extract the distance as a string
				double value = atof(number.c_str()); // Convert it to double
				distances.addEdge(value); // push it to the Edges vector
				pos = nextPos; //update pos to search starting from the next comma
			}
		}
		*/
	} // closes if (read.is_open())
	read.close();

	distances.printVertices(); // For debugging purposes
} // main
