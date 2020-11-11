#include <list>
#include <gtest/gtest.h>
#include "allocator/otusAllocator.hpp"
#include "sList/simpleList.hpp"

using namespace std;
using namespace slist;
using namespace simple_allocator;

TEST(allocator, overflow) {
  list<double,Light_Pool_Allocator<double,24>> list;
  ASSERT_NO_THROW(list.push_back(0));
  ASSERT_NO_THROW(list.push_back(0));
}


TEST(allocator, equal) {
   list<double,Light_Pool_Allocator<double,216>> list1;
   ASSERT_NO_THROW(list1.push_back(0));
   ASSERT_NO_THROW(list1.push_back(0));

   list<double,Light_Pool_Allocator<double,216>> list2(list1);

  ASSERT_EQ(list1, list2);
}

TEST(allocator, compare) {

  list<double,Light_Pool_Allocator<double,24>> list1;
  list<double,Light_Pool_Allocator<double,24>> list2;

  ASSERT_NE(list1.get_allocator(), list2.get_allocator());
}


/*TEST(container, __GLIBC_USE_DEPRECATED_GETS) {
  otus::Container<int> c;
  c.push_back(1);
  c.push_back(2);

  EXPECT_EQ(c[0], 1);
  EXPECT_EQ(c[1], 2);

  c[0] = 3;

  EXPECT_EQ(c[0], 3);
}
*/
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}