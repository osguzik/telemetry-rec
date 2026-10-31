#include "RingBuffer.h"

#include <cstdint>

#include <gtest/gtest.h>

TEST(RingBufferTest, StartsEmpty) {
  RingBuffer<uint32_t, 16> buffer;
  EXPECT_TRUE(buffer.empty());
}

TEST(RingBufferTest, LastAfterWrap) {
  RingBuffer<uint32_t, 10> buffer;
  for (uint32_t i = 1; i <= 10; i++) {
    buffer.put(i);
  }
  EXPECT_EQ(buffer.last(), 10);
}
