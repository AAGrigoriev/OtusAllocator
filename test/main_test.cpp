#include <list>
#include <gtest/gtest.h>
#include "allocator/otusAllocator.hpp"
#include "sList/simpleList.hpp"
#include "allocator/listStrategy.hpp"

using namespace std;
using namespace slist;
using namespace simple_allocator;

TEST(allocator, overflow)
{
  std::list<double, Simple_Allocator<double, 216,list_strategy>> list;
  ASSERT_NO_THROW(list.push_back(0));
  ASSERT_NO_THROW(list.push_back(0));
}

TEST(allocator, equal)
{
  std::list<double, Simple_Allocator<double, 216,list_strategy>> list1;
  ASSERT_NO_THROW(list1.push_back(0));
  ASSERT_NO_THROW(list1.push_back(0));

  std::list<double, Simple_Allocator<double, 216,list_strategy>> list2(list1);

  ASSERT_EQ(list1, list2);

  ASSERT_NE(list1.get_allocator(), list2.get_allocator());
}

TEST(allocator, compare)
{
  list<double, Simple_Allocator<double, 24,list_strategy>> list1;
  list<double, Simple_Allocator<double, 24,list_strategy>> list2;

  ASSERT_NE(list1.get_allocator(), list2.get_allocator());
}

TEST(allocator, alloc_dealloc)
{
  Simple_Allocator<double, 64,list_strategy> allocator;
  double* ptr1 = allocator.allocate(1);
  allocator.deallocate(ptr1);
  double* ptr2 = allocator.allocate(1);

  ASSERT_EQ(ptr1,ptr2);
}


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
