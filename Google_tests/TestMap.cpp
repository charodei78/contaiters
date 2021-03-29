
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
//
//TEST_F(TestMap, eraseIter)
//{
//	auto mIterator = mRandom.begin();
//	std::advance(mIterator, 10);
//	auto sIterator = sRandom.begin();
//	std::advance(sIterator, 10);
//	mRandom.erase(mIterator);
//	sRandom.erase(sIterator);
//	mapComparison(mRandom, sRandom);
//}

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
	std::cout << sTen.begin()->first << std::endl;

	mapComparison(mTen, sTen);
}