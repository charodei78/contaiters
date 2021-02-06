
#include "gtest/gtest.h"

#include <queue>
#include <iterator>
#include <limits>
#include <iostream>

#include "../Queue.hpp"

using mCon =    ft::Queue<int>;
using sCon =    std::queue<int>;

class TestQueue : public ::testing::Test {
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

		srand(static_cast<unsigned int>(time(nullptr)));
		for (int i = 0; i < 10; ++i)
		{
			test_value = rand();
			sTen.push(test_value);
			mTen.push(test_value);
		}

		for (int i = 0; i < rand() % 100 + 1; ++i)
		{
			test_value = rand();
			sRandom.push(test_value);
			mRandom.push(test_value);
		}
	}

//	static void         vectorComparison(const mCon & mV, const sCon & sV)
//	{
//		ASSERT_EQ(mV.size(), sV.size());
//		ASSERT_EQ(mV.empty(), sV.empty());
//
//		mCon::const_iterator    mBegin = mV.begin();
//		mCon::const_iterator    mEnd = mV.end();
//
//		sCon::const_iterator    sBegin = sV.begin();
//		sCon::const_iterator    sEnd = sV.end();
//
//		if (!mV.empty())
//			ASSERT_EQ(*sBegin, *mBegin);
//		else if (mV.capacity())
//			ASSERT_EQ(mV[0], sV[0]);
//		ASSERT_EQ(sBegin == sEnd, mBegin == mEnd);
//
//		ASSERT_EQ(sBegin == sEnd, mBegin == mEnd);
//		while (sBegin != sEnd)
//		{
//			if (mBegin.base() && *sBegin != *mBegin)
//				std::cout << mV.size() << "  " << mV.capacity() << std::endl;
//			EXPECT_EQ(*sBegin, *mBegin);
//			++sBegin;
//			++mBegin;
//		}
//		ASSERT_EQ(sBegin == sEnd, mBegin == mEnd);
//	}


};


TEST_F(TestQueue, emptyEmpty) {
	ASSERT_EQ(mEmpty.empty(), sEmpty.empty());
}

TEST_F(TestQueue, emptyTen) {
	ASSERT_EQ(mTen.empty(), sTen.empty());
}

TEST_F(TestQueue, emptyRandom) {
	ASSERT_EQ(mRandom.empty(), sRandom.empty());
}

TEST_F(TestQueue, sizeEmpty) {
	ASSERT_EQ(mEmpty.size(), sEmpty.size());
}

TEST_F(TestQueue, sizeTen) {
	ASSERT_EQ(mTen.size(), sTen.size());
}

TEST_F(TestQueue, sizeRandom) {
	ASSERT_EQ(mRandom.size(), sRandom.size());
}

TEST_F(TestQueue, frontTen) {
	ASSERT_EQ(mTen.front(), sTen.front());
}

TEST_F(TestQueue, frontRandom) {
	ASSERT_EQ(mRandom.front(), sRandom.front());
}

TEST_F(TestQueue, backTen) {
	ASSERT_EQ(mTen.back(), sTen.back());
}

TEST_F(TestQueue, backRandom) {
	ASSERT_EQ(mRandom.back(), sRandom.back());
}

TEST_F(TestQueue, equalEmpty) {
	ASSERT_EQ(mEmpty == mEmpty, sEmpty == sEmpty);
}

TEST_F(TestQueue, equalTen) {
	ASSERT_EQ(mTen == mTen, sTen == sTen);
}

TEST_F(TestQueue, equalRandom) {
	ASSERT_EQ(mRandom == mRandom, sRandom == sRandom);
}

TEST_F(TestQueue, popTen) {
	mTen.pop();
	sTen.pop();
	ASSERT_EQ(mTen.back(), sTen.back());
	ASSERT_EQ(mTen.front(), sTen.front());
	ASSERT_EQ(mTen.size(), sTen.size());
}

TEST_F(TestQueue, popRandom) {
	mRandom.pop();
	sRandom.pop();
	ASSERT_EQ(mRandom.back(), sRandom.back());
	ASSERT_EQ(mRandom.front(), sRandom.front());
	ASSERT_EQ(mRandom.size(), sRandom.size());
}


TEST_F(TestQueue, relationalEmpty) {
	ASSERT_EQ(mEmpty > mTen, sEmpty > sTen);
}

TEST_F(TestQueue, relationalTen) {
	ASSERT_EQ(mTen < mRandom, sTen == sRandom);
}

TEST_F(TestQueue, relationalRandom) {
	ASSERT_EQ(mRandom >= mRandom, sRandom >= sRandom);
}
