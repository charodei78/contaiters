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

			node_pointer getMore(node_pointer node) {
				if (node->right) {
					node = node->right;
					while (node->left)
						node = node->left;
					return node;
				} else {
					while (node->isRight())
						node = node->parent;
					return node->parent;
				}
			};

			node_pointer getLess(node_pointer node) {
				if (node->left) {
					node = node->left;
					while (node->right)
						node = node->right;
					return node;
				} else {
					while (node->isLeft())
						node = node->parent;
					return node->parent;
				}
			}

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
			value_type 		 operator* () const { return value_type(this->_p->value, this->_p->value); }
			pointer 		 operator->() const { return pointer(this->_p->value, this->_p->value); };
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
			value_type              *base() const { return this->_p; }
			value_type 		 		operator* () const { return value_type(this->_p->value, this->_p->value); }
			pointer 		 		operator->() const { return pointer(this->_p->value, this->_p->value); };
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
		              : _root(nullptr), _alloc(alloc), _cmp(comp), _size(0), _begin(nullptr), _end(nullptr), max_key(key_type()), min_key(max_key)
		              {};

		template < class InputIterator >
		Map (InputIterator first, _ENABLE_INPUT_ITERATOR last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				: _root(nullptr), _alloc(alloc), _cmp(comp), _size(0), _begin(nullptr), _end(nullptr), max_key(key_type()), min_key(max_key)
			{ insert(first, last); };


		Map (const Map& rhs) : _root(nullptr), _alloc(rhs._alloc), _cmp(rhs.comp), _size(0), _begin(nullptr), _end(nullptr), max_key(key_type()), min_key(max_key)
		{
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
			return size_type(-1) / sizeof(node_base);
		};

//		Element access

		mapped_type& operator[] (const key_type& key) {

			return ((this->insert(make_pair(key,mapped_type()))).first)->second;
		};

		void clear() {

		};

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
				insertCase5(n->left);
			}
			if (n->isLeft() && n->parent->isRight()) {
				rotateRight(n->parent);
				insertCase5(n->right);
			}
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

		void replaceNode(node_pointer n, node_pointer child)
		{
			child->parent = n->parent;
			if (n->isLeft())
				n->parent->left = child;
			else
				n->parent->right = child;
		}

		void destroy(node_pointer n)
		{
			node_pointer child = n->left ? n->left : n->right;

			replaceNode(n, child);
			if (!n->is_red)
			{
				if (child->is_red)
					child->is_red = false;
				else
					deleteCase1(child);
			}
			delete this;
		}

		// is root
		void deleteCase1(node_pointer n)
		{
			if (n->parent)
				deleteCase2(n);
		}

		// sibling is red
		void deleteCase2(node_pointer n)
		{
			node_pointer s = n->sibling();

			if (s->is_red)
			{
				n->parent->is_red = true;
				s->is_red = false;
				if (n->isLeft())
					rotateLeft(n);
				else
					rotateRight(n);
			}
			deleteCase3(n);
		}

		void deleteCase3(node_pointer n)
		{
			node_pointer s = n->sibling();

			if (!n->parent->is_red && !s->is_red && !n->left->is_red && !n->right->is_red)
			{
				n->is_red = true;
				deleteCase1(n->parent);
			}
			else
				deleteCase4(n);
		}

		void deleteCase4(node_pointer n)
		{
			node_pointer s = n->sibling();

			if (n->parent->is_red && !s->is_red && !n->left->is_red && !n->right->is_red)
			{
				s->is_red = true;
				n->parent->is_red = false;
			}
			else
				deleteCase5(n);
		}

		void deleteCase5(node_pointer n)
		{
			node_pointer s = n->sibling();

			if (!s->is_red)
			{
				if (n->isLeft() && !n->right->is_red && n->left->is_red)
				{
					s->is_red = true;
					s->left->is_red = false;
					rotateRight(s);
				} else if (n->isRight() && n->right->is_red && !n->left->is_red) {
					s->is_red = true;
					s->right->is_red = false;
					rotateLeft(s);
				}
			}
			deleteCase6(n);
		}

		void deleteCase6(node_pointer n)
		{
			node_pointer s = n->sibling();

			s->is_red = n->parent->is_red;
			n->parent->is_red = false;
			if (n->isLeft())
			{
				s->right->is_red = false;
				rotateLeft(n->parent);
			} else {
				s->left->is_red = false;
				rotateRight(n->parentparent);
			}
		}

	protected:
		std::pair<iterator,bool> insert (const value_type& val, node_pointer node) {
			key_type 			key = val.first;
			bool 				inserted = false;

			if (!node)
				node = _root;
			if (!node) {
				node = allocate_node(key, val.second, nullptr);
				_root = _begin = _end = node;
				max_key = min_key = key;
				insertCase1(node);
				return std::make_pair(iterator(node), true);
			}
			if (key == max_key)
				return std::make_pair(end(), true);
			if (key == min_key)
				return std::make_pair(begin(), true);
			if (_cmp(key, min_key)) {
				_begin->left = allocate_node(key, val.second, _begin);
				min_key = key;
				_begin = _begin->left;
				insertCase1(_begin);
				return std::make_pair(iterator(_begin), true);
			}
			if (!_cmp(key, max_key)) {
				_end->right = allocate_node(key, val.second, _end);
				_end = _end->right;
				max_key = key;
				insertCase1(_end);
				return std::make_pair(iterator(_end), true);
			}
			while (node) {
				if (node->key == key)
					break ;
				else if (_cmp(node->key, key)) {
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





	};
}


#endif //FT_CONTAINERS_MAP_HPP
