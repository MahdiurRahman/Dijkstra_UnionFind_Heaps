#ifndef HEAPIFY_
#define HEAPIFY_

/*NOTE:
	Every function here is public, because they are nessecary to use this data structure
	Also note that I don't move deleted roots to the end of the data. I simply delete it.
	There are differences b/w this heap and traditional heaps because this one is particular
	to Dijkstras shortest path.
*/

#include <vector>
#include <iostream>
using namespace std;

template <typename data>
class Heap
{
public:

	Heap() {};

	Heap(data x)
	{
		insert(x);
	}

	void insert(data x)
	{
		heap_.push_back(x);
		int index = heap_.size() - 1;
		while (heap_[index] < heap_[(index - 1) / 2])
		{
			heap_[index] = heap_[(index - 1) / 2];
			heap_[(index - 1) / 2] = x;
			index = (index - 1) / 2;
		}
	}

	void propogateDown(int index)
	{
		if ((index * 2 + 1) < heap_.size())
		{
			if ((index * 2 + 2) < heap_.size())
			{
					int replacement_index;
					if (heap_[index * 2 + 1] < heap_[index * 2 + 2])
					{
						replacement_index = index * 2 + 1;
					}
					else
					{
						replacement_index = index * 2 + 2;
					}
					if (heap_[replacement_index] < heap_[index])
					{
						data replacement_data = heap_[replacement_index];
						heap_[replacement_index] = heap_[index];
						heap_[index] = replacement_data;
						propogateDown(replacement_index);
					}
			}
			else
			{
				if (heap_[index * 2 + 1] < heap_[index])
				{
					data replacement = heap_[index];
					heap_[index] = heap_[index * 2 + 1];
					heap_[index * 2 + 1] = replacement;
				}
			}
		}
	}

	data getFromHeap()
	{
		data dummy;
		helper = dummy;
		if (heap_.size() > 0)
		{
			helper = heap_[0];
			heap_[0] = heap_[heap_.size() - 1];
			heap_.pop_back();
			if (heap_.size() > 1)
			{
				propogateDown(0);
			}
		}
		return helper;
	}

	void printHeap()
	{
		int square = 0;
		int iterator1 = 1;
		int iterator2 = iterator1;
		while (iterator1 < heap_.size())
		{
			for (int i = (iterator2 - 1); i < iterator1; i++)
			{
				cout << heap_[i] << " ";
			}
			cout << endl;
			square++;
			iterator2 = iterator1;
			iterator1 += (square * square);
		}
		for (int i = (iterator2 - 1); i < heap_.size(); i++)
		{
			cout << heap_[i] << " ";
		}
	}

	bool empty()
	{
		if (heap_.empty())
		{
			return true;
		}
		return false;
	}

private:
	data helper;
	vector<data> heap_;
};


#endif