//
// Created by Holli Heimerdinger on 11/30/20.
//

//#include "Google_tests/googletest/googletest/include/gtest/gtest.h"

#include <stack>
#include <list>
#include <vector>
#include <map>
#include <iostream>
#include "Vector.hpp"
#include "Map.hpp"
#include "Stack.hpp"

template <typename Key, typename T>
struct  pair {
	T       data;
	Key     key;
	pair    *left;
	pair    *prev;
	bool	is_red;
	pair    *right;
};

typedef  ft::Map<int, int> mCon;

class A {
public:
	A(){};
};

int 		main()
{

//	std::stack<int, std::list<int>> sCon;
//	ft::Stack<int, std::list<int>> mCon;\

	std::map<int, int> map_test;

//	auto it =  map_test.end();
	ft::Map<int, int> Map_test;
//std::list<int>::allocator_type test;
//	std::cout << sizeof(pair<int, std::string>) << std::endl;
//	std::cout << sizeof(std::map<int, std::string>::pointer) << std::endl;
//	std::cout << sizeof(ft::Map<int, std::string>::value_type) << std::endl;

//	std::cout << Map_test.max_size() << std::endl;
//	std::cout << map_test.max_size() << std::endl;

//
	Map_test.insert(std::make_pair(0, 1));
	Map_test.insert(std::make_pair(1, 2));
	Map_test.insert(std::make_pair(2, 3));
	Map_test.insert(std::make_pair(3, 4));
	Map_test.insert(std::make_pair(4, 5));
	Map_test.insert(std::make_pair(5, 6));
	Map_test.insert(std::make_pair(6, 2));
	Map_test.insert(std::make_pair(7, 3));
	Map_test.insert(std::make_pair(8, 4));
	Map_test.insert(std::make_pair(9, 5));

	mCon::iterator it = Map_test.begin();
	mCon::iterator ite = Map_test.end();
	int i = 0;
	while (it != ite && ++i < 15) {
		std::cout << (*it).first << std::endl;
		++it;
	}



//	std::vector<int>		v1(100, 15);
//	std::vector<int>		v2(10, 25);
//
//	std::cout << "capacity v1 = " << v1.capacity() << " capacity v2 = " << v2.capacity() << std::endl;
//	std::cout << "size v1 = " << v1.size() << " size v2 = " << v2.size() << std::endl;
//	v2 = v1;
//	std::cout << "capacity v1 = " << v1.capacity() << " capacity v2 = " << v2.capacity() << std::endl;
//	std::cout << "size v1 = " << v1.size() << " size v2 = " << v2.size() << std::endl;
//	std::cout << v1[0] << std::endl;
//	std::cout << v1[20] << std::endl;


//	t_list *test = new t_list;
//	std::cout << test->data << std::endl;
//	std::cout << test->next << std::endl;
//	std::cout << test->prev << std::endl;
//std::vector<A*> test;
//std::list<int> list(0);
//
//size_t a = 100;
//size_t b = 1000;
//
//std::cout << (int)a - (int)b;
//
//	std::list<int>::iterator begin = list.begin();
//	std::list<int>::iterator end = list.end();
//	list.insert(end, 2);
//	begin = list.begin();
//	end = list.end();
//	list.push_back(4);
//	begin = list.begin();
//	end = list.end();
//	list.push_back(4);
//	begin = list.begin();
//	end = list.end();
//	list.push_back(4);
//	list.push_back(4);
//	list.push_back(4);

//	test.push_back(new A);
//	test.push_back(new A);
//	test.push_back(new A);
//	test.push_back(new A);
//	test.push_back(new A);
//
//	std::vector<A*>::iterator it = test.begin();
//
//	it += 3;
//
//	test.erase(it);
//	std::cout << test.size();

//	std::vector<int>		orig;
//	ft::Vector<int>			my;
//
//	my.push_back(1);
//	std::cout << "value [0] = " << my[0] << std::endl;
//	std::cout << "capacity = " << my.capacity() << std::endl;
//	std::cout << "size = " << my.size() << std::endl;
//	my.push_back(2);
//	std::cout << "value [1] = " << my[1] << std::endl;
//	std::cout << "capacity = " << my.capacity() << std::endl;
//	std::cout << "size = " << my.size() << std::endl;
//	my.push_back(3);
//	std::cout << "value [2] = " << my[2] << std::endl;
//	std::cout << "capacity = " << my.capacity() << std::endl;
//	std::cout << "size = " << my.size() << std::endl;
//
//	ft::Vector<int>::iterator it(my.begin());
//	ft::Vector<int>::iterator it2 = my.begin();
//	ft::Vector<int>::const_iterator     const_it2 = my.begin();
//	ft::Vector<int>::const_iterator     const_it = it;
////	ft::Vector<int>::iterator it3 = const_it2;
////	it = const_it;
//	const_it = it;
//	const_it = const_it2;
//	std::cout << "iter  = " << *(const_it) << std::endl;
//
//
//	for (; it != my.end(); it++)
//		std::cout << "iter  = " << *it << std::endl;
//	ft::Vector<int>::iterator     test = it;
//	ft::Vector<int>::const_iterator     test2 = const_it;





	return (0);

}