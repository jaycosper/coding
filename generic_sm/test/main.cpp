/*
 * Main function for Lamda Averager
 *
 */

#include <cstdint>
#include <assert.h>
#include "generic_sm.h"

static bool testRunning = true;

int main(void)
{
    generic_sm_t sm;

    int retval = initalizeStateMachine(sm);
    assert(retval == 0);

    int iterations = 5;
    while (testRunning)
    {

        retval = processState(sm);
        assert(retval == 0);

        if (sm.currentState == state0 && sm.nextState == state0) retval = handlerEventA(sm);
        if (sm.currentState == state1 && sm.nextState == state1) retval = handlerEventB(sm);

        if (iterations-- == 0) testRunning = false;
    }

    return retval; // Ctest uses return 0 for pass
}
