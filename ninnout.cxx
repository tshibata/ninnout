#include <setjmp.h>
#include <functional>
#include <mutex>
#include <queue>
#include <tuple>
#include <utility>

#include "ninnout.h"

thread_local jmp_buf ninnout_jmp_buf;

std::mutex ninnout_mutex;

void finish_messages()
{
	longjmp(ninnout_jmp_buf, 1);
}
