//
// Created by Holli Heimerdinger on 11/30/20.
//

#include <stack>
#include <list>
#include <vector>
#include <iostream>
#include "Vector.hpp"

int 		main()
{
	std::vector<int>		orig;
	ft::Vector<int>			my;

	my.push_back(1);
	std::cout << "value [0] = " << my[0] << std::endl;
	std::cout << "capacity = " << my.capacity() << std::endl;
	std::cout << "size = " << my.size() << std::endl;
	my.push_back(2);
	std::cout << "value [1] = " << my[1] << std::endl;
	std::cout << "capacity = " << my.capacity() << std::endl;
	std::cout << "size = " << my.size() << std::endl;
	my.push_back(3);
	std::cout << "value [2] = " << my[2] << std::endl;
	std::cout << "capacity = " << my.capacity() << std::endl;
	std::cout << "size = " << my.size() << std::endl;

	ft::Vector<int>::iterator it(my.begin());
	ft::Vector<int>::iterator it2 = my.begin();
	ft::Vector<int>::const_iterator     const_it2 = my.begin();
	ft::Vector<int>::const_iterator     const_it = it;
//	ft::Vector<int>::iterator it3 = const_it2;
//	it = const_it;
	const_it = it;
	const_it = const_it2;
	std::cout << "iter  = " << *(const_it) << std::endl;


	for (; it != my.end(); it++)
		std::cout << "iter  = " << *it << std::endl;
	ft::Vector<int>::iterator     test = it;
	ft::Vector<int>::const_iterator     test2 = const_it;





	return (0);

}