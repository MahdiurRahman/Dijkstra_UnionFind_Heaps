#ifndef VERT_
#define VERT_

/*NOTES:
	This is a simple data type which I use in Dijkstra.
	Given a vertex, itt allows me to house:
	What index or "node number" used to identify the vertex
	What is the current weight on this vertex if shortest path is taken from start
	What is the previous vertex which leads to this one via shortest path
*/

#include <iostream>
using namespace std;

template <typename data>
class Vertex
{
public:
	Vertex() : index_{ 0 } {}
	Vertex(int index, data weight) : index_{ index }, weight_{ weight } {};
	Vertex(int index, data weight, Vertex* source) : index_{ index }, weight_{ weight }, source_{ source } {};

	int getIndex() { return index_; };
	data getWeight() { return weight_; };
	Vertex* getSource() { return source_; };

	void setIndex(int index) { index_ = index; };
	void setWeight(data weight) { weight_ = weight; };
	void setSource(Vertex* source) { source_ = source; };

	bool friend operator< (Vertex &lhs, Vertex &rhs)
	{
		if (lhs.getWeight() < rhs.getWeight())
		{
			return true;
		}
		return false;
	}

private:
	int index_ = 0;
	data weight_ = NULL;
	Vertex* source_ = nullptr;
};


#endif // !VERTEX_
