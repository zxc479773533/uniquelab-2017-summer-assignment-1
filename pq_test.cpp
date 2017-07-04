#include <queue>
#include <random>
#include "include/gtest/gtest.h"

#include "priority_queue.h"

namespace {
  TEST(push, random_large)
  {
    std::random_device rand_dev;

    std::default_random_engine e(810);
    std::uniform_real_distribution<double> dis(0, 100);

    std::priority_queue<double> std_pq;
    Priority_queue pq;

    for (unsigned i = 0; i != 1000000; ++i)
    {
      double num = dis(e);
      std_pq.push(num);
      pq.push(num);
    }

    EXPECT_EQ(std_pq.top(), pq.top());
    EXPECT_EQ(std_pq.size(), pq.size());
  }
  TEST(push,ordered_data)
  {
    std::priority_queue<double> std_pq;
    Priority_queue nonstd_pq;
    for(unsigned int i=0;i<10000;i++){
      std_pq.push((double)i);
      nonstd_pq.push((double)i);
    }
    EXPECT_EQ(std_pq.top(),nonstd_pq.top());
    EXPECT_EQ(std_pq.size(),nonstd_pq.size());
  }
  TEST(push,repeated_data){
    std::priority_queue<double> std_pq;
    Priority_queue nonstd_pq;
    for(unsigned int i=0;i<10000;i++){
      std_pq.push((double)i);
      nonstd_pq.push((double)i);
      std_pq.push(0.0f);
      nonstd_pq.push(0.0f);
      EXPECT_EQ(std_pq.top(),nonstd_pq.top());    
    }
    EXPECT_EQ(std_pq.size(),nonstd_pq.size());
    for(int i=0;i<20000;i++){
      EXPECT_EQ(std_pq.top(),nonstd_pq.top());
      std_pq.pop();
      nonstd_pq.pop();
    }
  }
  TEST(push,crossing_data){
    std::priority_queue<double> std_pq;
    Priority_queue nonstd_pq;
    for(unsigned int i=0;i<10000;i++){
      std_pq.push((double)i);
      nonstd_pq.push((double)i);
      std_pq.push((double)-i);
      nonstd_pq.push((double)-i);
      EXPECT_EQ(std_pq.top(),nonstd_pq.top());
      
    }
    EXPECT_EQ(std_pq.size(),nonstd_pq.size());
    for(int i=0;i<20000;i++){
        EXPECT_EQ(std_pq.top(),nonstd_pq.top());
        std_pq.pop();
        nonstd_pq.pop();
    }
  }
  
}