#include "gtest/gtest.h"

#include "system.h"


TEST(TestSystem, IsRandom) 
{
  particle_system world(10, 0.0001, 1500, 900);
  for (auto& p : world.get_particles())
  {
    EXPECT_TRUE(p._x <= 1500);
    EXPECT_TRUE(p._x >= 0);
    EXPECT_TRUE(p._y <= 900);
    EXPECT_TRUE(p._y >= 0);
  }
}
