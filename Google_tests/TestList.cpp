//
// Created by Holli Heimerdinger on 1/24/21.
//

#include "gtest/gtest.h"

#include <list>
#include <vector>
#include <iterator>
#include <limits>
#include <cmath>
#include <iostream>

#include "../List.hpp"

using mCon =    ft::List<double>;
using sCon =    std::list<double>;
using dataType = std::vector<double>;


class TestList : public ::testing::Test {
public:
	sCon		sEmpty;
	sCon		sTen;
	sCon		sOne;
	sCon		sTwo;
	sCon        sNotUnique;
	sCon        sUnsort1;
	sCon        sUnsort2;

	dataType    randomArray;

	mCon		mEmpty;
	mCon		mTen;
	mCon		mOne;
	mCon		mTwo;
	mCon        mNotUnique;
	mCon        mUnsort1;
	mCon        mUnsort2;

protected:
	void SetUp()
	{
		int     test_value;

		srand(static_cast<unsigned int>(time(nullptr)));
		for (int i = 0; i < 10; ++i)
		{
			test_value = rand();
			sTen.push_back(test_value);
			mTen.push_back(test_value);
		}

		mOne.push_back(10);
		sOne.push_back(10);

		mTwo.push_back(12);
		mTwo.push_back(25);

		sTwo.push_back(12);
		sTwo.push_back(25);

		for (int i = 0; i < 100; ++i) {
			randomArray.push_back(rand());
		}
		double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
		                     12.77, 73.35, 72.25, 15.3,  72.25 };
		sNotUnique.assign(mydoubles, mydoubles + 10);
		mNotUnique.assign(mydoubles, mydoubles + 10);

		double unsort1[] = { 3.1, 2.2, 2.9, 1.4, 2.3, 2.5, 0 };
		double unsort2[] = { 3.7, 7.1, 1.4 };

		sUnsort1.assign(unsort1, unsort1 + 3);
		sUnsort2.assign(unsort2, unsort2 + 3);
		mUnsort1.assign(unsort1, unsort1 + 3);
		mUnsort2.assign(unsort2, unsort2 + 3);

	}


	// a predicate implemented as a function:
	static bool single_digit (const int& value) { return (value<10); }

	// a predicate implemented as a class:
	struct is_odd {
		bool operator() (const int& value) { return (value%2)==1; }
	};

	// a binary predicate implemented as a function:
	static bool same_integral_part (double first, double second)
	{ return ( int(first)==int(second) ); }

	// a binary predicate implemented as a class:
	struct is_near {
		bool operator() (double first, double second)
		{ return (fabs(first-second)<5.0); }
	};

	static void         listComparison(const mCon & mC, const sCon & sC)
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

	static void         listIterComparison(mCon::const_iterator    mBegin,
	                                   mCon::const_iterator    mEnd,
	                                   sCon::const_iterator    sBegin,
	                                   sCon::const_iterator    sEnd)
	{
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

	static void         listRIterComparison(mCon::const_reverse_iterator    mBegin,
	                                       mCon::const_reverse_iterator    mEnd,
	                                       sCon::const_reverse_iterator    sBegin,
	                                       sCon::const_reverse_iterator    sEnd)
	{
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

TEST_F(TestList, default_constructor)
{
	mCon            mList(10);
	sCon            sList(10);

	listComparison(mList, sList);
}


TEST_F(TestList, equal_empty)
{
	listComparison(mEmpty, sEmpty);
}

TEST_F(TestList, equal_ten)
{
	listComparison(mTen, sTen);
}

TEST_F(TestList, equal_one)
{
	listComparison(mOne, sOne);
}

TEST_F(TestList, equal_two)
{
	listComparison(mTwo, sTwo);
}


TEST_F(TestList, r_equal_empty)
{
	listRIterComparison(mEmpty.rbegin(), mEmpty.rend(), sEmpty.rbegin(), sEmpty.rend());
}

TEST_F(TestList, r_equal_ten)
{
	listRIterComparison(mTen.rbegin(), mTen.rend(), sTen.rbegin(), sTen.rend());
}

TEST_F(TestList, r_equal_one)
{
	listRIterComparison(mOne.rbegin(), mOne.rend(), sOne.rbegin(), sOne.rend());
}

TEST_F(TestList, r_equal_two)
{
	listRIterComparison(mTwo.rbegin(), mTwo.rend(), sTwo.rbegin(), sTwo.rend());
}


TEST_F(TestList, empty_empty)
{
	ASSERT_EQ(mEmpty.empty(), sEmpty.empty());
}

TEST_F(TestList, empty_one)
{
	ASSERT_EQ(mOne.empty(), sOne.empty());
}

TEST_F(TestList, empty_two)
{
	ASSERT_EQ(mTwo.empty(), sTwo.empty());
}

TEST_F(TestList, empty_ten)
{
	ASSERT_EQ(mTen.empty(), sTen.empty());
}


TEST_F(TestList, max_size)
{
	ASSERT_EQ(mTwo.max_size(), sTwo.max_size());
}

TEST_F(TestList, front_empty)
{
	ASSERT_EQ(mEmpty.front(), sEmpty.front());
}

TEST_F(TestList, front_one)
{
	ASSERT_EQ(mOne.front(), sOne.front());
}

TEST_F(TestList, front_two)
{
	ASSERT_EQ(mTwo.front(), sTwo.front());
}

TEST_F(TestList, front_ten)
{
	ASSERT_EQ(mTen.front(), sTen.front());
}

TEST_F(TestList, const_front_empty)
{
	mCon const & mRef = mEmpty;
	sCon const & sRef = sEmpty;
	ASSERT_EQ(mRef.front(), sRef.front());
}

TEST_F(TestList, const_front_one)
{
	mCon const & mRef = mOne;
	sCon const & sRef = sOne;
	ASSERT_EQ(mRef.front(), sRef.front());
}

TEST_F(TestList, const_front_two)
{
	mCon const & mRef = mTwo;
	sCon const & sRef = sTwo;
	ASSERT_EQ(mRef.front(), sRef.front());
}

TEST_F(TestList, const_front_ten)
{
	mCon const & mRef = mTen;
	sCon const & sRef = sTen;
	ASSERT_EQ(mRef.front(), sRef.front());
}

TEST_F(TestList, back_empty)
{
	ASSERT_EQ(mEmpty.back(), sEmpty.back());
}

TEST_F(TestList, back_one)
{
	ASSERT_EQ(mOne.back(), sOne.back());
}

TEST_F(TestList, back_two)
{
	ASSERT_EQ(mTwo.back(), sTwo.back());
}

TEST_F(TestList, back_ten)
{
	ASSERT_EQ(mTen.back(), sTen.back());
}

TEST_F(TestList, const_back_empty)
{
	mCon const & mRef = mEmpty;
	sCon const & sRef = sEmpty;
	ASSERT_EQ(mRef.back(), sRef.back());
}

TEST_F(TestList, const_back_one)
{
	mCon const & mRef = mOne;
	sCon const & sRef = sOne;
	ASSERT_EQ(mRef.back(), sRef.back());
}

TEST_F(TestList, const_back_two)
{
	mCon const & mRef = mTwo;
	sCon const & sRef = sTwo;
	ASSERT_EQ(mRef.back(), sRef.back());
}

TEST_F(TestList, const_back_ten)
{
	mCon const & mRef = mTen;
	sCon const & sRef = sTen;
	ASSERT_EQ(mRef.back(), sRef.back());
}

TEST_F(TestList, assign_iter_empty)
{
	mEmpty.assign(randomArray.begin(), randomArray.end());
	sEmpty.assign(randomArray.begin(), randomArray.end());
	listComparison(mEmpty, sEmpty);
}

TEST_F(TestList, assign_iter_ten)
{
	mTen.assign(randomArray.begin(), randomArray.end());
	sTen.assign(randomArray.begin(), randomArray.end());
	listComparison(mTen, sTen);
}

TEST_F(TestList, assign_iter_one)
{
	mOne.assign(randomArray.begin(), randomArray.end());
	sOne.assign(randomArray.begin(), randomArray.end());
	listComparison(mOne, sOne);
}

TEST_F(TestList, assign_iter_two)
{
	mTwo.assign(randomArray.begin(), randomArray.end());
	sTwo.assign(randomArray.begin(), randomArray.end());
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, assign_val_empty)
{
	mEmpty.assign(30, 42);
	sEmpty.assign(30, 42);
	listComparison(mEmpty, sEmpty);
}

TEST_F(TestList, assign_val_ten)
{
	mTen.assign(30, 42);
	sTen.assign(30, 42);
	listComparison(mTen, sTen);
}

TEST_F(TestList, assign_val_one)
{
	mOne.assign(30, 42);
	sOne.assign(30, 42);
	listComparison(mOne, sOne);
}

TEST_F(TestList, assign_val_two)
{
	mTwo.assign(30, 42);
	sTwo.assign(30, 42);
	listComparison(mTwo, sTwo);
}

//TEST_F(TestList, pop_front_empty)
//{
//	mEmpty.pop_front();
//	sEmpty.pop_front();
//	listComparison(mEmpty, sEmpty);
//}

TEST_F(TestList, pop_front_ten)
{
	mTen.pop_front();
	sTen.pop_front();
	listComparison(mTen, sTen);
}

TEST_F(TestList, pop_front_one)
{
	mOne.pop_front();
	sOne.pop_front();
	listComparison(mOne, sOne);
}

TEST_F(TestList, pop_front_two)
{
	mTwo.pop_front();
	sTwo.pop_front();
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, pop_x2_front_two)
{
	mTwo.pop_front();
	sTwo.pop_front();
	mTwo.pop_front();
	sTwo.pop_front();
	listComparison(mTwo, sTwo);
}

//TEST_F(TestList, pop_back_empty)
//{
//	mEmpty.pop_back();
//	sEmpty.pop_back();
//	listComparison(mEmpty, sEmpty);
//}

TEST_F(TestList, pop_back_ten)
{
	mTen.pop_back();
	sTen.pop_back();
	listComparison(mTen, sTen);
}

TEST_F(TestList, pop_back_one)
{
	mOne.pop_back();
	sOne.pop_back();
	listComparison(mOne, sOne);
}

TEST_F(TestList, pop_back_two)
{
	mTwo.pop_back();
	sTwo.pop_back();
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, pop_x2_back_two)
{
	mTwo.pop_back();
	sTwo.pop_back();
	mTwo.pop_back();
	sTwo.pop_back();
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, insert_begin_empty)
{
	ASSERT_EQ(mTwo.insert(mTwo.begin(), 10), mTwo.begin());
	ASSERT_EQ(sTwo.insert(sTwo.begin(), 10), sTwo.begin());
	listComparison(mEmpty, sEmpty);
}

TEST_F(TestList, insert_begin_ten)
{
	ASSERT_EQ(mEmpty.insert(mEmpty.begin(), 10), mEmpty.begin());
	ASSERT_EQ(sEmpty.insert(sEmpty.begin(), 10), sEmpty.begin());
	listComparison(mTen, sTen);
}

TEST_F(TestList, insert_begin_one)
{
	ASSERT_EQ(mTen.insert(mTen.begin(), 10), mTen.begin());
	ASSERT_EQ(sTen.insert(sTen.begin(), 10), sTen.begin());
	listComparison(mOne, sOne);
}

TEST_F(TestList, insert_begin_two)
{
	ASSERT_EQ(mOne.insert(mOne.begin(), 10), mOne.begin());
	ASSERT_EQ(sOne.insert(sOne.begin(), 10), sOne.begin());
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, insert_many_begin_empty)
{
	mEmpty.insert(mEmpty.begin(), 10, 20);
	sEmpty.insert(sEmpty.begin(), 10, 20);
	listComparison(mEmpty, sEmpty);
}

TEST_F(TestList, insert_many_begin_ten)
{
	mTen.insert(mTen.begin(), 10, 20);
	sTen.insert(sTen.begin(), 10, 20);
	listComparison(mTen, sTen);
}

TEST_F(TestList, insert_many_begin_one)
{
	mOne.insert(mOne.begin(), 10, 20);
	sOne.insert(sOne.begin(), 10, 20);
	listComparison(mOne, sOne);
}

TEST_F(TestList, insert_many_begin_two)
{
	mTwo.insert(mTwo.begin(), 10, 20);
	sTwo.insert(sTwo.begin(), 10, 20);
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, insert_range_begin_empty)
{
	int range = rand() % randomArray.size() + 1;

	mEmpty.insert(mEmpty.begin(), randomArray.begin(), randomArray.begin() + range);
	sEmpty.insert(sEmpty.begin(), randomArray.begin(), randomArray.begin() + range);
	listComparison(mEmpty, sEmpty);
}

TEST_F(TestList, insert_range_begin_ten)
{
	int range = rand() % randomArray.size() + 1;

	mTen.insert(mTen.begin(), randomArray.begin(), randomArray.begin() + range);
	sTen.insert(sTen.begin(), randomArray.begin(), randomArray.begin() + range);
	listComparison(mTen, sTen);
}

TEST_F(TestList, insert_range_begin_one)
{
	int range = rand() % randomArray.size() + 1;

	mOne.insert(mOne.begin(), randomArray.begin(), randomArray.begin() + range);
	sOne.insert(sOne.begin(), randomArray.begin(), randomArray.begin() + range);
	listComparison(mOne, sOne);
}

TEST_F(TestList, insert_range_begin_two)
{
	int range = rand() % randomArray.size() + 1;

	mTwo.insert(mTwo.begin(), randomArray.begin(), randomArray.begin() + range);
	sTwo.insert(sTwo.begin(), randomArray.begin(), randomArray.begin() + range);
	listComparison(mTwo, sTwo);
}





TEST_F(TestList, insert_end_empty)
{
	ASSERT_EQ(mTwo.insert(mTwo.end(), 10), --mTwo.end());
	ASSERT_EQ(sTwo.insert(sTwo.end(), 10), --sTwo.end());
	listComparison(mEmpty, sEmpty);
}

TEST_F(TestList, insert_end_ten)
{
	ASSERT_EQ(mEmpty.insert(mEmpty.end(), 10), --mEmpty.end());
	ASSERT_EQ(sEmpty.insert(sEmpty.end(), 10), --sEmpty.end());
	listComparison(mTen, sTen);
}

TEST_F(TestList, insert_end_one)
{
	ASSERT_EQ(mTen.insert(mTen.end(), 10), --mTen.end());
	ASSERT_EQ(sTen.insert(sTen.end(), 10), --sTen.end());
	listComparison(mOne, sOne);
}

TEST_F(TestList, insert_end_two)
{
	ASSERT_EQ(mOne.insert(mOne.end(), 10), --mOne.end());
	ASSERT_EQ(sOne.insert(sOne.end(), 10), --sOne.end());
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, insert_many_end_empty)
{
	mEmpty.insert(mEmpty.end(), 10, 20);
	sEmpty.insert(sEmpty.end(), 10, 20);
	listComparison(mEmpty, sEmpty);
}

TEST_F(TestList, insert_many_end_ten)
{
	mTen.insert(mTen.end(), 10, 20);
	sTen.insert(sTen.end(), 10, 20);
	listComparison(mTen, sTen);
}

TEST_F(TestList, insert_many_end_one)
{
	mOne.insert(mOne.end(), 10, 20);
	sOne.insert(sOne.end(), 10, 20);
	listComparison(mOne, sOne);
}

TEST_F(TestList, insert_many_end_two)
{
	mTwo.insert(mTwo.end(), 10, 20);
	sTwo.insert(sTwo.end(), 10, 20);
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, insert_range_end_empty)
{
	int range = rand() % randomArray.size() + 1;

	mEmpty.insert(mEmpty.end(), randomArray.begin(), randomArray.begin() + range);
	sEmpty.insert(sEmpty.end(), randomArray.begin(), randomArray.begin() + range);
	listComparison(mEmpty, sEmpty);
}

TEST_F(TestList, insert_range_end_ten)
{
	int range = rand() % randomArray.size() + 1;

	mTen.insert(mTen.end(), randomArray.begin(), randomArray.begin() + range);
	sTen.insert(sTen.end(), randomArray.begin(), randomArray.begin() + range);
	listComparison(mTen, sTen);
}

TEST_F(TestList, insert_range_end_one)
{
	int range = rand() % randomArray.size() + 1;

	mOne.insert(mOne.end(), randomArray.begin(), randomArray.begin() + range);
	sOne.insert(sOne.end(), randomArray.begin(), randomArray.begin() + range);
	listComparison(mOne, sOne);
}

TEST_F(TestList, insert_range_end_two)
{
	int range = rand() % randomArray.size() + 1;

	mTwo.insert(mTwo.end(), randomArray.begin(), randomArray.begin() + range);
	sTwo.insert(sTwo.end(), randomArray.begin(), randomArray.begin() + range);
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, erase_one_ten)
{
	ASSERT_EQ(mTen.erase(mTen.begin()), mTen.begin());
	ASSERT_EQ(sTen.erase(sTen.begin()), sTen.begin());
	listComparison(mTen, sTen);
}

TEST_F(TestList, erase_one_one)
{
	ASSERT_EQ(mOne.erase(mOne.begin()), mOne.begin());
	ASSERT_EQ(sOne.erase(sOne.begin()), sOne.begin());
	listComparison(mOne, sOne);
}

TEST_F(TestList, erase_one_two)
{
	ASSERT_EQ(mTwo.erase(mTwo.begin()), mTwo.begin());
	ASSERT_EQ(sTwo.erase(sTwo.begin()), sTwo.begin());
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, erase_range_full_ten)
{
	mTen.erase(mTen.begin(), mTen.end());
	sTen.erase(sTen.begin(), sTen.end());
	listComparison(mTen, sTen);
}

TEST_F(TestList, erase_range_full_one)
{
	mOne.erase(mOne.begin(), mOne.end());
	sOne.erase(sOne.begin(), sOne.end());
	listComparison(mOne, sOne);
}

TEST_F(TestList, erase_range_full_two)
{
	mTwo.erase(mTwo.begin(), mTwo.end());
	sTwo.erase(sTwo.begin(), sTwo.end());
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, erase_range_part_ten)
{
	mTen.erase(mTen.begin(), ++(mTen.begin()));
	sTen.erase(sTen.begin(), ++(sTen.begin()));
	listComparison(mTen, sTen);
}

TEST_F(TestList, swap_empty_ten)
{
	mEmpty.swap(mTen);
	sEmpty.swap(sTen);
	listComparison(mTen, sTen);
	listComparison(mEmpty, sEmpty);

}

TEST_F(TestList, swap_ten_empty)
{
	mTen.swap(mEmpty);
	sTen.swap(sEmpty);
	listComparison(mEmpty, sEmpty);
	listComparison(mTen, sTen);
}

TEST_F(TestList, swap_one_two)
{
	mOne.swap(mTwo);
	sOne.swap(sTwo);
	listComparison(mTwo, sTwo);
	listComparison(mOne, sOne);
}

TEST_F(TestList, swap_two_one)
{
	mTwo.swap(mTen);
	sTwo.swap(sTen);
	listComparison(mTwo, sTwo);
	listComparison(mTen, sTen);
}

TEST_F(TestList, swap_two_ten)
{
	mTwo.swap(mTen);
	sTwo.swap(sTen);
	listComparison(mTwo, sTwo);
	listComparison(mTen, sTen);
}

TEST_F(TestList, resize_empty)
{
	mEmpty.resize(10, 2);
	sEmpty.resize(10, 2);
	listComparison(mEmpty, sEmpty);
}

TEST_F(TestList, resize_one)
{
	mOne.resize(10, 2);
	sOne.resize(10, 2);
	listComparison(mOne, sOne);
}

TEST_F(TestList, resize_two)
{
	mTwo.resize(10, 2);
	sTwo.resize(10, 2);
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, resize_ten)
{
	mTen.resize(10, 2);
	sTen.resize(10, 2);
	listComparison(mTen, sTen);
}

TEST_F(TestList, splice_empty)
{
	mEmpty.splice(mEmpty.begin(), mTen);
	sEmpty.splice(sEmpty.begin(), sTen);
	listComparison(mEmpty, sEmpty);
}

TEST_F(TestList, splice_one)
{
	mOne.splice(mOne.begin(), mTen);
	sOne.splice(sOne.begin(), sTen);
	listComparison(mOne, sOne);
}

TEST_F(TestList, splice_two)
{
	mTwo.splice(mTwo.begin(), mTen);
	sTwo.splice(sTwo.begin(), sTen);
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, splice_ten)
{
	mTen.splice(mTen.begin(), mTwo);
	sTen.splice(sTen.begin(), sTwo);
	listComparison(mTen, sTen);
}

TEST_F(TestList, splice_i_empty)
{
	mEmpty.splice(mEmpty.begin(), mTen, ++(mTen.begin()));
	sEmpty.splice(sEmpty.begin(), sTen, ++(sTen.begin()));
	listComparison(mEmpty, sEmpty);
}

TEST_F(TestList, splice_i_one)
{
	mOne.splice(mOne.begin(), mTen, ++(mTen.begin()));
	sOne.splice(sOne.begin(), sTen, ++(sTen.begin()));
	listComparison(mOne, sOne);
}

TEST_F(TestList, splice_i_two)
{
	mTwo.splice(mTwo.begin(), mTen, ++(mTen.begin()));
	sTwo.splice(sTwo.begin(), sTen, ++(sTen.begin()));
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, splice_i_ten)
{
	mTen.splice(mTen.begin(), mTwo, ++(mTwo.begin()));
	sTen.splice(sTen.begin(), sTwo, ++(sTwo.begin()));
	listComparison(mTen, sTen);
}


TEST_F(TestList, splice_range_empty)
{
	mEmpty.splice(mEmpty.begin(), mTen, ++(mTen.begin()), --(mTen.end()));
	sEmpty.splice(sEmpty.begin(), sTen, ++(sTen.begin()), --(sTen.end()));
	listComparison(mEmpty, sEmpty);
}

TEST_F(TestList, splice_range_one)
{
	mOne.splice(mOne.begin(), mTen, ++(mTen.begin()), --(mTen.end()));
	sOne.splice(sOne.begin(), sTen, ++(sTen.begin()), --(sTen.end()));
	listComparison(mOne, sOne);
}

TEST_F(TestList, splice_range_two)
{
	mTwo.splice(mTwo.begin(), mTen, ++(mTen.begin()), --(mTen.end()));
	sTwo.splice(sTwo.begin(), sTen, ++(sTen.begin()), --(sTen.end()));
	listComparison(mTwo, sTwo);
}


// undefined
TEST_F(TestList, splice_range_ten)
{
	mTen.splice(mTen.begin(), mTwo, ++(mTwo.begin()), --(mTwo.end()));
	sTen.splice(sTen.begin(), sTwo, ++(sTwo.begin()), --(sTwo.end()));
	listComparison(mTen, sTen);
}


TEST_F(TestList, splice_range_middle_ten)
{
	mTen.splice(++(mTen.begin()), mTwo, mTwo.begin(), mTwo.end());
	sTen.splice(++(sTen.begin()), sTwo, sTwo.begin(), sTwo.end());
	listComparison(mTen, sTen);
}

TEST_F(TestList, remove_empty)
{
	mEmpty.remove(1);
	sEmpty.remove(1);
	listComparison(mEmpty, sEmpty);
}

TEST_F(TestList, remove_one)
{
	mOne.remove(1);
	sOne.remove(1);
	listComparison(mOne, sOne);
}

TEST_F(TestList, remove_10_one)
{
	mOne.remove(10);
	sOne.remove(10);
	listComparison(mOne, sOne);
}


TEST_F(TestList, remove_1_two)
{
	mTwo.remove(1);
	sTwo.remove(1);
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, remove_25_two)
{
	mTwo.remove(25);
	sTwo.remove(25);
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, remove_12_two)
{
	mTwo.remove(25);
	sTwo.remove(25);
	listComparison(mTwo, sTwo);
}

TEST_F(TestList, remove_10_ten)
{
	mTen.remove(10);
	sTen.remove(10);
	listComparison(mTen, sTen);
}


TEST_F(TestList, remove_if_single_digit_ten)
{
	mTen.remove_if(single_digit);
	sTen.remove_if(single_digit);
	listComparison(mTen, sTen);
}

TEST_F(TestList, remove_if_is_odd_ten)
{
	mTen.remove_if(is_odd());
	sTen.remove_if(is_odd());
	listComparison(mTen, sTen);
}


TEST_F(TestList, unique)
{
	mNotUnique.unique();
	sNotUnique.unique();

	listComparison(mNotUnique, sNotUnique);
}

TEST_F(TestList, sort_unique)
{
	mNotUnique.sort();
	mNotUnique.unique();
	sNotUnique.sort();
	sNotUnique.unique();

	listComparison(mNotUnique, sNotUnique);
}

TEST_F(TestList, unique_same_integral_part)
{
	mNotUnique.unique(same_integral_part);
	sNotUnique.unique(same_integral_part);
	listComparison(mNotUnique, sNotUnique);
}

TEST_F(TestList, sort_unique_same_integral_part)
{
	mNotUnique.sort();
	mNotUnique.unique(same_integral_part);
	sNotUnique.sort();
	sNotUnique.unique(same_integral_part);
	listComparison(mNotUnique, sNotUnique);
}

TEST_F(TestList, sort_unique_is_near)
{
	mNotUnique.sort();
	mNotUnique.unique(is_near());
	sNotUnique.sort();
	sNotUnique.unique(is_near());
	listComparison(mNotUnique, sNotUnique);
}

TEST_F(TestList, merge)
{
	mUnsort1.merge(mUnsort2);
	sUnsort1.merge(sUnsort2);
	listComparison(mUnsort1, sUnsort1);
}

TEST_F(TestList, sort_merge)
{
	mUnsort2.sort();
	mUnsort1.merge(mUnsort2);
	sUnsort2.sort();
	sUnsort1.merge(sUnsort2);
	listComparison(mUnsort1, sUnsort1);
}

TEST_F(TestList, sort)
{
	mUnsort1.sort();
	sUnsort1.sort();
	listComparison(mUnsort1, sUnsort1);
}

TEST_F(TestList, reverse)
{
	mTen.reverse();
	sTen.reverse();
	listComparison(mTen, sTen);
}

TEST_F(TestList, operator_equal) {
	mCon mTest = mTen;
	sCon sTest = sTen;

	ASSERT_EQ(mTen == mTen, sTen == sTen);
	ASSERT_EQ(mEmpty == mEmpty, sEmpty == sEmpty);
	ASSERT_EQ(mOne == mTwo, sOne == sTwo);
	ASSERT_EQ(mEmpty == mTwo, sEmpty == sTwo);
	ASSERT_EQ(mOne == mTwo, sOne == sTwo);
	ASSERT_EQ(mTest == mTen, sTest == sTen);
}

TEST_F(TestList, operator_lower) {
	mCon mTest = mTen;
	sCon sTest = sTen;

	ASSERT_EQ(mTen < mTen, sTen < sTen);
	ASSERT_EQ(mEmpty < mEmpty, sEmpty < sEmpty);
	ASSERT_EQ(mOne < mTwo, sOne < sTwo);
	ASSERT_EQ(mEmpty < mTwo, sEmpty < sTwo);
	ASSERT_EQ(mOne < mTwo, sOne < sTwo);
	ASSERT_EQ(mTest < mTen, sTest < sTen);
}

TEST_F(TestList, operator_or_equal_lower) {
	mCon mTest = mTen;
	sCon sTest = sTen;

	ASSERT_EQ(mTen <= mTen, sTen <= sTen);
	ASSERT_EQ(mEmpty <= mEmpty, sEmpty <= sEmpty);
	ASSERT_EQ(mOne <= mTwo, sOne <= sTwo);
	ASSERT_EQ(mEmpty <= mTwo, sEmpty <= sTwo);
	ASSERT_EQ(mOne <= mTwo, sOne <= sTwo);
	ASSERT_EQ(mTest <= mTen, sTest <= sTen);
}


TEST_F(TestList, swap_non_member) {
	mCon mTest = mTen;
	sCon sTest = sTen;

	swap(mTen , mTen), swap(sTen , sTen);
	listComparison(mTen,sTen);
	swap(mEmpty , mEmpty), swap(sEmpty , sEmpty);
	listComparison(mEmpty,sEmpty);
	swap(mOne , mTwo), swap(sOne , sTwo);
	listComparison(mOne,sOne);
	listComparison(mTwo,sTwo);
	swap(mEmpty , mTwo), swap(sEmpty , sTwo);
	listComparison(mEmpty,sEmpty);
	listComparison(mTwo,sTwo);
	swap(mOne , mTwo), swap(sOne , sTwo);
	listComparison(mOne,sOne);
	listComparison(mTwo,sTwo);
	swap(mTest , mTen), swap(sTest , sTen);
	listComparison(mTest,sTest);
	listComparison(mTen,sTen);

}
