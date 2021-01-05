#include "gtest/gtest.h"

#include <vector>
#include <iterator>
#include <limits>
#include <iostream>

#include "../Vector.hpp"

using mVec =    ft::Vector<int>;
using sVec =    std::vector<int>;

class TestVector : public ::testing::Test {
	sVec		sEmpty;
	sVec		sTen;
	sVec		sRandom;

	mVec		mEmpty;
	mVec		mTen;
	mVec		mRandom;

public:
	TestVector() {
		int     test_value;

		sTen.reserve(10);
		mTen.reserve(10);

		srand(static_cast<unsigned int>(time(nullptr)));
		for (int i = 0; i < 10; ++i) {
			test_value = rand();
			sTen.push_back(test_value);
			mTen.push_back(test_value);
		}

		for (int i = 0; i < rand() % 100 + 1; ++i) {
			test_value = rand();
			sRandom.push_back(test_value);
			mRandom.push_back(test_value);
		}
	}

	void                        vectorComparison(const mVec & mV, const sVec & sV) {
		ASSERT_EQ(mV.size(), sV.size());
		ASSERT_EQ(mV.capacity(), sV.capacity());

		mVec::const_iterator    mBegin = mV.begin();
		mVec::const_iterator    mEnd = mV.end();

		sVec::const_iterator    sBegin = sV.begin();
		sVec::const_iterator    sEnd = sV.end();

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