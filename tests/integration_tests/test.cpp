#include "simulated_integration_test.h"
#include <iostream>
#include <ctime>
// TODO: Delete from here (provide a better interface)

class SomeTest : public SimulatedIntegrationTest
{
protected:
  // Tears down the stuff shared by all tests in this test suite.
  //
  // Google Test will call Foo::TearDownTestSuite() after running the last
  // test in test suite Foo.  Hence a sub-class can define its own
  // TearDownTestSuite() method to shadow the one defined in the super
  // class.

  virtual void SetUp() override
  {
    std::cout << "$$$$ Test" << std::endl;
  }

  static void TearDownTestSuite()
  {
  }
};

TEST_F(SomeTest, Test)
{
  EXPECT_EQ(1, 1);
  appSoftware().print();

  float sim_time_start = std::clock();

  bool prev = false;
  // while((std::clock() - sim_time_start) < 10000)
  {
    // if(prev != static_cast<bool>(GPIOD->ODR & GPIO_PIN_12))
    // {
    //   std::cout << "GPIO toogled!\n";
    //   prev = (GPIOD->ODR & GPIO_PIN_12);
    // }
  }

  // while((GPIOD->ODR & GPIO_PIN_12))
  // {
  //   std::cout << "Simulation time: " << (std::clock() - sim_time_start) / CLOCKS_PER_SEC  << std::endl;
  // }

  // EXPECT_FALSE(GPIOD->ODR & GPIO_PIN_12);

  // while(!(GPIOD->ODR & GPIO_PIN_12))
  // {
  //   std::cout << "Simulation time: " << (std::clock() - sim_time_start) / CLOCKS_PER_SEC  << std::endl;
  // }

  // EXPECT_FALSE(GPIOD->ODR & GPIO_PIN_12);
}