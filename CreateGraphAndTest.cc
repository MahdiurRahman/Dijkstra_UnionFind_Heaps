#include <iostream>
#include <cstdlib>
#include "Graph.h"
using namespace std;

int main(int argc, const char * argv[])
{
	if (argc != 3)
	{
		cout << "Usage: " << argv[0] << " <filename>" << " <starting vertex #>" << std::endl;
		return 1;
	}
	string data = argv[1];
	string search_file = argv[2];

	Graph a(data);
	a.dataSearch(search_file);
	return 0;
}