//
// Created by Holli Heimerdinger on 11/30/20.
//

#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include <memory>
#include <cstddef>



namespace ft
{
	template<
			typename T,
			typename Allocator = std::allocator<T>
	>

	class												List
	{

		typedef struct									s_list {
			T											data;
			struct list_t								*next;
		}												t_list;


		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef List<T>									iterator;
		typedef List<T>									const_iterator;
		typedef std::reverse_iterator<iterator>			reverse_iterator;
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::ptrdiff_t							difference_type;
		typedef std::size_t								size_type;

		List();
		~List();
		List&						operator=(const List& x);

//		Iterators
		iterator					begin();
		const_iterator 				begin() const;
		iterator					end();
		const_iterator 				end() const;
		reverse_iterator			rbegin();
		const_reverse_iterator		rbegin() const;
		reverse_iterator			rend();
		const_reverse_iterator		rend() const;

//		Capacity
		bool 						empty() const;
		size_type					size() const;
		size_type					max_size() const;

//		Element access

		reference					front();
		const_reference				front() const;
		reference					back();
		const_reference				back() const;

//		Modifiers

		template <class InputIterator>
		void						assign(InputIterator first, InputIterator last);
		void						assign(size_type n, const value_type& val);
		void						push_front(const value_type& val);
		void						push_front(value_type&& val);
		void						pop_front();
		void						push_back(const value_type& val);
		void						push_back(value_type&& val);
		void						pop_back();
		iterator 					insert(iterator position, const value_type& val);
		void						insert(iterator position, size_type n, const value_type& val);
		template <class InputIterator>
		void						insert(iterator position, InputIterator first, InputIterator last);
		iterator					erase(iterator position);
		iterator					erase(iterator first, iterator last);
		void						swap(List& x);
		void						resize(size_type n, value_type val = value_type());
		void						clear();

//		Operations

		void						splice(iterator position, List& x);
		void						splice(iterator position, List& x, iterator i);
		void						splice(iterator position, List& x, iterator first, iterator last);
		void						remove(const value_type& val);
		template <class Predicate>
		void						remove_if(Predicate pred);
		void						unique();
		template <class BinaryPredicate>
		void						unique(BinaryPredicate binary_pred);
		void						merge(List& x);
		template <class Compare>
		void						merge(List& x, Compare comp);
		void						sort();
		template <class Compare>
  		void						sort(Compare comp);
		void						reverse();
	};

}

	template <class T, class Alloc>
	bool							operator==(const ft::List<T,Alloc>& lhs, const ft::List<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool							operator!=(const ft::List<T,Alloc>& lhs, const ft::List<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool							operator< (const ft::List<T,Alloc>& lhs, const ft::List<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool							operator<=(const ft::List<T,Alloc>& lhs, const ft::List<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool							operator> (const ft::List<T,Alloc>& lhs, const ft::List<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool							operator>=(const ft::List<T,Alloc>& lhs, const ft::List<T,Alloc>& rhs);
	template <class T, class Alloc>
	void swap(ft::List<T,Alloc>& x, ft::List<T,Alloc>& y);

#endif //FT_CONTAINERS_LIST_HPP
