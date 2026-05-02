
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
