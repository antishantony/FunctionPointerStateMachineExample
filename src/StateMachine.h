///
/// \file 				StateMachine.h
/// \author 			Geoffrey Hunter (www.mbedded.ninja) <gbmhunter@gmail.com>
/// \edited             n/a
/// \created			2017-04-15
/// \last-modified		2018-03-19
/// \brief 				Contains the StateMachine module.
/// \details
///		See README.md in root dir for more info.

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum {
    ST_GREEN,
    ST_YELLOW,
    ST_RED
} state_t;

typedef struct {
    state_t currState;
} stateMachine_t;

/// \brief      All the possible events that can occur for this state machine.
/// \details    Unlike states_t, these do not need to be kept in a special order.
typedef enum {
    EV_ANY,
    EV_NONE,
    EV_TIMER_50,
    EV_TIMER_8,
    EV_TIMER_32
} event_t;

void StateMachine_Init(stateMachine_t * stateMachine);
void StateMachine_RunIteration(stateMachine_t *stateMachine, event_t event);
const char * StateMachine_GetStateName(state_t state);

#endif