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

		typedef Key                                                 key_type;
		typedef T                                                   mapped_type;
		typedef std::pair<const key_type, mapped_type>        		value_type;
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

		public:
			static node_pointer getMore(node_pointer node) {
				if (!node)
					return node;
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
				if (!node)
					return node;
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
		protected:
			base_iterator(): _p(nullptr) {};
			base_iterator(base_iterator const &rhs): _p(nullptr) {
				this->_p = rhs._p;
			}

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

			_size++;
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
		};

	public:

		class iterator: public base_iterator {
		public:
			iterator(node_pointer p): base_iterator(p) {};
			iterator(): base_iterator() {};
			iterator(iterator const &rhs): base_iterator(rhs) {}
			~iterator(){};
			node_pointer     base() const { return this->_p; }
			std::pair<const Key, T&>	_get_value() const { return std::pair<const Key, T&>(this->_p->key, this->_p->value); }
			value_type 		 operator* () const { return value_type(this->_p->key, this->_p->value); }
			iterator&        operator++() { this->_p = this->getMore(this->_p); return *this; };
			iterator         operator++(int) { iterator tmp(*this); operator++(); return tmp; }
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
			node_pointer             *base() const { return this->_p; }
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
			{ insert(first, last); };


		Map (const Map& rhs) : _begin(allocate_node(Key(), T())), _end(allocate_node(Key(), T())), _root(_end), _alloc(allocator_type()), _cmp(key_compare()), _size(0), max_key(key_type()), min_key(max_key)
		{
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

			pivot->parent = n->parent;
			if (n->parent) {
				if (n->isLeft())
					n->parent->left = pivot;
				else
					n->parent->right = pivot;
			}

			n->right = pivot->left;
			if (pivot->left)
				pivot->left->parent = n;

			n->parent = pivot;
			pivot->left = n;
			if (!pivot->parent)
				this->_root = pivot;
		}

		void rotateRight(node_pointer n)
		{
			node_pointer pivot = n->left;

			pivot->parent = n->parent;
			if (n->parent) {
				if (n->isLeft())
					n->parent->left = pivot;
				else
					n->parent->right = pivot;
			}

			n->left = pivot->right;
			if (pivot->right)
				pivot->right->parent = n;

			n->parent = pivot;
			pivot->right = n;
			if (!pivot->parent)
				this->_root = pivot;
		}

		// is root
		void insertCase1(node_pointer n)
		{

			if (n->parent == nullptr)
				n->is_red = false;
			else
				insertCase2(n);

		}

		// parent black
		void insertCase2(node_pointer n)
		{
			if (n->parent->is_red)
				insertCase3(n);
		}

		// parent and uncle is red
		void insertCase3(node_pointer n)
		{
			node_pointer u, g;

			u = n->uncle();
			if (u && u->is_red) {
				n->parent->is_red = false;
				u->is_red = false;
				g = n->grandparent();
				g->is_red = true;
				insertCase1(g);
			} else {
				insertCase4(n);
			}
		}

		// parent is red, uncle is black, node is right, parent is left (or vice versa)
		void insertCase4(node_pointer n)
		{
			if (n->isRight() && n->parent->isLeft()) {
				rotateLeft(n->parent);
				n = n->left;
			}
			if (n->isLeft() && n->parent->isRight()) {
				rotateRight(n->parent);
				n = n->right;
			}
			insertCase5(n);
		}

		// parent is red, uncle is black, node is right, parent is right (or vice versa)
		void insertCase5(node_pointer n)
		{
			node_pointer g = n->grandparent();

			n->parent->is_red = false;
			g->is_red = true;
			if (n->isLeft() && n->parent->isLeft())
				rotateRight(g);
			else
				rotateLeft(g);
		}

		void swapNode(node_pointer n1, node_pointer n2)
		{
			node_base tmp;

			if (n1->parent == n1->left || n1->parent == n1->right || n2->parent == n2->left || n2->parent == n2->right ||
				n1->parent == n1 || n1 == n1->right || n1 == n1->left || n2->parent == n2 || n2 == n2->right || n2 == n2->left)
				return;
			tmp = *n1;
			*n1 = *n2;
			if (n2->left)
				n2->left->parent = n1;
			if (n2->right)
				n2->right->parent = n1;
			if (n2->parent) {
				if (n2->isLeft())
					n2->parent->left = n1;
				else
					n2->parent->right = n1;
			} else {
				_root = n1;
			}

			*n2 = tmp;
			if (tmp.left)
				tmp.left->parent = n2;
			if (tmp.right)
				tmp.right->parent = n2;
			if (tmp.parent) {
				if (tmp.isLeft())
					tmp.parent->left = n2;
				else
					tmp.parent->right = n2;
			} else {
				_root = n2;
			}
			if (n1->parent == n1->left || n1->parent == n1->right || n2->parent == n2->left || n2->parent == n2->right)
				return;
		}

		bool isRed(node_pointer n) {
			return n && n->is_red;
		}

		void copyNode(node_pointer src, node_pointer dst)
		{
			dst->value = src->value;
			dst->key = src->key;
			if (src == _end)
				_end = dst;
			if (src == _begin)
				_begin = dst;
		}

		void replaceNode(node_pointer src, node_pointer dst)
		{
			dst->parent = src->parent;
			if (src->isLeft())
				dst->parent->left = dst;
			else
				dst->parent->right = dst;
		}

		void destroy(node_pointer n)
		{
			node_pointer child;
			node_pointer target;

			if (n->right && n->left) {
				target = base_iterator::getLess(n);
				if (target == _begin)
					target = base_iterator::getMore(n);
				swapNode(target, n);
			} else
				target = n;
			if (target->left || target->right) { // target не можнет  быть красным
				child = target->left ? target->left : target->right;
				if (child == target)
					return;
				swapNode(target, child);
				child->is_red = false;
				_deallocateNode(target);
			}
			else
				destroyZeroChild(target);
		}

		void destroyZeroChild(node_pointer n)
		{
			if (n->isLeft())
				n->parent->left = nullptr;
			else
				n->parent->right = nullptr;
			if (!n->is_red)
				balanceTree(n->parent, n->isLeft());
			_deallocateNode(n);
		}



		void balanceTree(node_pointer n, bool leftDeleted)
		{
			node_pointer child = leftDeleted ? n->right : n->left;

			if (n->is_red) {
				if ((!child->left || !child->left->is_red) && (!child->right || !child->right->is_red)) {
					child->is_red = true;
					n->is_red = false;
				}
				else if ((!child->left && child->left->is_red) || (!child->right && !child->right->is_red)) {
					n->is_red = false;
					child->is_red = true;
					if (leftDeleted)
						rotateLeft(n);
					else
						rotateRight(n);
				}
			} else {
				if (child->is_red) {
					if (!leftDeleted && child->right && !isRed(child->right->left) && !isRed(child->right->right)) {
						child->is_red = false;
						child->right->is_red = true;
						rotateRight(n);
					} else if (leftDeleted && child->left && !isRed(child->left->left) && !isRed(child->left->right)) {
						child->is_red = false;
						child->left->is_red = true;
						rotateLeft(n);
					} else if (!leftDeleted && child->right && isRed(child->right->left) && !isRed(child->right->right)) {
						child->right->left->is_red = false;
						rotateLeft(child);
						rotateRight(n);
					} else if (leftDeleted && child->left && !isRed(child->left->left) && isRed(child->left->right)) {
						child->left->right->is_red = false;
						rotateRight(child);
						rotateLeft(n);
				} else {
						if (!leftDeleted && isRed(child->right)) {
							child->right->is_red = false;
							rotateLeft(child);
							rotateRight(n);
						} else if (leftDeleted && isRed(child->left)) {
							child->left->is_red = false;
							rotateRight(child);
							rotateLeft(n);
						}
						else if (!isRed(child->right) && !isRed(child->left)) {
							if (leftDeleted)
								child->right->is_red = true;
							else
								child->left->is_red = true;
							if (n->parent)
								balanceTree(n->parent, n->isLeft());
						}
					}
				}
			}

		}



//		void destroyOneChild(node_pointer n)
//		{
//			node_pointer child = n->left ? n->left : n->right;
//
//			replaceNode(n, child);
//			if (!n->is_red)
//			{
//				if (child->is_red)
//					child->is_red = false;
//				else
//					deleteCase1(child);
//			}
//			_deallocateNode(n);
//		}
//
//		// is root
//		void deleteCase1(node_pointer n)
//		{
//			if (n->parent)
//				deleteCase2(n);
//		}
//
//		// sibling is red
//		void deleteCase2(node_pointer n)
//		{
//			node_pointer s = n->sibling();
//
//			if (s->is_red)
//			{
//				n->parent->is_red = true;
//				s->is_red = false;
//				if (n->isLeft())
//					rotateLeft(n);
//				else
//					rotateRight(n);
//			}
//			deleteCase3(n);
//		}
//
//		void deleteCase3(node_pointer n)
//		{
//			node_pointer s = n->sibling();
//
//			if (!n->parent->is_red && !s->is_red && !n->left->is_red && !n->right->is_red)
//			{
//				n->is_red = true;
//				deleteCase1(n->parent);
//			}
//			else
//				deleteCase4(n);
//		}
//
//		void deleteCase4(node_pointer n)
//		{
//			node_pointer s = n->sibling();
//
//			if (n->parent->is_red && !s->is_red && !n->left->is_red && !n->right->is_red)
//			{
//				s->is_red = true;
//				n->parent->is_red = false;
//			}
//			else
//				deleteCase5(n);
//		}
//
//		void deleteCase5(node_pointer n)
//		{
//			node_pointer s = n->sibling();
//
//			if (!s->is_red)
//			{
//				if (n->isLeft() && !n->right->is_red && n->left->is_red)
//				{
//					s->is_red = true;
//					s->left->is_red = false;
//					rotateRight(s);
//				} else if (n->isRight() && n->right->is_red && !n->left->is_red) {
//					s->is_red = true;
//					s->right->is_red = false;
//					rotateLeft(s);
//				}
//			}
//			deleteCase6(n);
//		}
//
//		void deleteCase6(node_pointer n)
//		{
//			node_pointer s = n->sibling();
//
//			s->is_red = n->parent->is_red;
//			n->parent->is_red = false;
//			if (n->isLeft())
//			{
//				s->right->is_red = false;
//				rotateLeft(n->parent);
//			} else {
//				s->left->is_red = false;
//				rotateRight(n->parent);
//			}
//		}

	protected:
		std::pair<iterator,bool> insert (const value_type& val, node_pointer node) {
			key_type 			key = val.first;
			bool 				inserted = false;

			if (!node)
				node = _root;
//			if (!node) {
//				node = allocate_node(key, val.second, nullptr);
//				_root = _begin = _end = node;
//				max_key = min_key = key;
//				insertCase1(node);
//				return std::make_pair(iterator(node), true);
//			}
//			if (key == max_key)
//				return std::make_pair(iterator(_end->parent), true);
//			if (key == min_key)
//				return std::make_pair(begin(), true);
//			if (_cmp(key, min_key)) {
//				node = allocate_node(key, val.second, _begin);
//				_begin->right = node;
//				min_key = key;
//				insertCase1(node);
//				return std::make_pair(iterator(_begin), true);
//			}
//			if (!_cmp(key, max_key)) {
//				_end->right = allocate_node(key, val.second, _end);
//				_end = _end->right;
//				max_key = key;
//				insertCase1(_end);
//				return std::make_pair(iterator(_end), true);
//			}
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
			insertCase1(node);
			return std::make_pair(iterator(node), inserted);
		};

	public:

		std::pair<iterator,bool> insert (const value_type& val) {
			return (insert(val, nullptr));
		};

		iterator 			insert(iterator position, const value_type& val) {
			return (insert(val, position.base()).first);
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
			destroy(position.base());
		};

		size_type erase (const key_type& k) {
			erase(find(k));
		};

		void erase (iterator first, iterator last) {
			while (first != last)
			{
				erase(first);
				first++;
			}
		};

		iterator find (const key_type& k);
		const_iterator find (const key_type& k) const;


	};
}


#endif //FT_CONTAINERS_MAP_HPP
