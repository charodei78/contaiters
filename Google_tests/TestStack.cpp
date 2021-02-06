
#include "gtest/gtest.h"

#include <stack>
#include <iterator>
#include <limits>
#include <iostream>

#include "../Stack.hpp"

using mCon =    ft::Stack<int>;
using sCon =    std::stack<int>;

class TestStack : public ::testing::Test {
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


TEST_F(TestStack, emptyEmpty) {
	ASSERT_EQ(mEmpty.empty(), sEmpty.empty());
}

TEST_F(TestStack, emptyTen) {
	ASSERT_EQ(mTen.empty(), sTen.empty());
}

TEST_F(TestStack, emptyRandom) {
	ASSERT_EQ(mRandom.empty(), sRandom.empty());
}

TEST_F(TestStack, sizeEmpty) {
	ASSERT_EQ(mEmpty.size(), sEmpty.size());
}

TEST_F(TestStack, sizeTen) {
	ASSERT_EQ(mTen.size(), sTen.size());
}

TEST_F(TestStack, sizeRandom) {
	ASSERT_EQ(mRandom.size(), sRandom.size());
}

TEST_F(TestStack, topTen) {
	ASSERT_EQ(mTen.top(), sTen.top());
}

TEST_F(TestStack, topRandom) {
	ASSERT_EQ(mRandom.top(), sRandom.top());
}

TEST_F(TestStack, equalEmpty) {
	ASSERT_EQ(mEmpty == mEmpty, sEmpty == sEmpty);
}

TEST_F(TestStack, equalTen) {
	ASSERT_EQ(mTen == mTen, sTen == sTen);
}

TEST_F(TestStack, equalRandom) {
	ASSERT_EQ(mRandom == mRandom, sRandom == sRandom);
}

TEST_F(TestStack, popTen) {
	mTen.pop();
	sTen.pop();
	ASSERT_EQ(mTen.top(), sTen.top());
	ASSERT_EQ(mTen.size(), sTen.size());
}

TEST_F(TestStack, popRandom) {
	mRandom.pop();
	sRandom.pop();
	ASSERT_EQ(mRandom.top(), sRandom.top());
	ASSERT_EQ(mRandom.size(), sRandom.size());
}


TEST_F(TestStack, relationalEmpty) {
	ASSERT_EQ(mEmpty > mTen, sEmpty > sTen);
}

TEST_F(TestStack, relationalTen) {
	ASSERT_EQ(mTen < mRandom, sTen == sRandom);
}

TEST_F(TestStack, relationalRandom) {
	ASSERT_EQ(mRandom >= mRandom, sRandom >= sRandom);
}
