//
// Created by Holli Heimerdinger on 12/1/20.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <memory>
#include <type_traits>
#include <stdexcept>

#define _INPUT_ITERATOR_TEMPLATE \
	template < \
		class InputIterator,\
		typename = typename std::enable_if< std::__is_input_iterator<InputIterator>::value>::type \
	>

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class Vector {

	public:

		class const_iterator;
		class iterator;

		typedef std::reverse_iterator<iterator>			reverse_iterator;
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef std::ptrdiff_t							difference_type;
		typedef std::size_t								size_type;

	private:
		class base_iterator: public std::iterator<std::input_iterator_tag, T>
		{
		protected:
			pointer _p;

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


//		template<class _Iter>
//		class _iterable {
//		public:
//			typedef _Iter                                                              iterator_type;
//			typedef typename std::iterator_traits<iterator_type>::iterator_category    iterator_category;
//			typedef typename std::iterator_traits<iterator_type>::value_type           value_type;
//			typedef typename std::iterator_traits<iterator_type>::difference_type      difference_type;
//			typedef typename std::iterator_traits<iterator_type>::pointer              pointer;
//			typedef typename std::iterator_traits<iterator_type>::reference            reference;
//		private:
//			iterator_type _p;
//		public:
//			_iterable(): _p(nullptr) {};
//			_iterable(iterator_type p): _p(p) {};
//			template<class _Up>
//			_iterable(_iterable<_Up> &rhs,
//				typename std::enable_if<std::is_convertible<_Up, iterator_type>::value>::type* = 0)
//					: _p(rhs) {}
//			reference       operator*() const { return *(this->p); }
//			pointer         operator->() const { return pointer(this->p); };
//			_iterable&      operator++() { ++this->p;return *this; };
//			_iterable       operator++(int) { _iterable tmp(*this); operator++(); return tmp; }
//			_iterable&      operator--() { --this->p;return *this; };
//			_iterable       operator--(int) { _iterable tmp(*this); operator--(); return tmp; }
//			_iterable       operator+ (difference_type n) const { _iterable res(this); res += n; return res; }
//			_iterable&      operator+=(const int i) { this->p += i;return *this; };
//			_iterable       operator- (difference_type n) const { return *this + (-n); }
//			_iterable&      operator-=(const int i) { this->p -= i;return *this; };
//			reference       operator[](difference_type i) { return this->p[i]; }
//			iterator_type   base() const { return _p; }
//			bool            operator==(const _iterable& rhs) const {return (this->base()) == rhs.base(); }
//			bool            operator!=(const _iterable& rhs) const { return !(*this == rhs); }
//			bool            operator< (const _iterable& rhs) const { return (this->base()) < rhs.base(); }
//			bool            operator>=(const _iterable& rhs) const { return !(*this < rhs); }
//			bool            operator> (const _iterable& rhs) const { return (this->base()) > rhs.base(); }
//			bool            operator<=(const _iterable& rhs) const { return !(*this > rhs); }
//			_iterable       operator- (const _iterable& rhs) const { return _iterable(this->base() - rhs.base()); }
//			_iterable&      operator=(_iterable const &rhs) {
//				this->p = rhs.base();
//				return *this;
//			};
//		};

	public:

		class iterator: public base_iterator {
		public:
			iterator(): base_iterator() {};
			~iterator(){};
			iterator(pointer p): base_iterator(p) {};
			iterator(iterator const &rhs): base_iterator(rhs) {}
			reference        operator* () const { return *(this->_p); }
			pointer          operator->() const { return pointer(this->_p); };
			iterator&        operator++() { ++(this->_p);return *this; };
			iterator         operator++(int) { iterator tmp(*this); operator++(); return tmp; }
			iterator&        operator--() { --(this->_p);return *this; };
			iterator         operator--(int) { iterator tmp(*this); operator--(); return tmp; }
			iterator         operator+ (difference_type n) const { iterator res(*this); res += n; return res; }
			iterator&        operator+=(const int i) { this->_p += i;return *this; };
			iterator         operator- (difference_type n) const { return *this + (-n); }
			iterator&        operator-=(const int i) { this->_p -= i;return *this; };
			reference        operator[](difference_type i) { return this->_p[i]; }
			pointer          base() const { return this->_p; }
			bool             operator==(const iterator& rhs) const {return (this->base()) == rhs.base(); }
			bool             operator!=(const iterator& rhs) const { return !(*this == rhs); }
			bool             operator< (const iterator& rhs) const { return (this->base()) < rhs.base(); }
			bool             operator>=(const iterator& rhs) const { return !(*this < rhs); }
			bool             operator> (const iterator& rhs) const { return (this->base()) > rhs.base(); }
			bool             operator<=(const iterator& rhs) const { return !(*this > rhs); }
			iterator    operator- (const base_iterator& rhs) const { return base_iterator(this->base() - rhs.base()); }
			iterator &  operator=(iterator const &rhs) {
				this->_p = rhs._p;
				return *this;
			};
		};

		class const_iterator: public base_iterator {
		public:
			const_iterator(pointer p): base_iterator(p) {};
			const_iterator(): base_iterator() {};
			~const_iterator(){};
			const_iterator(base_iterator const &rhs): base_iterator(rhs) {};
			reference        operator*() const { return *(this->_p); }
			pointer          operator->() const { return pointer(this->_p); };
			const_iterator&   operator++() { ++this->_p;return *this; };
			const_iterator    operator++(int) { const_iterator tmp(*this); operator++(); return tmp; }
			const_iterator&   operator--() { --this->_p;return *this; };
			const_iterator    operator--(int) { const_iterator tmp(*this); operator--(); return tmp; }
			const_iterator    operator+ (difference_type n) const { const_iterator res(*this); res += n; return res; }
			const_iterator&   operator+=(const int i) { this->_p += i;return *this; };
			const_iterator    operator- (difference_type n) const { return *this + (-n); }
			const_iterator&   operator-=(const int i) { this->_p -= i;return *this; };
			reference        operator[](difference_type i) { return this->_p[i]; }
			pointer          base() const { return this->_p; }
			bool             operator==(const const_iterator& rhs) const {return (this->base()) == rhs.base(); }
			bool             operator!=(const const_iterator& rhs) const { return !(*this == rhs); }
			bool             operator< (const const_iterator& rhs) const { return (this->base()) < rhs.base(); }
			bool             operator>=(const const_iterator& rhs) const { return !(*this < rhs); }
			bool             operator> (const const_iterator& rhs) const { return (this->base()) > rhs.base(); }
			bool             operator<=(const const_iterator& rhs) const { return !(*this > rhs); }
			const_iterator    operator- (const const_iterator& rhs) const { return base_iterator(this->base() - rhs.base()); }
			const_iterator &operator=(const_iterator const &rhs) {
				this->_p = rhs._p;
				return *this;
			}
			const_iterator & operator=(iterator const &rhs) {
				base_iterator::operator=(rhs);
				return *this;
			};
		};

	private:
		value_type										*_memory = nullptr;
		size_type										_size;
		size_type										_capacity;
		allocator_type									_alloc;

	public:
		explicit Vector (const allocator_type& alloc = allocator_type())
				: _memory(nullptr), _size(0), _capacity(0), _alloc(alloc) {};

		explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				:_memory(nullptr), _size(0), _capacity(0), _alloc(alloc) {
			resize(n, val);
		};

		_INPUT_ITERATOR_TEMPLATE
		Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
				: _memory(nullptr), _size(0), _capacity(0), _alloc(alloc) {
			iterator 	it;
			size_type 	distance;

			distance = std::distance(first, last);
			reserve(distance);
			it = begin();
			for (; first != last ; it++, first++) {
				*it = *first;
			}
			_size = distance;
		};

		Vector (const Vector& x) : _memory(nullptr), _size(0), _capacity(0) {
			*this = x;
		};

		~Vector() {
			if (this->_memory != 0 && _capacity != 0)
				_alloc.deallocate(this->_memory, _capacity);
		};

		Vector&						operator=(const Vector& rhs) {
			if (this != &rhs)
			{
				this->reserve(rhs._size);
				this->_alloc = rhs._alloc;
				this->_size = rhs._size;
				for (int i = 0; i < rhs._size; ++i) {
					this->_memory[i] = rhs[i];
				}
			}
			return *this;
		};


//		Iterators
		iterator					begin() {
			return iterator(_memory);
		};

		const_iterator 				begin() const
		{
			return const_iterator(_memory);
		};

		iterator					end() {
			return iterator(_memory + _size);
		};

		const_iterator 				end() const {
			return const_iterator(_memory + _size);
		};

		reverse_iterator			rbegin() {
			return reverse_iterator(end());
		}

		const_reverse_iterator		rbegin() const {
			return reverse_iterator(end());
		};

		reverse_iterator			rend() {
			return reverse_iterator(begin());
		};

		const_reverse_iterator		rend() const  {
			return reverse_iterator(begin());
		};

//		Capacity

		bool 						empty() const {
			return !_size;
		};

		size_type					size() const {
			return _size;
		};

		size_type					max_size() const {
			return size_type(-1) / sizeof(value_type);
		};

		void						resize(size_type n, value_type val = value_type()) {
			pointer 				new_array;
			size_type 				new_capacity;

			if (n > _capacity)
			{
				if (n > _capacity * 2)
					new_capacity = n;
				else
					new_capacity = _capacity * 2;
				new_array = new_array = static_cast<pointer>(_alloc.allocate(new_capacity));
				for (size_type i = 0; i < _size && i < n; ++i) {
					new_array[i] = _memory[i];
				}
				if (_memory)
					_alloc.deallocate(_memory, _capacity);
				_capacity = new_capacity;
				_memory = new_array;
			}
			if (n > _size) {
				for (size_type i = 0; i < n - _size; ++i) {
					_memory[i + _size] = val;
				}
			}
			this->_size = n;
		};

		size_type					capacity() const {
			return _capacity;
		};

		void						reserve (size_type n) {
			pointer             	new_array;

			if (n <= _capacity)
				return ;
			new_array = static_cast<pointer>(_alloc.allocate(n));
			for (size_type i = 0; i < _size; ++i) {
				new_array[i] = _memory[i];
			}
			if (_memory)
				_alloc.deallocate(_memory, _capacity);
			_memory = new_array;
			_capacity = n;
		};

//		Element access

		reference					operator[](size_type n) {
			return _memory[n];
		};

		const_reference				operator[](size_type n) const {
			return _memory[n];
		};

		reference					at(size_type n) {
			if (n >= _size)
				throw std::out_of_range("Vector");
			return _memory[n];
		};

		const_reference				at(size_type n) const {
			return at(n);
		};

		reference					front() {
			return _memory[0];
		};

		const_reference				front() const {
			return front();
		};

		reference					back() {
			return _memory[_size - 1];
		};

		const_reference				back() const {
			return back();
		};

//		Modifiers

		_INPUT_ITERATOR_TEMPLATE
		void						assign(InputIterator first, InputIterator last) {
			size_type				distance = std::distance(first, last);
			iterator 				it;

			resize(distance);
			it = begin();
			for (; first != last; ++first, ++it) {
				*it = *first;
			}
			_size = distance;
		};

		void						assign(size_type n, const value_type& val) {
			resize(n);
			for (size_type i = 0; i < n; ++i) {
				at(i) = val;
			}
			_size = n;
		};

		void						push_back(const value_type& val) {
			resize(_size + 1, val);
		};

		void						pop_back() {
			_size--;
		};

		iterator 					insert(iterator position, const value_type& val) {
			value_type              tmp;
			size_type               num_position;

			num_position = std::distance(begin(), position);
			resize(_size + 1);
			position = begin() + num_position;
			tmp = *position;
			*position = val;
			position++;
			for (; position != this->end(); ++position) {
				std::swap(tmp, *position);
			}
			return begin() + num_position;
		};

		void						insert(iterator position, size_type n, const value_type& val) {
			reverse_iterator        src;
			reverse_iterator        dst;
			bool                    is_empty = false;
			size_type               num_position;

			if (n == 0)
				return ;
			if (_size == 0)
				is_empty = true;
			else
				num_position = std::distance(begin(), position);
			resize(_size + n);
			if (is_empty)
				position = begin();
			else {
				position = begin() + num_position;
				src = rbegin() + n;
				dst = rbegin();
				for (;src != rend() - num_position; ++src, ++dst) // rewrite old values
					*dst = *src;
			}
			for (; n > 0; ++position, --n) {
				*position = val;
			}
		};

		_INPUT_ITERATOR_TEMPLATE
		void						insert(iterator position, InputIterator first, InputIterator last) {
			reverse_iterator        src;
			reverse_iterator        dst;
			size_type 				distance;
			bool                    is_empty = false;
			size_type               num_position;

			if (distance == 0)
				return ;
			if (_size == 0)
				is_empty = true;
			else
				num_position = std::distance(begin(), position);
			distance = std::distance(first, last);
			resize(_size + distance);
			if (is_empty) {
				position = begin();
			}
			else {
				position = begin() + num_position;
				src = rbegin() + distance;
				dst = rbegin();
				for (;src != rend() - num_position; ++src, ++dst) // rewrite old values
					*dst = *src;
			}
			for (;first != last; ++position, ++first) {
				*position = (*first);
			}
		};

		iterator					erase(iterator position) {
			iterator                tmp;

			if (position.base() == nullptr)
				return end();
			tmp = position;
			for (; tmp != end() - 1; tmp++) {
				*tmp = *(tmp + 1);
			}
			--_size;
			return position;
		};

		iterator					erase(iterator first, iterator last) {
			iterator                begin(first);

			if (first.base() == nullptr)
				return end();
			for (; last != end() - 1; ++first, ++last) {
				*first = *last;
			}
			_size -= std::distance(first, last);
			return begin;
		};

		void						swap(Vector& x) {
			value_type				*memoryTmp = x._memory ;
			size_type				sizeTmp = x._size ;
			size_type				capacityTmp = x._capacity ;
			allocator_type          allocatorTmp = x._alloc;

			x._memory       = this->_memory;
			x._size         = this->_size;
			x._capacity	    = this->_capacity;
			x._alloc        = this->_alloc;
			this->_alloc    = allocatorTmp;
			this->_memory   = memoryTmp;
			this->_size     = sizeTmp;
			this->_capacity	= capacityTmp;
		};
		void						clear() {
			_size = 0;
		};

};
}

#endif //FT_CONTAINERS_VECTOR_HPP
