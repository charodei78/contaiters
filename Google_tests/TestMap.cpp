
#include "gtest/gtest.h"

#include <map>
#include <list>
#include <iterator>
#include <limits>
#include <iostream>

#include "../Map.hpp"

using mCon =    ft::Map<int, int>;
using sCon =    std::map<int, int>;

class TestMap : public ::testing::Test
{
public:
	sCon sEmpty;
	sCon sTen;
	sCon sRandom;

	mCon mEmpty;
	mCon mTen;
	mCon mRandom;
	std::list<std::pair<int, int>> insertValues;


protected:
	void SetUp()
	{
		int test_value;
		int test_value2;

		srand(static_cast<unsigned int>(time(nullptr)));

		for (int i = 0; i < 20; ++i)
		{
			test_value = rand();
			test_value2 = rand();
			insertValues.push_back(std::make_pair(test_value,test_value2));
		}

		for (int i = 0; i < 10; ++i)
		{
			sTen.insert(std::make_pair(i, i));
			mTen.insert(std::make_pair(i, i));
		}

		for (int i = 0; i < rand() % 80 + 40; ++i)
		{
			test_value = rand();
			sRandom.insert(std::make_pair(test_value, test_value));
			mRandom.insert(std::make_pair(test_value, test_value));
		}
	}

public:
	static void 	mapComparison(const mCon & mC, const sCon & sC)
	{
		ASSERT_EQ(mC.size(), sC.size());

		mCon::const_iterator    mBegin = mC.begin();
		mCon::const_iterator    mEnd = mC.end();

		sCon::const_iterator    sBegin = sC.begin();
		sCon::const_iterator    sEnd = sC.end();

		if (!mC.empty())
			ASSERT_EQ(*sBegin, *mBegin);
//		ASSERT_EQ(sBegin, sEnd);
		ASSERT_EQ(sBegin == sEnd, mBegin == mEnd);

		ASSERT_EQ(sBegin == sEnd, mBegin == mEnd);
		while (sBegin != sEnd)
		{
			EXPECT_EQ(*sBegin, *mBegin);
			++sBegin;
			++mBegin;
		}
		ASSERT_EQ(sBegin == sEnd, mBegin == mEnd);
	}

};


TEST_F(TestMap, iteratorTest)
{
	mCon::iterator mstart = mTen.begin();
	mCon::iterator mend = mTen.end();
	sCon::iterator sstart = sTen.begin();
	sCon::iterator send = sTen.end();


//	std::cout << (*(send2)).first << ' ' << std::endl;

	while(send != sstart)
	{
		mend--;
		send--;
		ASSERT_EQ(*mend, *send);
	}
}

TEST_F(TestMap, equalTen)
{
	mapComparison(mTen, sTen);
}

TEST_F(TestMap, equalRandom)
{
	mapComparison(mRandom, sRandom);
}

TEST_F(TestMap, operatorSqareBrackets)
{
	mTen[15] = 10;
	sTen[15] = 10;
	mapComparison(mTen, sTen);
}

TEST_F(TestMap, insertTarget)
{
	auto mIterator = mTen.insert(std::make_pair(20, 12)).first;
	mTen.insert(mIterator,std::make_pair(20, 12));
	auto sIterator = sTen.insert(std::make_pair(20, 12)).first;
	sTen.insert(sIterator,std::make_pair(20, 12));
	mapComparison(mTen, sTen);
}

TEST_F(TestMap, insertRange)
{
	mCon mMap;
	sCon sMap;

	mMap.insert(insertValues.begin(), insertValues.end());
	sMap.insert(insertValues.begin(), insertValues.end());
	mapComparison(mTen, sTen);
}

TEST_F(TestMap, eraseTen)
{
	mTen.erase(mTen.begin(), mTen.end());
}

TEST_F(TestMap, eraseIter)
{
	auto mIterator = mRandom.begin();
	std::advance(mIterator, 10);
	auto sIterator = sRandom.begin();
	std::advance(sIterator, 10);
	mRandom.erase(mIterator);
	sRandom.erase(sIterator);
	mapComparison(mRandom, sRandom);
}

TEST_F(TestMap, erase2Iter)
{
	auto mIterator = mTen.begin();
	auto sIterator = sTen.begin();
	auto mIterator2 = mIterator++;
	auto sIterator2 = sIterator++;

	std::advance(mIterator, 3);
	std::advance(sIterator, 3);


	sTen.erase(sIterator2);
	sTen.erase(sIterator);
	mTen.erase(mIterator2);
	mTen.erase(mIterator);

	mapComparison(mTen, sTen);
}

TEST_F(TestMap, eraseRangeTen)
{
	auto mIterator = mTen.begin();
	auto sIterator = sTen.begin();
	std::advance(mIterator, 2);
	std::advance(sIterator, 2);

	auto mIterator2 = mIterator;
	auto sIterator2 = sIterator;
	std::advance(mIterator2, 5);
	std::advance(sIterator2, 5);

	sTen.erase(sIterator, sIterator2);
	mTen.erase(mIterator, mIterator2);

	mapComparison(mTen, sTen);
}

TEST_F(TestMap, eraseRangeRandom)
{
	auto mIterator = mRandom.begin();
	auto sIterator = sRandom.begin();

	int size = mRandom.size();

	int val1 = rand() % size / 2;
	int val2 = rand() % size / 2;

	std::advance(sIterator, std::min(val1, val2));
	std::advance(mIterator, std::min(val1, val2));



	auto mIterator2 = mRandom.begin();
	auto sIterator2 = sRandom.begin();
	std::advance(sIterator2, std::max(val1, val2));
	std::advance(mIterator2, std::max(val1, val2));

	sTen.erase(sIterator, sIterator2);
	mTen.erase(mIterator, mIterator2);

	mapComparison(mTen, sTen);
}

TEST_F(TestMap, findTen)
{
	for (int i = 0; i < 10; ++i)
	{
		ASSERT_EQ(*mTen.find(i), *sTen.find(i));
	}
	mapComparison(mTen, sTen);
}

TEST_F(TestMap, eraseKeyTen)
{
	for (int i = 0; i < 5; ++i)
	{
		ASSERT_EQ(mTen.erase(i), sTen.erase(i));
		ASSERT_EQ(mTen.erase(9 - i), sTen.erase(9 - i));
	}
	mapComparison(mTen, sTen);
}

TEST_F(TestMap, findConstKeyTen)
{
	mCon const& mTen2 = this->mTen;
	sCon const& sTen2 = this->sTen;

	for (int i = 0; i < 10; ++i)
	{
		ASSERT_EQ(*mTen2.find(i), *sTen2.find(i));
	}
	mapComparison(mTen, sTen);
}

TEST_F(TestMap, swap)
{
	ft::Map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	foo.swap(bar);

	ASSERT_EQ(bar['x'], 100);
	ASSERT_EQ(bar['y'], 200);
	ASSERT_EQ(foo['a'], 11);
	ASSERT_EQ(foo['b'], 22);
	ASSERT_EQ(foo['c'], 33);
}

TEST_F(TestMap, clear)
{
	mRandom.clear();
	sRandom.clear();

	mapComparison(mRandom, sRandom);
}

TEST_F(TestMap, value_compare)
{
	ft::Map<char,int> mymap;

	mymap['x']=1001;
	mymap['y']=2002;
	mymap['z']=3003;

	std::cout << *(mymap.rbegin());
//	std::pair<char,int> highest = *(mymap.rbegin());          // last element
//
//	ft::Map<char,int>::iterator it = mymap.begin();
//	do {
//		std::cout << (*it).first << " => " << (*it).second << '\n';
//	} while ( mymap.value_comp()(*it++, highest) );
}