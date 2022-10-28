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

    virtual void
    SetUp() override
    {
        std::cout << "$$$$ Test" << std::endl;
    }

    static void
    TearDownTestSuite()
    {}
};

TEST_F(SomeTest, Test)
{
    EXPECT_EQ(1, 1);
    for (volatile unsigned i = 0; i < 10000000u; ++i)
    {
        executeSystick();
    }
    EXPECT_EQ(1, 1);
}