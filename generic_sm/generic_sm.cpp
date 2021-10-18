/*
 * Generic State Machine
 * Implementation of a dynamic and flexible state machine design
 *
 */

#include <cstdint>
#include <iostream>
#include "generic_sm.h"

namespace {

typedef struct _state_table_t_
{
    int (*fcnPtrEntry)(generic_sm_t &){ nullptr };
    int (*fcnPtrProcess)(generic_sm_t &){ nullptr };
    int (*fcnPtrExit)(generic_sm_t &){ nullptr };
    int (*fcnPtrEvents)(generic_sm_t &){ nullptr };
} state_table_t;

typedef struct _event_table_t_
{
    states_e noEventNextState;
    states_e eventANextState;
    states_e eventBNextState;
} event_table_t;

// Complete event table to match sm.puml
constexpr event_table_t eventTable[max_states]
{
    // State        // No Event // Event A  // Event B
    {/* State0 */   state0,     state1,     state0, },
    {/* State1 */   state1,     state0,     state2, },
    {/* State2 */   state0,     state2,     state2, },
};

// Implementation-specific code
// ****************************
// Entry
int state0_entry(generic_sm_t &sm)
{
    std::cout << __func__ << std::endl;
    return 0;
}
int state1_entry(generic_sm_t &sm)
{
    std::cout << __func__ << std::endl;
    return 0;
}
int state2_entry(generic_sm_t &sm)
{
    std::cout << __func__ << std::endl;
    return 0;
}

// Process
int state0_process(generic_sm_t &sm)
{
    std::cout << __func__ << std::endl;
    return 0;
}
int state1_process(generic_sm_t &sm)
{
    std::cout << __func__ << std::endl;
    return 0;
}
int state2_process(generic_sm_t &sm)
{
    std::cout << __func__ << std::endl;
    return 0;
}

// Exit
int state0_exit(generic_sm_t &sm)
{
    std::cout << __func__ << std::endl;
    return 0;
}
int state1_exit(generic_sm_t &sm)
{
    std::cout << __func__ << std::endl;
    return 0;
}
int state2_exit(generic_sm_t &sm)
{
    std::cout << __func__ << std::endl;
    return 0;
}

// Event
int generic_event(generic_sm_t &sm)
{
    std::cout << __func__ << std::endl;

    if (sm.pendingEventBitmap & (1<<eventA) & ~(sm.maskedEventBitmap))
    {
        sm.nextState = eventTable[sm.currentState].eventANextState;
        clearEvent(sm, eventA, false);
    }
    else if (sm.pendingEventBitmap & (1<<eventB) & ~(sm.maskedEventBitmap))
    {
        sm.nextState = eventTable[sm.currentState].eventBNextState;
        clearEvent(sm, eventB, false);
    }
    else
    {
        // no event
        sm.nextState = eventTable[sm.currentState].noEventNextState;
    }

    return 0;
}
// state-specific handlers if needed
//int state0_event(generic_sm_t &sm)
//{
//    std::cout << __func__ << std::endl;
//    sm.nextState = eventTable[sm.currentState].noEventNextState;
//    return 0;
//}
//int state1_event(generic_sm_t &sm)
//{
//    std::cout << __func__ << std::endl;
//    sm.nextState = eventTable[sm.currentState].noEventNextState;
//    return 0;
//}
//int state2_event(generic_sm_t &sm)
//{
//    std::cout << __func__ << std::endl;
//    sm.nextState = eventTable[sm.currentState].noEventNextState;
//    return 0;
//}
// ****************************

constexpr state_table_t stateTable[max_states]
{
    // State        // entry        // current          // exit         // event
    {/* State0 */   &state0_entry,  &state0_process,    &state0_exit,   &generic_event },
    {/* State1 */   &state1_entry,  &state1_process,    &state1_exit,   &generic_event },
    {/* State1 */   &state2_entry,  &state2_process,    &state2_exit,   &generic_event },
};

}

// Implementation-specific code
// ****************************
// Event Handlers
int handlerEventA(generic_sm_t &sm)
{
    // set bitmap for this event
    sm.pendingEventBitmap |= (1<<eventA);
    std::cout << __func__ << ": " << sm.pendingEventBitmap << std::endl;
    return 0;
}

int handlerEventB(generic_sm_t &sm)
{
    // set bitmap for this event
    sm.pendingEventBitmap |= (1<<eventB);
    std::cout << __func__ << ": " << sm.pendingEventBitmap << std::endl;
    return 0;
}

int clearEvent(generic_sm_t &sm, events_e evt, bool clearAll)
{
    if (clearAll)
    {
        sm.pendingEventBitmap = 0;
    }
    else
    {
        sm.pendingEventBitmap &= ~(1<<evt);
    }
    std::cout << __func__ << ": " << sm.pendingEventBitmap << std::endl;
    return 0;
}
// ****************************

int initalizeStateMachine(generic_sm_t &sm)
{
    sm.currentState = state0;
    sm.nextState = state0;
    sm.pendingEventBitmap = 0;
    sm.maskedEventBitmap = 0;
    return 0;
}

int processState(generic_sm_t &sm)
{
    // check if entry needed
    if (sm.currentState != sm.nextState)
    {
        // run next state entry function
        stateTable[sm.nextState].fcnPtrEntry(sm);
    }
    // after running entry function, set current state
    sm.currentState = sm.nextState;
    // check events
    stateTable[sm.currentState].fcnPtrEvents(sm);
    // process current state
    stateTable[sm.currentState].fcnPtrProcess(sm);
    // check if exit needed
    if (sm.currentState != sm.nextState)
    {
        stateTable[sm.currentState].fcnPtrExit(sm);
    }
    std::cout << "Current State: " << sm.currentState << std::endl;
    std::cout << "Next State: " << sm.nextState << std::endl;
    std::cout << "Pending event bitmap: " << sm.pendingEventBitmap << std::endl;
    std::cout << "Masked event bitmap: " << sm.maskedEventBitmap << std::endl;
    return 0;
}