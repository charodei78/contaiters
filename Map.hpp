//
// Created by Holli Heimerdinger on 2/6/21.
//

#ifndef FT_CONTAINERS_MAP_HPP
# define FT_CONTAINERS_MAP_HPP

# include <memory>
# include <cstddef>
# include <strhash.h>

# ifndef _ENABLE_INPUT_ITERATOR
#  define _ENABLE_INPUT_ITERATOR typename std::enable_if< std::__is_input_iterator<InputIterator>::value, InputIterator>::type
# endif

// TODO: Red-Black tree :)

namespace ft {

	template <typename Key, typename T>
	struct  pair {
		T       data;
		Key     key;
		pair    *left;
		pair    *prev;
		bool	is_red;
		pair    *right;
	};


	template < class Key,                                     // map::key_type
			class T,                                       // map::mapped_type
			class Compare = std::less<Key>,                     // map::key_compare
			class Alloc = std::allocator<pair<const Key,T> >    // map::allocator_type
	>
	class Map {

	public:
		class iterator;
		class const_iterator;

		typedef Key                                                 key_type;
		typedef T                                                   mapped_type;
		typedef pair<const key_type,mapped_type>                    value_type;
		typedef Compare                                             key_compare;
		typedef Alloc                                               allocator_type;
		typedef typename allocator_type::pointer                    pointer;
		typedef typename allocator_type::const_pointer              const_pointer;
		typedef typename allocator_type::reference                  reference;
		typedef typename allocator_type::const_reference            const_reference;
		typedef ptrdiff_t                                           difference_type;
		typedef typename std::reverse_iterator<iterator>            reverse_iterator;
		typedef std::reverse_iterator<const_iterator>               const_reverse_iterator;
		typedef size_t                                              size_type;

		allocator_type 		_alloc;
		size_type 			_size;
		pointer 			_begin;
		pointer 			_end;
		pointer 			_root;
		value_type			_tree;
		key_compare			_cmp;


	private:
		class base_iterator: public std::iterator<std::input_iterator_tag, T>
		{
		protected:
			value_type *_p;

			pointer getMore(pointer node) {
				if (node->right) {
					node = node->right;
					while (node->left)
						node = node->left;
					return node;
				} else {
					while (node->prev->right == node)
						node = node->prev;
					return node->prev;
				}
			};

			pointer getLess(pointer node) {
				if (node->left) {
					node = node->left;
					while (node->right)
						node = node->right;
					return node;
				} else {
					while (node->prev->left == node)
						node = node->prev;
					return node->prev;
				}
			}

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

		value_type			allocate_node(Key key, T value = T(), pointer parent = nullptr) {
			pointer			node;

			node = _alloc.allocate(1);

			node->key = key;
			node->data = value;
			node->left = nullptr;
			node->right = parent;

			return node;
		}

	public:

		class iterator: public base_iterator {
		public:
			iterator(): base_iterator() {};
			iterator(value_type *p): base_iterator(p) {};
			iterator(iterator const &rhs): base_iterator(rhs) {}
			~iterator(){};
			value_type       *base() const { return this->_p; }
			reference        operator* () const { return this->_p->data; }
			pointer          operator->() const { return pointer(this->_p->data); };
			iterator&         operator++() { this->_p = getMore(this->_p); return *this; };
			iterator         operator++(int) { iterator tmp(*this); operator++(); return tmp; }
			iterator&        operator--() { this->_p = getLess(this->_p); return *this; };
			iterator         operator--(int) { iterator tmp(*this); operator--(); return tmp; }
			bool             operator==(iterator const&rhs) const { return this->_p == rhs._p; }
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
			value_type              *base() const { return this->_p; }
			reference               operator* () const { return this->_p->data; }
			pointer                 operator->() const { return pointer(this->_p->data); };
			const_iterator&         operator++() { this->_p = getMore(this->_p); return *this; };
			const_iterator          operator++(int) { const_iterator tmp(*this); operator++(); return tmp; }
			const_iterator&         operator--() { this->_p = getLess(this->_p); return *this; };
			const_iterator          operator--(int) { const_iterator tmp(*this); operator--(); return tmp; }
			bool                    operator==(const_iterator const&rhs) const { return this->_p == rhs._p; }
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




		explicit Map (const key_compare& comp = key_compare(),
		              const allocator_type& alloc = allocator_type())
		              : _tree(nullptr), _alloc(alloc), _cmp(comp) {};

		template < class InputIterator >
		Map (InputIterator first, _ENABLE_INPUT_ITERATOR last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				: _tree(nullptr), _alloc(alloc), _cmp(comp)
			{ insert(first, last); };


		Map (const Map& rhs) {
			insert(rhs.begin(), rhs.end());
		};

		~Map() {
			clear();
		};

		Map &operator=(Map const &rhs) {
			clear();
			insert(rhs.begin(), rhs.end());
		}


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
			return size_type(-1) / sizeof(value_type);
		};

//		Element access

		mapped_type& operator[] (const key_type& key) {
			pointer 		node = _root;

			while (node) {
				if (_cmp(node->key, key)) {
					if (node->right)
						node = node->right;
					else
						return (node->right = allocate_node(key, T(), node));
				}
				else if (node->key == key)
					break ;
				else {
					if (node->left)
						node = node->left;
					else
						return (node->left = allocate_node(key, T(), node));
				}
			}
			if (!node) {
				node = allocate_node(key);
				_root = _begin = _end = node;
			}
			return node;
		};

	};
}


#endif //FT_CONTAINERS_MAP_HPP
