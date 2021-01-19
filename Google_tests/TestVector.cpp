#include "gtest/gtest.h"

#include <vector>
#include <iterator>
#include <limits>
#include <iostream>

#include "../Vector.hpp"

using mCon =    ft::Vector<int>;
using sCon =    std::vector<int>;

class TestVector : public ::testing::Test {
public:
	sCon		sEmpty;
	sCon		sTen;
	sCon		sRandom;

	mCon		mEmpty;
	mCon		mTen;
	mCon		mRandom;

protected:
	void SetUp()
	{
		int     test_value;

		sTen.reserve(10);
		mTen.reserve(10);

		srand(static_cast<unsigned int>(time(nullptr)));
		for (int i = 0; i < 10; ++i)
		{
			test_value = rand();
			sTen.push_back(test_value);
			mTen.push_back(test_value);
		}

		for (int i = 0; i < rand() % 100 + 1; ++i)
		{
			test_value = rand();
			sRandom.push_back(test_value);
			mRandom.push_back(test_value);
		}
	}

	static void         vectorComparison(const mCon & mV, const sCon & sV)
	{
		ASSERT_EQ(mV.size(), sV.size());
		ASSERT_EQ(mV.capacity(), sV.capacity());

		mCon::const_iterator    mBegin = mV.begin();
		mCon::const_iterator    mEnd = mV.end();

		sCon::const_iterator    sBegin = sV.begin();
		sCon::const_iterator    sEnd = sV.end();

		if (!mV.empty())
			ASSERT_EQ(*sBegin, *mBegin);
		else if (mV.capacity())
			ASSERT_EQ(mV[0], sV[0]);
		ASSERT_EQ(sBegin == sEnd, mBegin == mEnd);

		ASSERT_EQ(sBegin == sEnd, mBegin == mEnd);
		while (sBegin != sEnd)
		{
			if (mBegin.base() && *sBegin != *mBegin)
				std::cout << mV.size() << "  " << mV.capacity() << std::endl;
			EXPECT_EQ(*sBegin, *mBegin);
			++sBegin;
			++mBegin;
		}
		ASSERT_EQ(sBegin == sEnd, mBegin == mEnd);
	}


};

TEST_F(TestVector, eqBaseTest)
{
	vectorComparison(mEmpty, sEmpty);
	vectorComparison(mTen, sTen);
	vectorComparison(mRandom, sRandom);
}

TEST_F(TestVector, emptyCopyConstructorTest)
{
	mCon        mCopy(mEmpty);
	sCon        sCopy(sEmpty);

	vectorComparison(mCopy, sCopy);
}

TEST_F(TestVector, tenCopyConstructorTest)
{
	mCon        mCopy(mTen);
	sCon        sCopy(sTen);

	vectorComparison(mCopy, sCopy);
}

TEST_F(TestVector, randomCopyConstructorTest)
{
	mCon        mCopy(mRandom);
	sCon        sCopy(sRandom);

	vectorComparison(mCopy, sCopy);
}

TEST_F(TestVector, emptyRangeConstructorTest)
{
	mCon        mCopy(mEmpty.begin(), mEmpty.end());
	sCon        sCopy(sEmpty.begin(), sEmpty.end());

	vectorComparison(mCopy, sCopy);
}

TEST_F(TestVector, tenRangeConstructorTest)
{
	mCon        mCopy(mTen.begin(), mTen.end());
	sCon        sCopy(sTen.begin(), sTen.end());

	vectorComparison(mCopy, sCopy);
}

TEST_F(TestVector, randomRangeConstructorTest)
{
	mCon        mCopy(mRandom.begin(), mRandom.end());
	sCon        sCopy(sRandom.begin(), sRandom.end());

	vectorComparison(mCopy, sCopy);
}

TEST_F(TestVector, emptyEqOperatorTest)
{
	mCon        mCopy;
	sCon        sCopy;

	mCopy = mEmpty;
	sCopy = sEmpty;

	vectorComparison(mCopy, sCopy);
}

TEST_F(TestVector, tenEqOperatorTest)
{
	mCon        mCopy;
	sCon        sCopy;

	mCopy = mTen;
	sCopy = sTen;

	vectorComparison(mCopy, sCopy);
}

TEST_F(TestVector, randomEqOperatorTest)
{
	mCon        mCopy;
	sCon        sCopy;

	mCopy = mRandom;
	sCopy = sRandom;

	vectorComparison(mCopy, sCopy);
}

TEST_F(TestVector, constructorWithDefaultValue)
{
	mCon        mDef(12, 4);
	sCon        sDef(12, 4);

	vectorComparison(mDef, sDef);
}

// Iterators

TEST_F(TestVector, iteratorTest)
{
	mCon::iterator mIt = mEmpty.begin();
	sCon::iterator sIt = sEmpty.begin();

	mCon::const_iterator mItConst = mTen.begin();
	sCon::const_iterator sItConst = sTen.begin();

	mItConst = mIt;
	sItConst = sIt;

//	mIt = mItConst;
//	sIt = sItConst;
}

TEST_F(TestVector, iteratorPlusTest)
{
	mCon::iterator mIt = mTen.begin();
	sCon::iterator sIt = sTen.begin();

	mCon::iterator mIt2 = mIt + 4;
	sCon::iterator sIt2 = sIt + 4;

	mIt++;mIt++;mIt++;mIt++;
	sIt++;sIt++;sIt++;sIt++;

	ASSERT_EQ(mIt, mIt2);
	ASSERT_EQ(sIt, sIt2);
	ASSERT_EQ(*sIt, *mIt);
	ASSERT_EQ(*sIt2, *mIt2);


//	mIt = mItConst;
//	sIt = sItConst;
}

TEST_F(TestVector, reverceIterator)
{
	mCon::reverse_iterator mBegin = mTen.rbegin();
	mCon::reverse_iterator mEnd = mTen.rend();
	mCon::const_reverse_iterator mBeginC = mTen.rbegin();
	mCon::const_reverse_iterator mEndC = mTen.rend();

	sCon::reverse_iterator sBegin = sTen.rbegin();
	sCon::reverse_iterator sEnd = sTen.rend();
	sCon::const_reverse_iterator sBeginC = sTen.rbegin();
	sCon::const_reverse_iterator sEndC = sTen.rend();

	++sBegin;
	++mBegin;
	--sBegin;
	--mBegin;

	ASSERT_EQ(sBegin == sEnd, mBegin == mEnd);
	while (sBegin != sEnd)
	{
		EXPECT_EQ(*sBegin, *mBegin);
		++sBegin;
		++mBegin;
	}
	ASSERT_EQ(sBegin == sEnd, mBegin == mEnd);
}

TEST_F(TestVector, reverceConstIterator)
{
	mCon::const_reverse_iterator mBegin = mTen.rbegin();
	mCon::const_reverse_iterator mEnd = mTen.rend();

	sCon::const_reverse_iterator sBegin = sTen.rbegin();
	sCon::const_reverse_iterator sEnd = sTen.rend();

	++sBegin;
	++mBegin;
	--sBegin;
	--mBegin;

	ASSERT_EQ(sBegin == sEnd, mBegin == mEnd);
	while (sBegin != sEnd)
	{
		EXPECT_EQ(*sBegin, *mBegin);
		++sBegin;
		++mBegin;
	}
	ASSERT_EQ(sBegin == sEnd, mBegin == mEnd);
}

// Capacity


TEST_F(TestVector, sizeTest)
{
	ASSERT_EQ(mTen.size(), sTen.size());

	mTen.push_back(10);
	mTen.push_back(10);

	sTen.push_back(10);
	sTen.push_back(10);

	ASSERT_EQ(mTen.size(), sTen.size());

	mTen.push_back(10);
	mTen.push_back(10);

	sTen.push_back(10);
	sTen.push_back(10);

	ASSERT_EQ(mTen.size(), sTen.size());

	mEmpty.push_back(10);
	mEmpty.push_back(10);

	sEmpty.push_back(10);
	sEmpty.push_back(10);

	ASSERT_EQ(mEmpty.size(), sEmpty.size());
	vectorComparison(mEmpty, sEmpty);
}

TEST_F(TestVector, maxSizeTest)
{
	ASSERT_EQ(mTen.max_size(), sTen.max_size());

	mTen.push_back(10);
	mTen.push_back(10);

	sTen.push_back(10);
	sTen.push_back(10);
	ASSERT_EQ(mTen.max_size(), sTen.max_size());

	mTen.push_back(10);
	mTen.push_back(10);

	sTen.push_back(10);
	sTen.push_back(10);

	ASSERT_EQ(mTen.max_size(), sTen.max_size());

	mEmpty.push_back(10);
	mEmpty.push_back(10);

	sEmpty.push_back(10);
	sEmpty.push_back(10);

	ASSERT_EQ(mEmpty.max_size(), sEmpty.max_size());
	vectorComparison(mEmpty, sEmpty);


	mRandom.push_back(10);
	mRandom.push_back(10);

	sRandom.push_back(10);
	sRandom.push_back(10);

	ASSERT_EQ(mRandom.max_size(), sRandom.max_size());
	vectorComparison(mTen, sTen);
}

TEST_F(TestVector, resizeTenTest)
{
	mTen.resize(10);
	sTen.resize(10);

	vectorComparison(mTen, sTen);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	mTen.resize(5);
	sTen.resize(5);

	vectorComparison(mTen, sTen);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	mTen.resize(11);
	sTen.resize(11);

	vectorComparison(mTen, sTen);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	mTen.resize(16);
	sTen.resize(16);

	vectorComparison(mTen, sTen);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	mTen.resize(0);
	sTen.resize(0);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	vectorComparison(mTen, sTen);
}

TEST_F(TestVector, resizeRandomTest)
{

	mRandom.resize(10);
	sRandom.resize(10);

	vectorComparison(mRandom, sRandom);

	ASSERT_EQ(mRandom.capacity(), sRandom.capacity());
	ASSERT_EQ(mRandom.size(), sRandom.size());

	mRandom.resize(5);
	sRandom.resize(5);

	vectorComparison(mRandom, sRandom);

	ASSERT_EQ(mRandom.capacity(), sRandom.capacity());
	ASSERT_EQ(mRandom.size(), sRandom.size());

	mRandom.resize(11);
	sRandom.resize(11);

	vectorComparison(mRandom, sRandom);

	ASSERT_EQ(mRandom.capacity(), sRandom.capacity());
	ASSERT_EQ(mRandom.size(), sRandom.size());

	mRandom.resize(16);
	sRandom.resize(16);

	vectorComparison(mRandom, sRandom);

	ASSERT_EQ(mRandom.capacity(), sRandom.capacity());
	ASSERT_EQ(mRandom.size(), sRandom.size());

	mRandom.resize(0);
	sRandom.resize(0);

	ASSERT_EQ(mRandom.capacity(), sRandom.capacity());
	ASSERT_EQ(mRandom.size(), sRandom.size());

	vectorComparison(mRandom, sRandom);
}

TEST_F(TestVector, resizeRandom30Test)
{
	for (int i = 0; i < 30; ++i) {
		mRandom.resize(mRandom.size() + 1);
		sRandom.resize(sRandom.size() + 1);

		ASSERT_EQ(mRandom.capacity(), sRandom.capacity());
		ASSERT_EQ(mRandom.size(), sRandom.size());

		vectorComparison(mRandom, sRandom);
	}
}

TEST_F(TestVector, resizeValueTest)
{
	mTen.resize(10, 42);
	sTen.resize(10, 42);

	vectorComparison(mTen, sTen);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	mTen.resize(5, 42);
	sTen.resize(5, 42);

	vectorComparison(mTen, sTen);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	mTen.resize(11, 42);
	sTen.resize(11, 42);

	vectorComparison(mTen, sTen);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	mTen.resize(16, 42);
	sTen.resize(16, 42);

	vectorComparison(mTen, sTen);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	mTen.resize(0, 42);
	sTen.resize(0, 42);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	vectorComparison(mTen, sTen);
}

TEST_F(TestVector, capacityReallocTest)
{
	ASSERT_EQ(mTen.capacity(), sTen.capacity());

	mTen.push_back(10);
	mTen.push_back(10);

	sTen.push_back(10);
	sTen.push_back(10);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());

	mTen.push_back(10);
	mTen.push_back(10);

	sTen.push_back(10);
	sTen.push_back(10);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());

	mEmpty.push_back(10);
	mEmpty.push_back(10);

	sEmpty.push_back(10);
	sEmpty.push_back(10);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	vectorComparison(mTen, sTen);
}

TEST_F(TestVector, emptyTest)
{
	ASSERT_EQ(mEmpty.empty(), sEmpty.empty());
	ASSERT_EQ(mTen.empty(), sTen.empty());
	ASSERT_EQ(mRandom.empty(), mRandom.empty());
}

TEST_F(TestVector, reserveTest)
{

	mTen.reserve(10);
	sTen.reserve(10);

	vectorComparison(mTen, sTen);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	mTen.reserve(5);
	sTen.reserve(5);

	vectorComparison(mTen, sTen);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	mTen.reserve(11);
	sTen.reserve(11);

	vectorComparison(mTen, sTen);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	mTen.reserve(16);
	sTen.reserve(16);

	vectorComparison(mTen, sTen);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	mTen.reserve(0);
	sTen.reserve(0);

	ASSERT_EQ(mTen.capacity(), sTen.capacity());
	ASSERT_EQ(mTen.size(), sTen.size());

	vectorComparison(mTen, sTen);
}

// Element access

TEST_F(TestVector, AtTest)
{
	ASSERT_THROW(mEmpty.at(10), std::out_of_range);
	ASSERT_THROW(sEmpty.at(10), std::out_of_range);
	ASSERT_THROW(mTen.at(10), std::out_of_range);
	ASSERT_THROW(mRandom.at(mRandom.size()), std::out_of_range);
	ASSERT_THROW(mEmpty.at(-1), std::out_of_range);
	ASSERT_THROW(mTen.at(-1), std::out_of_range);
	ASSERT_THROW(mRandom.at(-1), std::out_of_range);
}

TEST_F(TestVector, frontTest)
{
	ASSERT_EQ(mTen.front(), sTen.front());
	ASSERT_EQ(mRandom.front(), sRandom.front());

	mEmpty.push_back(10);
	sEmpty.push_back(10);
	ASSERT_EQ(mEmpty.front(), sEmpty.front());
}

TEST_F(TestVector, backTest)
{
	ASSERT_EQ(mTen.back(), sTen.back());
	ASSERT_EQ(mRandom.back(), sRandom.back());

	mEmpty.push_back(10);
	sEmpty.push_back(10);
	ASSERT_EQ(mEmpty.back(), sEmpty.back());
}

// Modifiers

TEST_F(TestVector, assignTest)
{
	mEmpty.assign(100, 10);
	sEmpty.assign(100, 10);

	vectorComparison(mEmpty, sEmpty);

	mTen.assign(1, 10);
	sTen.assign(1, 10);

	vectorComparison(mEmpty, sEmpty);

	mTen.assign(11, 42);
	sTen.assign(11, 42);

	vectorComparison(mEmpty, sEmpty);
}

TEST_F(TestVector, assignRangeTest)
{
	sCon                data(100, 12);
	sCon::iterator      it = data.begin();
	sCon::iterator      ite = data.end();

	it.operator*();
	mEmpty.assign(it, it + 1);
	sEmpty.assign(it, it + 1);

	vectorComparison(mEmpty, sEmpty);

	mEmpty.assign(it, ite);
	sEmpty.assign(it, ite);

	vectorComparison(mEmpty, sEmpty);
}

TEST_F(TestVector, pop_backTest)
{
	sEmpty.pop_back();
	mEmpty.pop_back();
	ASSERT_EQ(sEmpty.size(), mEmpty.size());
	ASSERT_EQ(sEmpty.capacity(), mEmpty.capacity());

	sTen.pop_back();
	mTen.pop_back();
	ASSERT_EQ(sTen.size(), mTen.size());
	ASSERT_EQ(sTen.capacity(), mTen.capacity());
	vectorComparison(mTen, sTen);
}

TEST_F(TestVector, insertSingleValueEmptyTest)
{
	sEmpty.insert(sEmpty.begin(), 42);
	mEmpty.insert(mEmpty.begin(), 42);
	vectorComparison(mEmpty, sEmpty);
}

TEST_F(TestVector, insertSingleValueTenTest)
{
	sTen.insert(sTen.begin(), 42);
	mTen.insert(mTen.begin(), 42);
	vectorComparison(mTen, sTen);
}

TEST_F(TestVector, insertSingleValueRandomTest)
{
	sRandom.insert(sRandom.begin(), 42);
	mRandom.insert(mRandom.begin(), 42);
	vectorComparison(mRandom, sRandom);
}

TEST_F(TestVector, insertSingleValueMiddleRandomTest)
{
	size_t      offset;

	for (int i = 0; i < 10; ++i) {
		offset = rand() % mRandom.size() + 1;
		ASSERT_EQ(*sRandom.insert(sRandom.begin() + offset, 42),
		          *mRandom.insert(mRandom.begin() + offset, 42));
		vectorComparison(mRandom, sRandom);
	}
}

TEST_F(TestVector, insertValuesToBeginEmptyTest)
{
	sEmpty.insert(sEmpty.begin(), 10, 42);
	mEmpty.insert(mEmpty.begin(), 10, 42);
	vectorComparison(mEmpty, sEmpty);
}

TEST_F(TestVector, insertValuesToBeginTenTest)
{
	sTen.insert(sTen.begin(), 10, 42);
	mTen.insert(mTen.begin(), 10, 42);
	vectorComparison(mTen, sTen);
}

TEST_F(TestVector, insertValuesToBeginRandomTest)
{
	vectorComparison(mRandom, sRandom);

	sRandom.insert(sRandom.begin(), 10, 42);
	mRandom.insert(mRandom.begin(), 10, 42);
	vectorComparison(mRandom, sRandom);
}

TEST_F(TestVector, insertValuesToEndEmptyTest)
{
	sEmpty.insert(sEmpty.end(), 10, 42);
	mEmpty.insert(mEmpty.end(), 10, 42);
	vectorComparison(mEmpty, sEmpty);
}

TEST_F(TestVector, insertValuesToEndTenTest)
{
	sTen.insert(sTen.end(), 10, 42);
	mTen.insert(mTen.end(), 10, 42);
	vectorComparison(mTen, sTen);
}

TEST_F(TestVector, insertValuesToEndRandomTest)
{
	sRandom.insert(sRandom.end(), 10, 42);
	mRandom.insert(mRandom.end(), 10, 42);
	vectorComparison(mRandom, sRandom);
}

TEST_F(TestVector, insertValuesToMiddleTenTest)
{
	sTen.insert(sTen.begin() + 4, 10, 42);
	mTen.insert(mTen.begin() + 4, 10, 42);
	vectorComparison(mTen, sTen);
}

TEST_F(TestVector, insertValuesToMiddleRandomTest)
{
	size_t offset = 100 % mRandom.size();
	sRandom.insert(sRandom.begin() + offset, 10, 42);
	mRandom.insert(mRandom.begin() + offset, 10, 42);
	vectorComparison(mRandom, sRandom);
}

TEST_F(TestVector, insertAtotherContainerTest)
{
	sCon        sAnotherContainer;
	mCon        mAnotherContainer;

	mEmpty.insert(mAnotherContainer.begin(), 10, 42);
	sEmpty.insert(sAnotherContainer.begin(), 10, 42);
	vectorComparison(mEmpty, sEmpty);
}

TEST_F(TestVector, insertRangeBeginEmptyTest)
{
	sCon                data(100, 12);
	sCon::iterator      it = data.begin();
	sCon::iterator      ite = data.end();
//	mCon::iterator      mite = mEmpty.end();

	mEmpty.insert(mEmpty.begin(), it, ite);
	sEmpty.insert(sEmpty.begin(), it, ite);
	vectorComparison(mEmpty, sEmpty);
}

TEST_F(TestVector, insertRangeBeginTenTest)
{
	sCon                data(100, 12);
	sCon::iterator      it = data.begin();
	sCon::iterator      ite = data.end();

	mEmpty.insert(mEmpty.begin(), it, ite);
	sEmpty.insert(sEmpty.begin(), it, ite);
	vectorComparison(mEmpty, sEmpty);
}

TEST_F(TestVector, insertRangeBeginRandomTest)
{
	sCon                data(100, 12);
	sCon::iterator      it = data.begin();
	sCon::iterator      ite = data.end();

	mEmpty.insert(mEmpty.begin(), it, ite);
	sEmpty.insert(sEmpty.begin(), it, ite);
	vectorComparison(mEmpty, sEmpty);
}

TEST_F(TestVector, insertRangeEndEmptyTest)
{
	sCon                data(100, 12);
	sCon::iterator      it = data.begin();
	sCon::iterator      ite = data.end();
//	mCon::iterator      mite = mEmpty.end();

	mEmpty.insert(mEmpty.end(), it, ite);
	sEmpty.insert(sEmpty.end(), it, ite);
	vectorComparison(mEmpty, sEmpty);
}

TEST_F(TestVector, insertRangeEndTenTest)
{
	sCon                data(100, 12);
	sCon::iterator      it = data.begin();
	sCon::iterator      ite = data.end();

	mTen.insert(mTen.end(), it, ite);
	sTen.insert(sTen.end(), it, ite);
	vectorComparison(mTen, sTen);
}

TEST_F(TestVector, insertRangeEndRandomTest)
{
	sCon                data(100, 12);
	sCon::iterator      it = data.begin();
	sCon::iterator      ite = data.end();

	mRandom.insert(mRandom.end(), it, ite);
	sRandom.insert(sRandom.end(), it, ite);
	vectorComparison(mRandom, sRandom);
}


TEST_F(TestVector, insertRangeMiddleRandomTest)
{
	sCon                data(100, 12);
	sCon::iterator      it = data.begin();
	sCon::iterator      ite = data.end();

	size_t offset = rand() % mRandom.size() + 1;
	mRandom.insert(mRandom.begin() + offset, it, ite);
	sRandom.insert(sRandom.begin() + offset, it, ite);
	vectorComparison(mRandom, sRandom);
}

TEST_F(TestVector, eriseRandomTest)
{
	for (int i = 0; i < mRandom.size(); ++i) {
		ASSERT_EQ(*mRandom.erase(mRandom.begin()), *sRandom.erase(sRandom.begin()));
	}
}

TEST_F(TestVector, eriseRandomOffsetTest)
{
	size_t offset;

	for (int i = 0; i < mRandom.size(); ++i) {
		offset = rand() % mRandom.size();
		ASSERT_EQ(*mRandom.erase(mRandom.begin() + offset), *sRandom.erase(sRandom.begin() + offset));
	}
	EXPECT_EQ(mRandom.erase(mRandom.begin())[0], sRandom.erase(sRandom.begin())[0]);
}

TEST_F(TestVector, eriseRandomRangeTest)
{
	for (int i = 0; i < mRandom.size(); ++i) {
		ASSERT_EQ(*mRandom.erase(mRandom.begin()), *sRandom.erase(sRandom.begin()));
	}
}

TEST_F(TestVector, swapTest)
{
	mEmpty.swap(mRandom);
	sEmpty.swap(sRandom);
	vectorComparison(mEmpty, sEmpty);
	vectorComparison(mRandom, sRandom);
}

TEST_F(TestVector, clearRandomTest)
{
	sRandom.clear();
	mRandom.clear();
	vectorComparison(mRandom, sRandom);
}

TEST_F(TestVector, clearEmptyTest)
{
	sEmpty.clear();
	mEmpty.clear();
	vectorComparison(mEmpty, sEmpty);
}

TEST_F(TestVector, clearTenTest)
{
	sTen.clear();
	mTen.clear();
	vectorComparison(mTen, sTen);
}