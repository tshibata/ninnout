/*
 * Merge sort by using a message queue.
 */
#include <functional>
#include <queue>
#include <tuple>
#include <utility>

#include "ninnout.h"

#include <iostream>
#include <random>

struct Section
{
	int size;
	int * array;
	Section(int i)
	{
		size = i;
		array = new int[i];
	}
	~Section()
	{
		delete array;
	}
};

template<> void handle_messages(Section * s1, Section * s2)
{
	Section * s3 = new Section(s1->size + s2->size);
	int i1 = 0;
	int i2 = 0;
	for (int i3 = 0; i3 < s3->size; i3++)
	{
		if (s1->size <= i1)
		{
			s3->array[i3] = s2->array[i2++];
		}
		else if (s2->size <= i2)
		{
			s3->array[i3] = s1->array[i1++];
		}
		else if (s1->array[i1] <= s2->array[i2])
		{
			s3->array[i3] = s1->array[i1++];
		}
		else
		{
			s3->array[i3] = s2->array[i2++];
		}
	}
	delete(s1);
	delete(s2);
	send_messages(s3);
}

template<> void handle_messages(Section * s)
{
	std::cout << "sorted:";
	for (int i = 0; i < s->size; i++)
	{
		std::cout << " " << s->array[i];
	}
	std::cout << std::endl;
	delete(s);
}

int main(int argc, char * * argv)
{
	std::random_device seed;
	std::mt19937 engine(seed());
	std::uniform_int_distribution dist;

	std::cout << "random:";
	for (int i = 1; i < 10; i++)
	{
		Section * s = new Section(1);
		s->array[0] = 10 + dist(engine) % 90;
		std::cout << " " << s->array[0];
		send_messages(s);
	}
	std::cout << std::endl;

	while (receive_messages<Section *, Section *>()
		|| receive_messages<Section *>());
	return 0;
}
