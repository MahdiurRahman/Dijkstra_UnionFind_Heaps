#ifndef DIJKSTRA_
#define DIJKSTRA_

#include <iostream>
#include <vector>
#include "Graph.h"
#include "Heapify.h"
#include "Vertex.h"
using namespace std;

/*NOTES:
	This was BY FAR the most difficult coding project
	In nearly every function you'll see a "cout". These are for debug purposes
	Dijkstra makes use of: 
	Graph, to record the connections
	Heapify, (priority queue) to have the smallest distance readily available
	Vertex, to have datatypes which house information on index, weight, and path leading to it
*/

class Dijkstra
{
public:
	explicit Dijkstra() {};

	Dijkstra(string &file_name)
	{
		//cout << "Running Dijkstra(file_name)" << endl;

		graph_.initialize(file_name);
		initializePaths(graph_.size_ - 1);
	}

	void initializePaths(int size)
	{
		//cout << "Running initializePaths" << endl;

		Vertex<float> x; //dummy vertex to initialize stuff and add to vector
		x.setIndex(0);
		x.setWeight(2147483646.0); //instead of infinity, I use the numerical limit of signed int
		for (int i = 0; i <= size; i++)
		{
			paths_.push_back(x);
		}
		resetPaths();
	}

	//this is really a complement to initializePaths
		//it just makes each thing point to itself, and have itself as its index
	void resetPaths()
	{
		//cout << "Running resetPaths" << endl;

		for (int i = 0; i < paths_.size(); i++)
		{
			paths_[i].setIndex(i);
			paths_[i].setWeight(2147483646.0);
			paths_[i].setSource(&paths_[i]);
		}
	}

	//given an index, you look at all its outgoing connections, and add them to the queue
	void process(int index)
	{
		//cout << "Running process" << endl;

		Vertex<float> helper;
		helper.setSource(&paths_[index]);

		graph_.collector_ = graph_.adjacency_list[index];
		while (graph_.collector_ != nullptr)
		{
			helper.setIndex(graph_.collector_->vertex);
			helper.setWeight((graph_.collector_->weight) + paths_[index].getWeight());
			heap_.insert(helper);
			graph_.collector_ = graph_.collector_->next;
		}
	}

	//you take from top of the heap (smallest value), assess it with process function (above this)
	//you keep doing this recursively til heap is empty
	void runHeap()
	{
		//cout << "Running runHeap" << endl;

		if (!heap_.empty())
		{
			Vertex<float> helper = heap_.getFromHeap();
			//helper.setWeight(paths_[helper.getIndex()].getWeight());
			if (helper.getWeight() < paths_[helper.getIndex()].getWeight())
			{
				paths_[helper.getIndex()].setWeight(helper.getWeight());
				paths_[helper.getIndex()].setSource(helper.getSource());
				process(helper.getIndex());
			}
			runHeap();
		}
	}

	//given an index, what is the fastest route from that index to all the others
	//this essentially sets up the heap with a few entrys, then calls runHeap (above)
	void generatePaths(int start)
	{
		//cout << "Running generatePaths" << endl;

		resetPaths();

		//reset starting to 0
			paths_[start].setWeight(0.0);
		//helper: a dummy vertex which, like all start's outgoing connections, sources back to start
			Vertex<float> helper;
			helper.setSource(&paths_[start]); //helper

		//use Graph to set up initial connections
			graph_.collector_ = graph_.adjacency_list[start];
			while (graph_.collector_ != nullptr)
			{
				helper.setIndex(graph_.collector_->vertex);
				helper.setWeight(graph_.collector_->weight);
				heap_.insert(helper);
				graph_.collector_ = graph_.collector_->next;
			}
		//heap set up with some initial values, lets run it
			runHeap();
	}

	//prints contents of heap_ vector
	//looks at each entry in heap_ vector, and follows its source back to start-index
	//thus for each index you get a list of items which lead from start to that index
	void printPaths()
	{
		for (int i = 1; i < paths_.size(); i++)
		{
			cout << i << ": ";
			float weight = paths_[i].getWeight();

			vector<int> path_indexes; //important vector: this is where the index values get pushed to form a path
			if (paths_[i].getSource() == &paths_[i])
			{
				path_indexes.push_back(i);
			}
			else
			{
				Vertex<float>* ptr = &paths_[i];
				while (ptr->getIndex() != ptr->getSource()->getIndex())
				{
					path_indexes.push_back(ptr->getIndex());
					ptr = ptr->getSource();
				}
				path_indexes.push_back(ptr->getIndex());
			}
			for (int j = path_indexes.size() - 1; j > -1; j--)
			{
				cout << path_indexes[j] << ", ";
			}
			cout << "Cost: " << weight << endl;
		}
	}

//DEBUG FUNCTION
	void printWeights()
	{
		for (int i = 1; i < paths_.size(); i++)
		{
			cout << paths_[i].getIndex() << " " << paths_[i].getWeight() << " " << (*paths_[i].getSource()).getIndex() << endl;
		}
	}

private:
	Graph graph_;
	vector<Vertex<float>> paths_;
	Heap<Vertex<float>> heap_;
};


#endif // !DIJKSTRA_