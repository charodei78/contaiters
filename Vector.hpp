//
// Created by Holli Heimerdinger on 12/1/20.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <memory>
#include <stdexcept>

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class													Vector{


public:

		template<typename U>
		class Iter {
		protected:
			Iter(U* p): p(p) {};
			~Iter() {};
			Iter & operator=(Iter const &rhs) {
				this->p = rhs.p;
				return *this;
			};
			U* p;
			U* getP() const
			{
				return this->p;
			}
		};

		template<typename U>
		class base_iterator: public Iter<U>
		{
		public:
			base_iterator(U* p): Iter<U>(p) {};
			base_iterator(): Iter<U>(NULL) {};
			base_iterator& operator++() {++this->p;return *this;}
			base_iterator<U> (base_iterator<U> const &rhs): Iter<U>(rhs.getP()) {}
			base_iterator operator++(int) {base_iterator tmp(*this); operator++(); return tmp;}
			bool operator==(const base_iterator& rhs) const {return (this->p)==rhs.p;}
			bool operator!=(const base_iterator& rhs) const {return p(this->p)!=rhs.p;}
			U& operator*() {return *(this->p);}
			base_iterator<const T> & operator=(base_iterator<T> const &rhs) {
				this->p = rhs.getP();
			};
		};

		typedef base_iterator<T>                        iterator;
		typedef base_iterator<const T>                  const_iterator;
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

		value_type										*_memory;
		size_type										_size;
		size_type										_capacity;
		allocator_type									_alloc;

		explicit Vector (const allocator_type& alloc = allocator_type())
				: _memory(), _size(), _capacity(), _alloc(alloc) {};
		explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				:_memory(0), _size(), _capacity(), _alloc(alloc) {
			resize(n, val);
		};
		template <class InputIterator>
		Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
				: _capacity(), _alloc(alloc) {
			iterator 	it;
			size_type 	distance;

			distance = std::distance(first, last);
			reserve(distance);
			it = begin();
			for (first; first != last ; it++, first++) {
				*it = *first;
			}
			_size = distance;
		};
		Vector (const Vector& x) : _size(), _capacity() {
			assign(x.begin(), x.end());
		};
		~Vector() {
			if (_memory != 0)
				_alloc.deallocate(_memory, _capacity);
		};

		Vector&						operator=(const Vector& x);


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
			for (size_type i = 0; i < n - _size; ++i) {
				_memory[i + _size] = val;
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
			operator[](n);
		};

		reference					at(size_type n) {
			if (n >= _size)
				throw std::out_of_range("Vector");
			return operator[](n);
		};

		const_reference				at(size_type n) const {
			return at(n);
		};

		reference					front() {
			return at(0);
		};

		const_reference				front() const {
			return front();
		};

		reference					back() {
			return at(_size - 1);
		};

		const_reference				back() const {
			return back();
		};

//		Modifiers

		template <class InputIterator>
		void						assign(InputIterator first, InputIterator last) {
			size_type				distance = std::distance(first, last);
			iterator 				it;

			resize(distance);
			for (first; first != last; ++first, ++it) {
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
			reverse_iterator 		rit_src;
			reverse_iterator 		rit_dst;

			if (n == 0)
				return ;
			resize(_size + n);
			rit_src = rbegin() + n;
			rit_dst = rbegin();
			for (rit_src; rit_src != position; ++rit_src, ++rit_dst) {
				*rit_dst = *(rit_src + 1);
			}
			for (rit_dst; rit_dst != position ; ++rit_dst) {
				*rit_dst = val;
			}
		};

		template <class InputIterator>
		void						insert(iterator position, InputIterator first, InputIterator last) {
			reverse_iterator 		rit_src;
			reverse_iterator 		rit_dst;
			size_type 				distance;

			distance = std::distance(first, last);
			if (distance == 0)
				return ;
			resize(_size + distance);
			rit_src = rbegin() - distance;
			rit_dst = rbegin();
			for (rit_src; rit_src != position; ++rit_src, ++rit_dst) {
				*rit_dst = *(rit_src + 1);
			}
			for (first; first != last ; ++first, ++rit_dst) {
				*rit_dst = *first;
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
