#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

//NOTE: This is not my code, taken from user Captain Obvlious on stack overflow
//Author: Captain Oblivious
//Source: https://stackoverflow.com/questions/16749723/how-i-can-find-value-in-priority-queue


#include <queue>
template<
	class T,
	class Container = std::vector<T>,
	class Compare = std::less<typename Container::value_type>
> class MyQueue : public std::priority_queue<T, Container, Compare>
{
public:
	typedef typename
		std::priority_queue<
		T,
		Container,
		Compare>::container_type::const_iterator const_iterator;

	const_iterator find(const T&val) const
	{
		auto first = this->c.cbegin();
		auto last = this->c.cend();
		while (first != last) {
			if (*first == val) return first;
			++first;
		}
		return last;
	}

	const_iterator  end() const
	{
		auto last = this->c.cend();
		return last;
	}
};

#endif // !PRIORITY_QUEUE_H