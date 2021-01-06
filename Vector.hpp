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
	class Vector{

	public:

		class const_iterator;
		class iterator;

		class base_iterator: public std::iterator<std::input_iterator_tag, T>
		{
		protected:
			T* p;

			base_iterator(): p(nullptr) {};
			base_iterator(base_iterator const &rhs) {
				this->p = rhs.p;
			}

			base_iterator(T *p) {
				this->p = p;
			}

			virtual base_iterator &operator=(const iterator &rhs){
				this->p = rhs.p;
				return *this;
			};

			base_iterator &operator=(const base_iterator &rhs){
				this->p = rhs.p;
				return *this;
			};

		};

		class iterator: public base_iterator {
		public:
			iterator(): base_iterator() {};
			iterator(T* p): base_iterator(p) {};
			iterator(iterator const &rhs): base_iterator(rhs) {}
			iterator& operator+=(const int i) {this->p += i;return *this;};
			iterator& operator-=(const int i) {this->p -= i;return *this;};
			iterator& operator++() {++this->p;return *this;};
			iterator operator++(int) {iterator tmp(*this); operator++(); return tmp;}
			iterator& operator--() {--this->p;return *this;};
			iterator operator--(int) {iterator tmp(*this); operator--(); return tmp;}
			bool operator==(const iterator& rhs) const {return (this->p)==rhs.p;}
			bool operator!=(const iterator& rhs) const {return (this->p)!=rhs.p;}
			T& operator*() {return *(this->p);}
			iterator & operator=(iterator const &rhs) {
				this->p = rhs.p;
				return *this;
			};
		};

		class const_iterator: public base_iterator {
		public:
			const_iterator(T* p): base_iterator(p) {};
			const_iterator(): base_iterator() {};
			const_iterator(base_iterator const &rhs): base_iterator(rhs) {}
			const_iterator& operator++() {++this->p;return *this;};
			const_iterator operator++(int) {const_iterator tmp(*this); operator++(); return tmp;}
			const_iterator& operator--() {--this->p;return *this;};
			const_iterator operator--(int) {const_iterator tmp(*this); operator--(); return tmp;}
			const_iterator& operator+=(const int i) {this->p += i;return *this;};
			const_iterator& operator-=(const int i) {this->p -= i;return *this;};
			bool operator==(const const_iterator& rhs) const {return (this->p)==rhs.p;}
			bool operator!=(const const_iterator& rhs) const {return (this->p)!=rhs.p;}
			T& operator*() {return *(this->p);}
			const_iterator &operator=(const_iterator const &rhs) {
				this->p = rhs.p;
				return *this;
			}
			const_iterator & operator=(iterator const &rhs) {
				base_iterator::operator=(rhs);
				return *this;
			};
		};

//		typedef T*                                      iterator;
//		typedef const T*                                const_iterator;
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
		value_type										*_memory;
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
			if (_memory != 0)
				_alloc.deallocate(_memory, _capacity);
		};

		Vector&						operator=(const Vector& rhs) {
			if (this != &rhs)
			{
				this->_alloc = rhs._alloc;
				this->reserve(rhs._size);
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

//		TODO: переделать resize на доп выделение памяти (выделяет больше ингода)
		void						resize(size_type n, value_type val = value_type()) {
			T*						new_array;
			size_type 				new_capacity;

			if (n > _capacity)
			{
				if (n > _capacity * 2)
					new_capacity = n;
				else if (n > _capacity)
					new_capacity = _capacity * 2;
				new_array = new_array = static_cast<T*>(_alloc.allocate(new_capacity));
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
			_size = n;
		};

		size_type					capacity() const {
			return _capacity;
		};

		void						reserve (size_type n) {
			T*	new_array;

			if (n <= _capacity)
				return ;
			new_array = static_cast<T*>(_alloc.allocate(n));
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
			reverse_iterator 		rit;

			resize(_size + 1);
			rit = rbegin();
			for (rit; rit != position; ++rit) {
				*rit = *(rit + 1);
			}
			*rit = val;
		};

		void						insert(iterator position, size_type n, const value_type& val) {
			iterator 		        src;
			iterator 		        dst;

			if (n == 0)
				return ;
			resize(_size + n);
			src = position;
			dst = position;
			dst += n; // todo:: not work
			for (;dst != end(); ++src, ++dst) // rewrite old values
				*dst = *src;
			for (;position != src; ++position) {
				*position = val;
			}
		};

		_INPUT_ITERATOR_TEMPLATE
		void						insert(iterator position, InputIterator first, InputIterator last) {
			iterator 		        src;
			iterator 		        dst;
			size_type 				distance;

			distance = std::distance(first, last);
			if (distance == 0)
				return ;
			resize(_size + distance);
			src = position;
			dst = position;
			dst += distance;
			for (;dst != end(); ++src, ++dst) // rewrite old values
				*dst = *src;
			for (; first != last ; ++first, ++position) {
				*position = *first;
			}
		};
		iterator					erase(iterator position) {
			for (position; position != end(); position++) {
				*position = *(position + 1);
			}
			--_size;
		};
		iterator					erase(iterator first, iterator last) {
			for (last; last != end() ; ++first, ++last) {
				*first = *last;
			}
			_size = std::distance(first, last);
		};
		void						swap(Vector& x) {
			value_type				tmp_memory = x._memory ;
			size_type				tmp_size = x._size ;
			size_type				tmp_capacity = x._capacity ;

			x._memory = this->_memory;
			x._size = this->_size;
			x._capacity	 = this->_capacity;
			this->_memory = tmp_memory;
			this->_size = tmp_size;
			this->_capacity	= tmp_capacity;
		};
		void						clear() {
			_size = 0;
		};

};
}

#endif //FT_CONTAINERS_VECTOR_HPP
