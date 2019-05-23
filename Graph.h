#ifndef GRAPH_
#define GRAPH_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Graph
{
public:
	friend class Dijkstra; //allows Dijkstra to access

	//default constructor
	Graph() : size_{ 0 } {};

	//constructor
	Graph(string &file_name)
	{
		initialize(file_name);
	};

	//destructor
	~Graph()
	{
		for (int i = 0; i < size_; i++)
		{
			delete adjacency_list[i];
		}
		delete adjacency_list;
	};

	void printGraph()
	{
		for (int i = 1; i < size_; i++)
		{
			cout << i << ": ";
			adjacency_node *helper = adjacency_list[i];
			while (helper != nullptr)
			{
				cout << helper->vertex << " " << helper->weight << " ";
				helper = helper->next;
			}
			cout << endl;
		}
	}

	//takes in file of pairs of numbers (i.e. "4 5"), checks if connected 
	void dataSearch(string &filename)
	{
		int A{ 0 }, B{ 0 };

		ifstream input_data(filename);
		string line;
		while (getline(input_data, line)) //reading line by line
		{
			stringstream linestream(line);
			while (linestream >> A >> B)
			{
				float val = connected(A, B);
				if (val == 0.0)
				{
					cout << A << " " << B << ": Not connected\n";
				}
				else
				{
					cout << A << " " << B << ": Connected, weight of edge is " << val << endl;
				}
			}
		}
	}

	int size() { return size_; };

private:
	struct adjacency_node
	{
		int vertex = 0;
		float weight = 0.0;
		adjacency_node * next = nullptr;
	};

	int size_ = 0;
	adjacency_node *collector_ = nullptr;
	adjacency_node **adjacency_list;

	//established array of pointers, each pointing to a linked chain which is an adjusted list
	void setupAdjacencyList(int size)
	{
		adjacency_list = new adjacency_node*[size];
		for (int i = 0; i < size; i++)
		{
			adjacency_list[i] = nullptr;
		}
	}

	//takes a file, reads line by line, allots info from file to variables as needed
	void initialize(string &file_name)
	{
		//initialize
		int index = 0;
		int vertex = 0;
		float weight;

		//read size (first line in file)
		ifstream input_data(file_name);
		input_data >> size_;
		size_++;
		setupAdjacencyList(size_);

		//read line by line
		string line;
		while (getline(input_data, line))
		{
			stringstream linestream(line);
			linestream >> index; //first item in line
			while (linestream >> vertex >> weight) //every pair therafter
			{
				addEdge(index, vertex, weight);
			}
		}
	}

	//index: which vertex(index) in array will host connection
	//vertex: which vertex connection will lead to
	//weight: weight of connection
	void addEdge(int index, int vertex, float weight)
	{
		adjacency_node *helper = adjacency_list[index];
		if (helper == nullptr)
		{
			adjacency_list[index] = new adjacency_node;
			adjacency_list[index]->vertex = vertex;
			adjacency_list[index]->weight = weight;
			adjacency_list[index]->next = nullptr;
		}
		else
		{
			while (helper->next != nullptr)
			{
				helper = helper->next;
			}
			helper->next = new adjacency_node;
			helper->next->vertex = vertex;
			helper->next->weight = weight;
			helper->next->next = nullptr;
		}
	}

	//checks if vertex A has an edge (connection) leading to B
	//unconventional: 0.0 means false, anything else is true
	float connected(int A, int B)
	{
		adjacency_node *helper = adjacency_list[A]; //pointer to adjacency list of vertex A

		if (helper == nullptr) //incase adjacency list is empty (i.e. A is connected to nothing)
		{
			return 0.0;
		}
		else //otherwise, if A DOES have connections
		{
			//keep moving helper to the next vertex til B is found or end is reached 
			while (true)
			{
				if (helper->vertex == B) //if B found
				{
					return helper->weight;
				}
				else if (helper->next != nullptr) //move onto next one
				{
					helper = helper->next;
				}
				else
				{
					return 0.0;
				}
			}
		}
	}

	//pointer to particular index's adjacency list
	adjacency_node* returnAdjacencyList(int index)
	{
		return adjacency_list[index];
	}

	//pointer to the whole array
	adjacency_node** returnAdjacencyPtr() { return adjacency_list; };
};


#endif // !GRAPH
