#include <functional>
#include <queue>
#include <tuple>
#include <utility>

#include "ninnout.h"

#include <iostream>

template<> void handle_messages(int msg)
{
	std::cout << msg << std::endl;
}

int main(int argc, char * * argv)
{
	send_messages(1);
	send_messages(2, 3);
	send_messages(4, 5, 6);

	while (receive_messages<int>());
	return 0;
}
