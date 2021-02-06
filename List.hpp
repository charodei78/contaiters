//
// Created by Holli Heimerdinger on 11/30/20.
//

#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include <memory>
#include <cstddef>
#include <stdlib.h>
#include <type_traits>
#include <stdexcept>

# ifndef _ENABLE_INPUT_ITERATOR
#  define _ENABLE_INPUT_ITERATOR typename std::enable_if< std::__is_input_iterator<InputIterator>::value, InputIterator>::type
# endif

namespace ft
{
	template <typename T>
	struct									        s_list {
		T											data;
		struct s_list								*next;
		struct s_list								*prev;
	};

	template<
			typename T,
			typename Allocator = std::allocator<struct s_list<T>>
	>

	class												List
	{


	public:
		class const_iterator;
		class iterator;

		typedef struct s_list<T>                        t_list;
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef T&			                            reference;
		typedef T const &		                        const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef std::reverse_iterator<iterator>			reverse_iterator;
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::ptrdiff_t							difference_type;
		typedef std::size_t								size_type;

	private:
		t_list  										*_begin = nullptr;
		t_list  										*_end = nullptr;
		size_type										_size;
		allocator_type									_alloc;

		t_list              *_allocate_node(value_type val = 0) {
			t_list          *node = _alloc.allocate(sizeof(t_list));
			node->next = node;
			node->prev = node;
			node->data = val;
			return node;
		};

		void                _deallocateNode(t_list *node) {
			_alloc.deallocate(node, 1);
		};

		template<typename Y>
		size_type           max(Y a, Y b) {
			return a > b ? a : b;
		};

		template<typename Y>
		size_type           min(Y a, Y b) {
			return a > b ? a : b;
		};

		void                link(t_list *left, t_list *right) {
			left->next = right;
			right->prev = left;
		};

		void                nodeSwap(t_list *left, t_list *right) {
			t_list          *tmp;

			tmp = right->next;
			link(left->prev, right);
			link(left, tmp);
			link(right, left);
		};

	public:
		explicit List (const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _begin(_allocate_node()), _end(_begin), _size(0){};

		explicit List (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _begin(_allocate_node()), _end(_begin), _size(0) {
			resize(n, val);
		};

		template < class InputIterator >
		List (InputIterator first, _ENABLE_INPUT_ITERATOR last, const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _begin(_allocate_node()), _end(_begin), _size(0) {
			size_type 	distance;

			distance = std::distance(first, last);
			while (distance > 0) {
				push_back(*first);
				distance--;
			}
			_size = distance;
		};
		List (const List& x): _alloc(x._alloc), _begin(_allocate_node()), _end(_begin), _size(0) {
			*this = x;
		};
		~List() {
			clear();
			_deallocateNode(_end);
		};
		List&						operator=(const List& rhs) {
			const_iterator                first = rhs.begin();
			const_iterator                last = rhs.end();

			if (this != &rhs) {
				clear();
				this->_alloc = rhs._alloc;
				while (first != last)
					push_back(*(first++));
			}
			return *this;
		}


	private:
		class base_iterator: public std::iterator<std::input_iterator_tag, T>
		{
		protected:
			t_list *_p;

			base_iterator(): _p(nullptr) {};
			base_iterator(base_iterator const &rhs): _p(nullptr) {
				this->_p = rhs._p;
			}

			base_iterator(pointer p) {
				this->_p = p;
			}

			virtual base_iterator &operator=(const iterator &rhs){
				this->_p = rhs._p;
				return *this;
			};

			virtual base_iterator &operator=(const base_iterator &rhs){
				this->_p = rhs._p;
				return *this;
			};
		};
	public:

		class iterator: public base_iterator {
		public:
			iterator(): base_iterator() {};
			iterator(t_list *p): base_iterator(p) {};
			iterator(iterator const &rhs): base_iterator(rhs) {}
			~iterator(){};
			t_list           *base() const { return this->_p; }
			reference        operator* () const { return this->_p->data; }
			pointer          operator->() const { return pointer(this->_p->data); };
			iterator&        operator++() { this->_p = this->_p->next;return *this; };
			iterator         operator++(int) { iterator tmp(*this); operator++(); return tmp; }
			iterator&        operator--() {this->_p = this->_p->prev;return *this; };
			iterator         operator--(int) { iterator tmp(*this); operator--(); return tmp; }
			bool             operator==(iterator const&rhs) const { return this->base() == rhs.base(); }
			bool             operator!=(iterator const&rhs) const { return !(*this == rhs); }
			iterator         &operator=(iterator const &rhs) {
				this->_p = rhs._p;
				return *this;
			};
		};

		class const_iterator: public base_iterator {
		public:
			const_iterator(pointer p): base_iterator(p) {};
			const_iterator(): base_iterator() {};
			const_iterator(base_iterator const &rhs): base_iterator(rhs) {};
			~const_iterator(){};
			t_list                  *base() const { return this->_p; }
			reference               operator* () const { return this->_p->data; }
			pointer                 operator->() const { return pointer(this->_p->data); };
			const_iterator&         operator++() { this->_p = this->_p->next;return *this; };
			const_iterator          operator++(int) { const_iterator tmp(*this); operator++(); return tmp; }
			const_iterator&         operator--() {this->_p = this->_p->prev;return *this; };
			const_iterator          operator--(int) { const_iterator tmp(*this); operator--(); return tmp; }
			bool                    operator==(const_iterator const&rhs) const { return this->base() == rhs.base(); }
			bool                    operator!=(const_iterator const&rhs) const { return !(*this == rhs); }
			const_iterator          &operator=(const_iterator const &rhs) {
				this->_p = rhs._p;
				return *this;
			}
			const_iterator & operator=(iterator const &rhs) {
				base_iterator::operator=(rhs);
				return *this;
			};
		};

//		Iterators
		iterator					begin() {
			return iterator(_begin);
		};
		const_iterator 				begin() const {
			return const_iterator(_begin);
		};
		iterator					end() {
			return iterator(_end);
		}
		const_iterator 				end() const {
			return const_iterator(_end);
		};
		reverse_iterator			rbegin() {
			return reverse_iterator(_end);
		};
		const_reverse_iterator		rbegin() const {
			return const_reverse_iterator(_end);
		};
		reverse_iterator			rend() {
			return reverse_iterator(_begin);
		};
		const_reverse_iterator		rend() const {
			return const_reverse_iterator(_begin);
		};

//		Capacity
		bool 						empty() const {
			return _size == 0;
		};
		size_type					size() const {
			return _size;
		};
		size_type					max_size() const {
			return size_type(-1) / sizeof(t_list);
		};

//		Element access

		reference					front() {
			return _begin->data;
		};
		const_reference				front() const {
			return _begin->data;
		};
		reference					back() {
			return _end->prev->data;
		};
		const_reference				back() const {
			return _end->prev->data;
		};

//		Modifiers

		template < class InputIterator >
		void						assign(InputIterator first, _ENABLE_INPUT_ITERATOR last) {
			clear();
			while (first != last) {
				push_back(*first);
				first++;
			}
		};
		void						assign(size_type n, const value_type& val) {
			clear();
			while (n-- > 0)
				push_back(val);
		};
		void						push_front(const value_type& val) {
			t_list                  *res = _allocate_node(val);

			res->next = _begin;
			res->begin = _end;
			_begin = res;
			++_size;
		};
		void						pop_front() {
			erase(begin());
		};
		void						push_back(const value_type& val) {
			t_list                  *res = _allocate_node(val);

			res->next->prev = _end->prev;
			_end->prev->next = res;
			res->next = _end;
			_end->prev = res;
			_begin = _end->next;
			++_size;
		};
		void						pop_back() {
			erase(--end());
		};
		iterator 					insert(iterator position, const value_type& val) {
			t_list                  *positionBase = position.base();
			t_list                  *res = _allocate_node(val);

			res->next = positionBase;
			positionBase->prev->next = res;
			res->prev = positionBase->prev;
			positionBase->prev = res;
			++_size;
			_begin = _end->next;
			return res;
		};
		void						insert(iterator position, size_type n, const value_type& val) {
			t_list                  *positionBase = position.base();
			t_list                  *begin;
			t_list                  *end;

			if (n) {
				begin = _allocate_node(val);
				end = begin;
				++_size;
				while (--n) {
					++_size;
					end->next = _allocate_node(val);
					end->next->prev = end;
					end = end->next;
				}
				end->next = positionBase;
				link(positionBase->prev, begin);
				positionBase->prev = end;
				_begin = _end->next;
			}
		};
		template < class InputIterator >
		void						insert(iterator position, InputIterator first, _ENABLE_INPUT_ITERATOR last) {
			t_list                  *positionBase = position.base();
			t_list                  *begin;
			t_list                  *end;

			if (std::distance(first, last)) {
				begin = _allocate_node(*(first++));
				end = begin;
				++_size;
				while (first != last) {
					++_size;
					end->next = _allocate_node(*(first++));
					end->next->prev = end;
					end = end->next;
				}
				end->next = positionBase;
				positionBase->prev->next = begin;
				begin->prev = positionBase->prev;
				positionBase->prev = end;
				_begin = _end->next;
			}
		};
		iterator					erase(iterator position) {
			t_list                  *positionBase = position.base();
			t_list                  *tmp;

			tmp = positionBase->next;
			positionBase->prev->next = tmp;
			tmp->prev = positionBase->prev;
			_deallocateNode(positionBase);
			--_size;
			_begin = _end->next;
			return tmp;
		};
		iterator					erase(iterator first, iterator last) {
			t_list                  *firstBase = first.base();
			t_list                  *lastBase = last.base();
			t_list                  *ret;

			firstBase->prev->next = lastBase;
			lastBase->prev = firstBase->prev;
			while (firstBase != lastBase) {
				ret = firstBase->next;
				_deallocateNode(firstBase);
				firstBase = ret;
				--_size;
			}
			_begin = _end->next;
			return  ret;
		};
		void						swap(List& rhs) {
			t_list                  *beginTmp = _begin;
			t_list                  *endTmp = _end;
			size_type               sizeTmp = _size;
			allocator_type          allocTmp = _alloc;

			_begin  = rhs._begin;
			_end    = rhs._end;
			_size   = rhs._size;
			_alloc  = rhs._alloc;
			rhs._begin = beginTmp;
			rhs._end = endTmp;
			rhs._size = sizeTmp;
			rhs._alloc = allocTmp;
		};
		void						resize(size_type n, value_type val = value_type()) {
			t_list                  new_list;

			if (n > _size)
				insert(end(), n - _size, val);
			else
				while (n < _size)
					erase(--end());
		};
		void						clear() {
			while (_size)
				erase(begin());
		};

//		Operations

		void						splice(iterator position, List& rhs) {
			t_list                  *positionBase;

			positionBase = position.base();
			positionBase->prev->next = rhs._begin;
			rhs._begin->prev = positionBase->prev;
			positionBase->prev = rhs._end->prev;
			rhs._end->prev->next = positionBase;
			rhs._begin = rhs._end;
			rhs._end->next = rhs._end;
			rhs._end->prev = rhs._end;
			_size += rhs._size;
			rhs._size = 0;
			_begin = _end->next;
		};

		void						splice(iterator position, List& x, iterator i) {
			t_list                  *rightPositionBase = i.base();
			t_list                  *leftPositionBase = position.base();

			link(rightPositionBase->prev, rightPositionBase->next);

			link(leftPositionBase->prev, rightPositionBase);
			link(rightPositionBase, leftPositionBase);
			++_size;
			--x._size;
			_begin = _end->next;
			x._begin = x._end->next;
		};

		void						splice(iterator position, List& x, iterator first, iterator last) {
			t_list                  *thisPositionBase = position.base();
			t_list                  *beginPositionBase = first.base();
			t_list                  *endPositionBase = last.base()->prev;
			size_type               distance;

			if (first == last)
				return;

			distance = std::distance(first, last);

			link(beginPositionBase->prev, endPositionBase->next);

			link(thisPositionBase->prev, beginPositionBase);
			link(endPositionBase, thisPositionBase);

			_size += distance;
			x._size -= distance;
			_begin = _end->next;
			x._begin = x._end->next;
		};

		void						remove(const value_type& val) {
			iterator                beginIt = begin();
			iterator                endIt = end();
			iterator                tmp;

			while (beginIt != endIt) {
				if (*beginIt == val) {
					tmp = beginIt++;
					erase(tmp);
				}
				beginIt++;
			}
		};

		template <class Predicate>
		void						remove_if(Predicate pred) {
			iterator                beginIt = begin();
			iterator                endIt = end();
			iterator                tmp;

			while (beginIt != endIt) {
				if (pred(*beginIt)) {
					tmp = beginIt++;
					erase(tmp);
				} else
					beginIt++;
			}
		};

		void						unique() {
			unique(std::equal_to<T>());
		};

		template <class BinaryPredicate>
		void						unique(BinaryPredicate binary_pred) {
			iterator                beginIt = begin();
			iterator                currentIt = ++begin();
			iterator                endIt = end();
			iterator                tmp;

			while (currentIt != endIt) {
				if (binary_pred(*beginIt, *currentIt)) {
					erase(currentIt++);
				} else {
					++beginIt;
					++currentIt;
				}
			}
		};
		void						merge(List& x) {
			merge(x, std::less<T>());
		};
		template <class Compare>
		void						merge(List& x, Compare comp) {
			t_list                  *firstBegin = _begin;
			t_list                  *firstEnd = _end;
			t_list                  *secondBegin = x._begin;
			t_list                  *secondEnd = x._end;
			t_list                  *last = _end;
			size_type               summarySize;

			summarySize = _size + x._size;

			for (size_type i = 0; i < summarySize; i++) {
				if (firstBegin != firstEnd && comp(firstBegin->data, secondBegin->data)) {
					link(last, firstBegin);
					firstBegin = firstBegin->next;
				} else if (secondBegin != secondEnd) {
					link(last, secondBegin);
					secondBegin = secondBegin->next;
				}
				last = last->next;
			}
			last->next = _end;
			_begin = _end->next;
			x._begin = x._end;
			link(x._begin, x._end);
			x._size = 0;
			_size = summarySize;

		};

		void						sort() {
			sort(std::greater<T>());
		};
		template <class Compare>
		void						sort(Compare comp) {
			t_list                  *first;

			for (size_type i = _size - 1; i > 0; --i) {
				first = _end->next;
				for (size_type j = 0; j < i; j++) {
					if (comp(first->data, first->next->data))
						nodeSwap(first, first->next);
					else
						first = first->next;
				}
			}
			_begin = _end->next;
		};
		void						reverse() {
			t_list                  *cur;
			t_list                  *prev;
			t_list                  *next;

			cur = _end->prev;
			prev = _end;
			while (next != _end) {
				next = cur->prev;
				link(prev, cur);
				prev = cur;
				cur = next;
			}
			link(prev, cur);
			_begin = _end->next;
		};
	};

}

	template <class T, class Alloc>
	bool							             operator==(const ft::List<T,Alloc>& lhs, const ft::List<T,Alloc>& rhs) {
		typename ft::List<T,Alloc>::const_iterator     leftBegin = lhs.begin();
		typename ft::List<T,Alloc>::const_iterator     leftEnd = lhs.end();
		typename ft::List<T,Alloc>::const_iterator     rightBegin = rhs.begin();
		typename ft::List<T,Alloc>::const_iterator     rightEnd = rhs.end();

		while (leftBegin != leftEnd && rightBegin != rightEnd) {
			if (*leftBegin != *rightBegin)
				return false;
			++leftBegin;
			++rightBegin;
		}
		if (leftBegin != leftEnd || rightBegin != rightEnd)
			return false;
		return true;
	};
	template <class T, class Alloc>
	bool							operator!=(const ft::List<T,Alloc>& lhs, const ft::List<T,Alloc>& rhs) {
		return (!(lhs == rhs));
	};
	template <class T, class Alloc>
	bool							operator< (const ft::List<T,Alloc>& lhs, const ft::List<T,Alloc>& rhs) {
		typename ft::List<T,Alloc>::const_iterator     leftBegin = lhs.begin();
		typename ft::List<T,Alloc>::const_iterator     leftEnd = lhs.end();
		typename ft::List<T,Alloc>::const_iterator     rightBegin = rhs.begin();
		typename ft::List<T,Alloc>::const_iterator     rightEnd = rhs.end();

		while (leftBegin != leftEnd && rightBegin != rightEnd) {
			if (*leftBegin < *rightEnd)
				return true;
			++leftBegin;
			++rightBegin;
		}
		if (rightBegin != rightEnd)
			return true;
		return false;
	};
	template <class T, class Alloc>
	bool							operator<=(const ft::List<T,Alloc>& lhs, const ft::List<T,Alloc>& rhs) {
		typename ft::List<T,Alloc>::const_iterator     leftBegin = lhs.begin();
		typename ft::List<T,Alloc>::const_iterator     leftEnd = lhs.end();
		typename ft::List<T,Alloc>::const_iterator     rightBegin = rhs.begin();
		typename ft::List<T,Alloc>::const_iterator     rightEnd = rhs.end();

		while (leftBegin != leftEnd && rightBegin != rightEnd) {
			if (*leftBegin <= *rightEnd)
				return true;
			++leftBegin;
			++rightBegin;
		}
		if (leftBegin != leftEnd)
			return false;
		return true;
	};
	template <class T, class Alloc>
	bool							operator> (const ft::List<T,Alloc>& lhs, const ft::List<T,Alloc>& rhs) {
		return (!(lhs <= rhs));
	};
	template <class T, class Alloc>
	bool							operator>=(const ft::List<T,Alloc>& lhs, const ft::List<T,Alloc>& rhs) {
		return (!(lhs < rhs));
	};
	template <class T, class Alloc>
	void swap(ft::List<T,Alloc>& x, ft::List<T,Alloc>& y) {
		x.swap(y);
	};

#endif //FT_CONTAINERS_LIST_HPP
