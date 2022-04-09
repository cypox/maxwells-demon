#include "gtest/gtest.h"

#include "system.h"


TEST(TestSystem, ParticlesInRange) 
{
  particle_system world(1000, 0.0001, 10, 10);
  for (auto& p : world.get_particles())
  {
    EXPECT_TRUE(p._x <= 10);
    EXPECT_TRUE(p._x >= 0);
    EXPECT_TRUE(p._y <= 10);
    EXPECT_TRUE(p._y >= 0);
  }
}

TEST(TestSystem, Distance)
{
  EXPECT_DOUBLE_EQ(distance(0., 0., 1., 1.), std::sqrt(2));
  EXPECT_DOUBLE_EQ(distance(-1., -1., 1., 1.), 2.*std::sqrt(2));
}

TEST(TestSystem, Step)
{
  particle_system world(2, 0.1, 10, 10);
}
