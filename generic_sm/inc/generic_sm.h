/*
 * Generic State Machine
 */

// enum
enum states_e {
    state0,
    state1,
    state2,
    max_states
};

enum events_e {
    noEvent,
    eventA,
    eventB,
    max_events
};

// typedefs
// State variable
typedef struct _generic_sm_t_
{
    /* data */
    states_e currentState;
    states_e nextState;
    uint32_t pendingEventBitmap;
    uint32_t maskedEventBitmap;
} generic_sm_t;

// prototypes
int initalizeStateMachine(generic_sm_t &sm);
int processState(generic_sm_t &sm);
int handlerEventA(generic_sm_t &sm);
int handlerEventB(generic_sm_t &sm);
int clearEvent(generic_sm_t &sm, events_e evt, bool clearAll);