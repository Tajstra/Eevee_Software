#include "simulated_integration_test.h"

ApplicationSoftware app_software {};

int
main()
{
    testing::InitGoogleTest();

    app_software.initialize();
    unsigned result = RUN_ALL_TESTS();

    return result;
}
