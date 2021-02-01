//
// Created by 32-ko on 01.02.2021.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

namespace ft
{
	template<class T, class Container = deque <T> >
	class Stack
	{

		typedef size_t          size_type;
		typedef Container       container_type;
		typedef T               value_type

		container_type          &_memory;

		explicit    Stack(Stack const &rhs) {};
		Stack       &operator=(Stack const &rhs) {};

	public:
		explicit Stack(const container_type &ctnr = container_type())
			:_memory(ctnr)
		{};

		virtual ~Stack() = default;

		bool    empty() const
		{
			return _memory.empty();
		}

		bool    size() const
		{
			return _memory.size();
		}

		value_type& top()
		{
			return _memory.back();
		};

		const value_type& top() const {
			return *(_memory.begin());
		};

		void push (const value_type& val) {
			_memory.push_back(val);
		};

		void pop() {
			_memory.pop_back();
		}

		const _Container& _Get_container() const
		{
			return (_memory);
		}

	}

	template <class T, class Container>
	bool operator== (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
		return lhs._Get_container() == rhs._Get_container();
	};

	template <class T, class Container>
	bool operator!= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
		return lhs._Get_container() != rhs._Get_container();
	};

	template <class T, class Container>
	bool operator<  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
		return lhs._Get_container() < rhs._Get_container();
	};

	template <class T, class Container>
	bool operator<= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
		return lhs._Get_container() <= rhs._Get_container();
	};

	template <class T, class Container>
	bool operator>  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
		return lhs._Get_container() > rhs._Get_container();
	};

	template <class T, class Container>
	bool operator>= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
		return lhs._Get_container() >= rhs._Get_container();
	};

};

#endif //FT_CONTAINERS_STACK_HPP
