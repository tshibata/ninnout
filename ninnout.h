
extern jmp_buf ninnout_jmp_buf;

template<typename T>
inline std::queue<T> shared_queue;

template<typename T>
inline unsigned int shared_queue_count;

template <class T>
void send(T msg)
{
	shared_queue<T>.push(msg);
	shared_queue_count<T>++;
}

void send_messages();

template <class Head, class... Tail>
void send_messages(Head&& head, Tail&&... tail)
{
	send(head);
	send_messages(std::forward<Tail>(tail)...);
}

bool check_messages();

template <class Head, class... Tail>
bool check_messages(Head&& head, Tail&&... tail)
{
	if (shared_queue_count<Head> == 0)
	{
		return false;
	}
	shared_queue_count<Head>--;
	bool result = check_messages(std::forward<Tail>(tail)...);
	shared_queue_count<Head>++;
	return result;
}

template <class... Ts>
bool check_all_messages(Ts&... msgs)
{
	return check_messages(std::forward<Ts>(msgs)...);
}

template<class T> void set_message(T & msg)
{
	msg = shared_queue<T>.front();
	shared_queue<T>.pop();
	shared_queue_count<T>--;
}

template<class... Ts>
void set_all_messages(std::tuple<Ts...>& tpl)
{
	std::apply([](Ts&... elems)
	{
		((void) set_message<Ts>(elems), ... );
	}, tpl);
}

template<typename... Ts> void handle_messages(Ts...);

template<typename... Ts>
bool receive_messages()
{
	std::tuple<Ts...> tpl;

	if (std::apply(check_all_messages<Ts...>, tpl))
	{
		set_all_messages(tpl);
		switch (setjmp(ninnout_jmp_buf)) {
		case 0:
			std::apply(handle_messages<Ts...>, tpl);
			break;
		default:
			break;
		}
		return true;
	}
	return false;
}

void finish_messages();
