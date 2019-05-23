#include <iostream>
#include <cstdlib>
#include "Graph.h"
#include "Heapify.h"
#include "Dijkstra.h"
#include "Union.h"
#include <cstdlib>
#include <ctime>
using namespace std;

void unionFindAlgorithm(int N)
{
	Union union_set(N);

	srand(time(0));
	int a{ 0 }, b{ 0 };
	while (!union_set.unionFind()) 
	{
		a = rand() % N + 1;
		b = rand() % N + 1; 
		union_set.union_(a, b);
	}

	union_set.generateStats(); cout << endl;

	cout << "a) total edges: " << union_set.totalEdges() << endl;
	cout << "b) smallest out-degree: " << union_set.smallestOutdegree() << endl;
	cout << "c) largest out-degree: " << union_set.largestOutdegree() << endl;
	cout << "d) average out-degree: " << union_set.averageOutdegree() << endl;
}

int main(int argc, const char * argv[])
{
	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " <filename>" << " <starting vertex #>" << std::endl;
		return 1;
	}

	char N = *argv[1];
	int N_ = int(N);

	unionFindAlgorithm(N_);

	return 0;
}