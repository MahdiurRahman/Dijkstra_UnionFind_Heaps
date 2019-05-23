#include <iostream>
#include <cstdlib>
#include "Graph.h"
#include "Heapify.h"
#include "Dijkstra.h"
#include "Union.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, const char * argv[])
{
	if (argc != 3)
	{
		cout << "Usage: " << argv[0] << " <filename>" << " <starting vertex #>" << std::endl;
		return 1;
	}

	string data = argv[1];
	char start_char = *argv[2];
	int start = start_char - '0';

	Dijkstra b(data);
	b.generatePaths(start);
	b.printPaths();

	return 0;
}