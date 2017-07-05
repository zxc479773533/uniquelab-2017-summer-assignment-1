#include <set>
#include <random>
#include "include/gtest/gtest.h"

#include "set.h"

namespace {
  TEST(push, random_large)
  {

    std::default_random_engine e(810);
    std::uniform_real_distribution<double> dis(0, 100);

    std::set<double> std_set;
    Set custom_set;

    for (unsigned i = 0; i != 10000; ++i)
    {
      double num = dis(e);
      std_set.insert(num);
      custom_set.insert(num);
    }

    EXPECT_EQ(std_set.size(), custom_set.size());
  }
}