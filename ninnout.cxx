#include <setjmp.h>
#include <functional>
#include <queue>
#include <tuple>
#include <utility>

#include "ninnout.h"

jmp_buf ninnout_jmp_buf;

void send_messages()
{
}

bool check_messages()
{
	return true;
}

void finish_messages()
{
	longjmp(ninnout_jmp_buf, 1);
}
