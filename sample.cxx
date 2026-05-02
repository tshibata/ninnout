#include <queue>

#include "ninnout.h"

#include <iostream>

int main(int argc, char * * argv)
{
	send_messages(1);
	send_messages(2, 3);
	send_messages(4, 5, 6);

	while (! shared_queue<int>.empty())
	{
		std::cout << shared_queue<int>.front() << std::endl;
		shared_queue<int>.pop();
	}
	return 0;
}
