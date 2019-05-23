#ifndef _UNION_
#define _UNION_

/*
	This is a unionfind data structure, but is a smart one, as it only uses a simply vector
	elements in the vector act as nodes and each node's index is its address
	Each node holds the numerical value of another index, thus acting like a fake pointer
*/


#include <vector>
#include <iostream>
using namespace std;

class Union
{
public:
	Union() : size_{ 0 }, total_edges_{ 0 }, largest_outdegree_{ 0 }, smallest_outdegree_{ 2147483646 }, average_outdegree_ { 0.0 }, union_find_{ false }
	{
		messageToProfStamos();
	};

	Union(int size) : size_{ size }, total_edges_{ 0 }, largest_outdegree_{ 0 }, smallest_outdegree_{ 2147483646 }, average_outdegree_{ 0.0 }, union_find_{ false }
	{
		messageToProfStamos();
		initialize();
	}

	void setSize(int size)
	{
		//cout << "running setSize" << endl;
		size_ = size;
		initialize();
	}

	int find(int a)
	{
		//cout << "running find" << endl;

		int explorer = a;
		while (array_[explorer] > 0)
		{
			explorer = array_[explorer];
		}
		return explorer;
	}

	bool union_(int a, int b)
	{
		//cout << "running union_" << endl;

		if ((outOfBounds(a) or outOfBounds(b)) or (a == b))
		{
			return false;
		}

		int set_a = find(a);
		int set_b = find(b);


		if (set_a == -1 and set_b == -1)
		{
			if (a < b)
			{
				array_[a] += -1;
				array_[b] = a;
			}
			else
			{
				array_[b] += -1;
				array_[a] = b;
			}
			return true;
		}

		if (set_a == set_b)
		{
			return false;
		}

		if (array_[set_a] < array_[set_b])
		{
			array_[set_a] += array_[set_b];
			array_[set_b] = set_a;
			if (array_[set_a] <= (size_ * -1))
			{
				union_find_ = true;
			}
			return true;
		}
		else
		{
			array_[set_b] += array_[set_a];
			array_[set_a] = set_b;
			if (array_[set_b] <= (size_ * -1))
			{
				union_find_ = true;
			}
			return true;
		}
	}

	bool unionFind()
	{
		//cout << "running unionFind" << endl;

		return union_find_;
	}

	void generateStats()
	{
		//cout << "running generateStats" << endl;

		for (int i = 0; i < array_.size(); i++)
		{
			stats_.push_back(0);
		}

		computeTotalEdges();
		computeOutdegrees();
	}

	int totalEdges()
	{
		return total_edges_;
	}

	int smallestOutdegree()
	{
		return smallest_outdegree_;
	}

	int largestOutdegree()
	{
		return largest_outdegree_;
	}

	float averageOutdegree()
	{
		return average_outdegree_;
	}

//DEBUG functions
	void printArray()
	{
		for (int i = 0; i < array_.size(); i++)
		{
			cout << "[" << i << " : " << array_[i] << "] ";
		}
	}

	void printStats()
	{
		for (int i = 0; i < stats_.size(); i++)
		{
			cout << "[" << i << " : " << stats_[i] << "] ";
		}
	}
	
private:
	int size_ = 0;
	bool union_find_ = false;
	vector<int> array_;
	vector<int> stats_;

	int total_edges_ = 0;
	int smallest_outdegree_ = 2147483646;
	int largest_outdegree_ = 0;
	float average_outdegree_ = 0.0;

	void messageToProfStamos()
	{
		cout << "!!!NOTE TO PROFESSOR STAMOS AND STAFF!!\n";
		cout << "In this implementation, it is assumed that:\n";
		cout << "in a set with only 1 member, that member has\n";
		cout << "exactly 1 outgoing edge going to nullpointer (-1).\n";
		cout << "Thus, every node always has atleast 1\n";
		cout << "outgoing edge. Thank you.\n";
	}

	void initialize()
	{
		//cout << "running initialize" << endl;

		union_find_ = false;
		for (int i = 0; i <= size_; i++)
		{
			array_.push_back(-1);
		}
	}

	bool outOfBounds(int x)
	{
		//cout << "running outOfBounds" << endl;

		if ((x < 1) or (x > size_))
		{
			return true;
		}
		return false;
	}

	void computeTotalEdges()
	{
		//cout << "running computeTotalEdges" << endl;

		total_edges_ = 0;
		for (int i = 1; i < array_.size(); i++)
		{
			if (array_[i] < 0)
			{
				total_edges_++;
			}
			else
			{
				total_edges_ += 2;
			}
		}
	}

	void computeOutdegrees()
	{
		//cout << "running computeOutdegrees" << endl;

		for (int i = 1; i < array_.size(); i++)
		{
			if (array_[i] < 0)
			{
				stats_[i]++;
			}
			else
			{
				stats_[i]++;
				stats_[array_[i]]++;
			}
		}

		//reset
		smallest_outdegree_ = 2147483646;
		largest_outdegree_ = 0;
		average_outdegree_ = 0.0;

		for (int i = 1; i < stats_.size(); i++)
		{
			if (stats_[i] < smallest_outdegree_)
			{
				smallest_outdegree_ = stats_[i];
			}
			if (stats_[i] > largest_outdegree_)
			{
				largest_outdegree_ = stats_[i];
			}
			average_outdegree_ += (stats_[i] / 1.0);
		}
		average_outdegree_ /= (size_ / 1.0);
	}
};


#endif // !_UNION_
