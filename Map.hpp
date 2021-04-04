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

template<typename T, typename Key>
struct node
{
	node 				*left;
	node 				*right;
	node 				*parent;
	Key 				key;
	T	 				value;
	bool 				is_red;

	bool isLeft()
	{
		return parent && parent->left == this;
	}

	bool isRight()
	{
		return !isLeft();
	}

	node *grandparent()
	{
		if (parent)
			return parent->parent;
		return nullptr;
	}

	node *uncle()
	{
		node *g = grandparent();
		if (!g)
			return nullptr;
		if (parent->isLeft())
			return g->right;
		return g->left;
	}

	node *sibling()
	{
		if (parent)
			return isLeft() ? parent->right : parent->left;
		return nullptr;
	}


};

namespace ft {

	template < class Key,                                     			// map::key_type
			class T,                                       				// map::mapped_type
			class Compare = std::less<Key>,                     		// map::key_compare
			class Alloc = std::allocator<std::pair<const Key,T> >   	 // map::allocator_type
	>
	class Map {

	public:
		class iterator;
		class const_iterator;
		class value_compare;

		typedef Key                                                 key_type;
		typedef T                                                   mapped_type;
		typedef std::pair<const key_type, mapped_type>        		value_type;
		typedef Compare                                             key_compare;
		typedef value_compare                                       value_comp;
		typedef Alloc                                               allocator_type;
		typedef typename allocator_type::pointer                    pointer;
		typedef typename allocator_type::const_pointer              const_pointer;
		typedef typename allocator_type::reference                  reference;
		typedef typename allocator_type::const_reference            const_reference;
		typedef ptrdiff_t                                           difference_type;
		typedef std::reverse_iterator<iterator>						reverse_iterator;
		typedef std::reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef size_t                                              size_type;

	private:
		typedef node<T, Key>										node_base;
		typedef typename allocator_type::template rebind<node_base>::other 	_node_alloc;
		typedef node_base*                  				 		 node_pointer;


		allocator_type 					_alloc;
		size_type 						_size;
		node_pointer  					_begin;
		key_type 						max_key;
		node_pointer  					_end;
		key_type 						min_key;
		node_pointer  					_root;
		key_compare						_cmp;

		// TODO: проверить коплина

		class base_iterator: public std::iterator<std::input_iterator_tag, T>
		{
		protected:
			node_pointer _p;
			value_type 	pair;

		public:
			static node_pointer getMore(node_pointer node) {
//				if (!node)
//					return node;
				if (node->right) {
					node = node->right;
					while (node->left)
						node = node->left;
					return node;
				} else if (node->isLeft()) {
					return node->parent;
				} else {
					while (node->parent && node->isRight())
						node = node->parent;
					return node->parent;
				}
			};

			static node_pointer getLess(node_pointer node) {
//				if (!node)
//					return node;
				if (node->left) {
					node = node->left;
					while (node->right)
						node = node->right;
					return node;
				} else if (node->isRight()){
					return node->parent;
				} else {
					while (node->parent && node->isLeft())
						node = node->parent;
					return node->parent;
				}
			}

			static node_pointer     getBase(base_iterator n) {
				return n._p;
			}

			base_iterator(base_iterator const &rhs): _p(nullptr){
				this->_p = rhs._p;
			}

			virtual ~base_iterator(){}

		protected:
			base_iterator(): _p(nullptr) {};


			base_iterator(node_pointer p) {
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

		node_pointer			allocate_node(Key key, T value = T(), node_pointer parent = nullptr) {
			node_pointer 			node;

			node = _node_alloc(_alloc).allocate(1);

			++_size;
			node->key = key;
			node->value = value;
			node->left = nullptr;
			node->right = nullptr;
			node->is_red = true;
			node->parent = parent;

			return node;
		}

		void                _deallocateNode(node_pointer node) {
			_node_alloc(_alloc).deallocate(node, 1);
			--_size;
		};

	public:

		class iterator: public base_iterator {
		public:
			iterator(node_pointer p): base_iterator(p) {};
			iterator(): base_iterator() {};
			iterator(iterator const &rhs): base_iterator(rhs) {}
			~iterator(){};
			std::pair<const Key, T&>	_get_value() const { return std::pair<const Key, T&>(this->_p->key, this->_p->value); }
			value_type 		 operator* () const { return value_type(this->_p->key, this->_p->value); }
			iterator&        operator++() {
				node_pointer tmp = this->_p;
				this->_p = this->getMore(this->_p);
				if (!this->_p)
					return *this;
				return *this; };
			iterator         operator++(int) {
				iterator tmp(*this);
				operator++();
				return tmp;
			}
			iterator&        operator--() { this->_p = this->getLess(this->_p); return *this; };
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
			const_iterator(node_pointer p): base_iterator(p) {};
			const_iterator(): base_iterator() {};
			const_iterator(base_iterator const &rhs): base_iterator(rhs) {};
			~const_iterator(){};
			std::pair<const Key, T&>	_get_value() const { return std::pair<const Key, T&>(this->_p->key, this->_p->value); }
			value_type		  		operator* () const { return value_type(this->_p->key, this->_p->value); }
			const_iterator&         operator++() { this->_p = this->getMore(this->_p); return *this; };
			const_iterator          operator++(int) { const_iterator tmp(*this); operator++(); return tmp; }
			const_iterator&         operator--() { this->_p = this->getLess(this->_p); return *this; };
			const_iterator          operator--(int) { const_iterator tmp(*this); operator--(); return tmp; }
			bool                    operator==(const_iterator const&rhs) const { return this->_p == rhs._p; }
			bool                    operator!=(const_iterator const&rhs) const { return !(*this == rhs); }
			const_iterator          &operator=(const_iterator const &rhs) {
				this->_p = rhs._p;
				return *this;
			}
			const_iterator 			&operator=(iterator const &rhs) {
				base_iterator::operator=(rhs);
				return *this;
			};
		};

		explicit Map (const key_compare& comp = key_compare(),
		              const allocator_type& alloc = allocator_type())
		              : _begin(allocate_node(Key(), T())), _end(allocate_node(Key(), T())), _root(_end), _alloc(alloc), _cmp(comp), _size(0), max_key(key_type()), min_key(max_key)
	      {
		      _begin->parent = _end;
		      _end->left = _begin;
		      _end->is_red = false;
		      _size = 0;
	      };

		template < class InputIterator >
		Map (InputIterator first, _ENABLE_INPUT_ITERATOR last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				: _begin(allocate_node(Key(), T())), _end(allocate_node(Key(), T())), _root(_end), _alloc(alloc), _cmp(comp), _size(0), max_key(key_type()), min_key(max_key)
		{
			_begin->parent = _end;
			_end->left = _begin;
			_end->is_red = false;
			_size = 0;
			insert(first, last);
		};


		Map (const Map& rhs) : _begin(allocate_node(Key(), T())), _end(allocate_node(Key(), T())), _root(_end), _alloc(allocator_type()), _cmp(key_compare()), _size(0), max_key(key_type()), min_key(max_key)
		{
			_begin->parent = _end;
			_end->left = _begin;
			_end->is_red = false;
			_size = 0;
			insert(rhs.begin(), rhs.end());
		};

		~Map() {
			clear();
			_deallocateNode(_begin);
			_deallocateNode(_end);
		};

		Map &operator=(Map const &rhs) {
			clear();
			insert(rhs.begin(), rhs.end());
		}

//		Iterators

		iterator					begin() {
			if (_begin->right)
				return iterator(_begin->right);
			return iterator(_begin->parent);
		};
		const_iterator 				begin() const {
			if (_begin->right)
				return const_iterator(_begin->right);
			return const_iterator(_begin->parent);
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
			if (_begin->right)
				return reverse_iterator(_begin->right);
			return reverse_iterator(_begin->parent);
		};
		const_reverse_iterator		rend() const {
			if (_begin->right)
				return const_reverse_iterator(_begin->right);
			return const_reverse_iterator(_begin->parent);
		};

//		Capacity
		bool 						empty() const {
			return _size == 0;
		};
		size_type					size() const {
			return _size;
		};
		size_type					max_size() const {
			return size_type(-1) / sizeof(node_base);
		};

//		Element access

		mapped_type &  operator[] (const key_type& key) {
			std::pair<iterator,bool> insert = this->insert(value_type(key,mapped_type()));
			iterator it = insert.first;
			return it._get_value().second;
		};

		void clear() {
			erase(begin(), end());
		};

	private:
		void rotateLeft(node_pointer n)
		{
			node_pointer pivot = n->right;

			n->right = pivot->left;

			if (pivot->left)
				pivot->left->parent = n;
			pivot->parent = n->parent;
			if (n->parent) {
				if (n->isLeft())
					n->parent->left = pivot;
				else
					n->parent->right = pivot;
			} else
				_root = pivot;
			pivot->left = n;
			n->parent = pivot;
		}

		void rotateRight(node_pointer n)
		{
			node_pointer pivot = n->left;

			n->left = pivot->right;

			if (pivot->right)
				pivot->right->parent = n;
			pivot->parent = n->parent;
			if (n->parent) {
				if (n->isLeft())
					n->parent->left = pivot;
				else
					n->parent->right = pivot;
			} else
				_root = pivot;
			pivot->right = n;
			n->parent = pivot;
		}


		void insertFixup(node_pointer n)
		{
			node_pointer u;

			while (isRed(n->parent)) {
				if (n->parent->isLeft())
				{
					u = n->uncle();
					if (isRed(u))
					{
						n->parent->is_red = false;
						u->is_red = false;
						n = n->grandparent();
						n->is_red = true;
					}
					else
					{
						if (n->isRight()) {
							n = n->parent;
							rotateLeft(n);
						}
						n->parent->is_red = false;
						n->grandparent()->is_red = true;
						rotateRight(n->grandparent());
					}
				}
				else
				{
					u = n->uncle();
					if (isRed(u))
					{
						n->parent->is_red = false;
						u->is_red = false;
						n = n->grandparent();
						n->is_red = true;
					}
					else
					{
						if (n->isLeft()) {
							n = n->parent;
							rotateRight(n);
						}
						n->parent->is_red = false;
						n->grandparent()->is_red = true;
						rotateLeft(n->grandparent());
					}
				}
			}
			_root->is_red = false;
		}

		void swapNode(node_pointer n1, node_pointer n2)
		{
			node_base tmp;
			tmp = *n2;

			*n2 = *n1;
			*n1 = tmp;

			n1->value = n2->value;
			n2->value = tmp.value;

			n1->key = n2->key;
			n2->key = tmp.key;

			if (n1 == _begin || n2 == _begin)
				_begin = n2 == _begin ? n1 : n2;
			if (n1 == _end || n2 == _end)
				_end = n2 == _end ? n1 : n2;
			if (n2->left) {
				if (n2->left == n2)
					n2->left = n1;
				n2->left->parent = n2;
			}
			if (n2->right) {
				if (n2->right == n2)
					n2->right = n1;
				n2->right->parent = n2;
			}
			if (n2->parent) {
				if (n2->parent == n2)
					n2->parent = n1;
				if (n1->left == n1 || n2->isLeft())
					n2->parent->left = n2;
				else
					n2->parent->right = n2;
			} else {
				_root = n2;
			}


			if (n1->left) {
				if (n1->left == n1)
					n1->left = n2;
				n1->left->parent = n1;
			}
			if (n1->right) {
				if (n1->right == n1)
					n1->right = n2;
				n1->right->parent = n1;
			}
			if (n1->parent) {
				if (n1->parent == n1)
					n1->parent = n2;
				if (n2 == n2->left || n1->isLeft())
					n1->parent->left = n1;
				else
					n1->parent->right = n1;
			} else {
				_root = n1;
			}
		}

		bool isRed(node_pointer n) {
			return n && n->is_red;
		}

		void transplant(node_pointer n1, node_pointer n2) {
			if (!n1->parent)
				_root = n2;
			else if (n1->isLeft())
				n1->parent->left = n2;
			else
				n1->parent->right = n2;
			if (n2)
				n2->parent = n1->parent;
		}

		void destroy(node_pointer z)
		{
			node_pointer x;
			node_pointer y = z;
			bool y_original_color = y->is_red;
			node_base 		nil;

			if (z == _end || z == _begin)
				return;
			nil.parent = nullptr;
			nil.left = nullptr;
			nil.right = nullptr;

			if (!z->left) {
				x = z->right;
				if (!x) {
					x = &nil;
					x->is_red = false;
					z->right = x;
				}
				transplant(z, z->right);
			}
			else if (!z->right) {
				x = z->left;
				if (!x) {
					x = &nil;
					x->is_red = false;
					z->left = x;
				}
				transplant(z, z->left);
			}
			else
			{
				y = base_iterator::getMore(z);
				y_original_color = y->is_red;
				x = y->right;
				if (!x) {
					x = &nil;
					x->is_red = false;
					y->right = x;
				}

				if (y->parent == z)
					x->parent = y;
				else {
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->is_red = z->is_red;
			}
			if (!y_original_color)
				deleteFixup(x);
//			--_size;
			_deallocateNode(z);
			if (nil.parent) {
				if (nil.isRight())
					nil.parent->right = nullptr;
				else if (nil.isLeft())
					nil.parent->left = nullptr;
//				tmp1->right = nullptr;
			}
		}

		void deleteFixup(node_pointer x)
		{
			node_pointer w;
			node_base 		nil;

			nil.parent = nullptr;
			nil.left = nullptr;
			nil.right = nullptr;

			while (x != _root && x->parent && !isRed(x)) {
				if (x->isLeft())
				{
					w = x->parent->right;
					if (!w) {
						w = &nil;
						w->is_red = false;
						x->parent->right = w;
					}
					if (isRed(w))
					{
						w->is_red = false;
						x->parent->is_red = true;
						rotateLeft(x->parent);
						w = x->parent->right;
						if (!w) {
							w = &nil;
							w->is_red = false;
							x->parent->right = w;
						}
					}
					if (!isRed(w->left) && !isRed(w->right))
					{
						w->is_red = true;
						x = x->parent;
					}
					else
					{
						if (!isRed(w->right))
						{
							w->left->is_red = false;
							w->is_red = true;
							rotateRight(w);
							w = x->parent->right;
							if (!w) {
								w = &nil;
								w->is_red = false;
								x->parent->right = w;
							}
						}
						w->is_red = x->parent->is_red;
						x->parent->is_red = false;
						w->right->is_red = false;
						rotateLeft(x->parent);
						x = _root;
					}
				}
				else
				{
					w = x->parent->left;
					if (!w) {
						w = &nil;
						w->is_red = false;
						x->parent->left = w;
					}
					if (isRed(w))
					{
						w->is_red = false;
						x->parent->is_red = true;
						rotateRight(x->parent);
						w = x->parent->left;
						if (!w) {
							w = &nil;
							w->is_red = false;
							x->parent->left = w;
						}
					}
					if (!isRed(w->right) && !isRed(w->left))
					{
						w->is_red = true;
						x = x->parent;
					}
					else
					{
						if (!isRed(w->left))
						{
							w->right->is_red = false;
							w->is_red = true;
							rotateLeft(w);
							w = x->parent->left;
							if (!w) {
								w = &nil;
								w->is_red = false;
								x->parent->left = w;
							}
						}
						w->is_red = x->parent->is_red;
						x->parent->is_red = false;
						w->left->is_red = false;
						rotateRight(x->parent);
						x = _root;
					}
				}
				if (nil.parent)
				{
					if (nil.isRight())
						nil.parent->right = nullptr;
					else if (nil.isLeft())
						nil.parent->left = nullptr;
				}
			}
			x->is_red = false;
			if (!x->parent)
				_root = x;
		}


	protected:
		std::pair<iterator,bool> insert (const value_type& val, node_pointer node) {
			key_type 			key = val.first;
			bool 				inserted = false;

			if (!node)
				node = _root;
			while (node) {
				if (node->key == key && node != _begin && node != _end)
					break ;
				else if ((node == _begin || _cmp(node->key, key)) && node != _end) {
					if (node->right)
						node = node->right;
					else {
						node->right = allocate_node(key, val.second, node);
						node = node->right;
						inserted = true;
					}
				}
				else {
					if (node->left)
						node = node->left;
					else {
						node->left = allocate_node(key, val.second, node);
						node = node->left;
						inserted = true;
					}
				}
			}
			insertFixup(node);
			return std::make_pair(iterator(node), inserted);
		};

	public:

		std::pair<iterator,bool> insert (const value_type& val) {
			return (insert(val, nullptr));
		};

		iterator 			insert(iterator position, const value_type& val) {
			return (insert(val, base_iterator::getBase(position)).first);
		};

		template <class InputIterator>
		void 				insert (_ENABLE_INPUT_ITERATOR begin, InputIterator end) {
			while (begin != end)
			{
				insert(*begin);
				begin++;
			}
		};


		void erase (iterator position) {
			destroy(base_iterator::getBase(position));
		};

		size_type erase (const key_type& k) {
			iterator tmp = find(k);

			if (tmp != _end)
				erase(tmp);
			return 1;
		};

		void erase (iterator first, iterator last) {
			iterator tmp;
			while (first != last)
			{
				erase(first++);
//				first++;
			}
		};

		void swap (Map& x) {
			allocator_type 	tmp_alloc = x._alloc;
			size_type 		tmp_size = x._size;
			node_pointer  	tmp_begin = x._begin;
			key_type 		tmp_max_key = x.max_key;
			node_pointer  	tmp_end = x._end;
			key_type 		tmp_min_key = x.min_key;
			node_pointer  	tmp_root = x._root;
			key_compare		tmp_cmp = x._cmp;

			x._alloc = this->_alloc;
			x._size = this->_size;
			x._begin = this->_begin;
			x.max_key = this->max_key;
			x._end = this->_end;
			x.min_key = this->min_key;
			x._root = this->_root;
			x._cmp = this->_cmp;

			this->_alloc = tmp_alloc;
			this->_size = tmp_size;
			this->_begin = tmp_begin;
			this->max_key = tmp_max_key;
			this->_end = tmp_end;
			this->min_key = tmp_min_key;
			this->_root = tmp_root;
			this->_cmp = tmp_cmp;
		};


		key_compare key_comp() const {
			return _cmp;
		}

		class value_compare
		{
//			friend class map;
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};


	protected:
		iterator findNode(const key_type& k) const
		{
			node_pointer node;

			node = _root;
			while (node && node != _begin && node != _end)
			{
				if (node->key == k)
					return node;
				else if (_cmp(k, node->key))
					node = base_iterator::getLess(node);
				else
					node = base_iterator::getMore(node);
			}
			return _end;
		}

	public:
		iterator find (const key_type& k)
		{
			return iterator(findNode(k));
		};

		const_iterator find (const key_type& k) const {
			return const_iterator(findNode(k));
		}
	};
}


#endif //FT_CONTAINERS_MAP_HPP
