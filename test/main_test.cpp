#include <list>
#include <gtest/gtest.h>
#include "allocator/otusAllocator.hpp"
#include "sList/simpleList.hpp"

using namespace std;
using namespace slist;
using namespace simple_allocator;

/*TEST(allocator, overflow)
{
  std::list<double, Light_Pool_Allocator<double, 216>> list;
  ASSERT_NO_THROW(list.push_back(0));
  ASSERT_NO_THROW(list.push_back(0));
}

TEST(allocator, equal)
{
  std::list<double, Light_Pool_Allocator<double, 216>> list1;
  ASSERT_NO_THROW(list1.push_back(0));
  ASSERT_NO_THROW(list1.push_back(0));

  std::list<double, Light_Pool_Allocator<double, 216>> list2(list1);

  ASSERT_EQ(list1, list2);
}

TEST(allocator, compare)
{

  list<double, Light_Pool_Allocator<double, 24>> list1;
  list<double, Light_Pool_Allocator<double, 24>> list2;

  ASSERT_NE(list1.get_allocator(), list2.get_allocator());
}

TEST(allocator, alloc_dealloc)
{
  Light_Pool_Allocator<double, 64> allocator;
  double* ptr1 = allocator.allocate(1);
  allocator.deallocate(ptr1);
  double* ptr2 = allocator.allocate(1);

  ASSERT_EQ(ptr1,ptr2);
}
*/
int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
