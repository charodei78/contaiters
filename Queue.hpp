//
// Created by Holli Heimerdinger on 2/6/21.
//

#ifndef FT_CONTAINERS_QUEUE_HPP
#define FT_CONTAINERS_QUEUE_HPP

#import <deque>

namespace ft
{
	template<class T, class Container = std::deque <T> >
	class Queue
	{

		typedef size_t          size_type;
		typedef Container       container_type;
		typedef Container       _Container;
		typedef T               value_type;

		container_type          _memory;

		explicit    Queue(Queue const &rhs) {};
		Queue       &operator=(Queue const &rhs) {};

	public:
		explicit Queue(const container_type &ctnr = container_type())
				:_memory(ctnr){};

		virtual ~Queue() = default;

		bool    empty() const
		{
			return _memory.empty();
		}

		size_type   size() const
		{
			return _memory.size();
		}

		value_type& back()
		{
			return _memory.back();
		};

		value_type& front()
		{
			return _memory.front();
		};

		const value_type& top() const {
			return *(_memory.begin());
		};

		void push (const value_type& val) {
			_memory.push_back(val);
		};

		void pop() {
			_memory.pop_front();
		}

		const _Container& _Get_container() const
		{
			return (_memory);
		}

	};

	template <class T, class Container>
	bool operator== (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
		return lhs._Get_container() == rhs._Get_container();
	};

	template <class T, class Container>
	bool operator!= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
		return lhs._Get_container() != rhs._Get_container();
	};

	template <class T, class Container>
	bool operator<  (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
		return lhs._Get_container() < rhs._Get_container();
	};

	template <class T, class Container>
	bool operator<= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
		return lhs._Get_container() <= rhs._Get_container();
	};

	template <class T, class Container>
	bool operator>  (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
		return lhs._Get_container() > rhs._Get_container();
	};

	template <class T, class Container>
	bool operator>= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
		return lhs._Get_container() >= rhs._Get_container();
	};

};

#endif //FT_CONTAINERS_QUEUE_HPP
