///
/// \file 				StateMachine.c
/// \author 			Geoffrey Hunter (www.mbedded.ninja) <gbmhunter@gmail.com>
/// \edited             n/a
/// \created			2017-04-15
/// \last-modified		2018-03-19
/// \brief 				Contains the StateMachine module.
/// \details
///		See README.md in root dir for more info.

// System includes
#include <stdio.h>

// Local includes
#include "Led.h"
#include "main.h"
#include "StateMachine.h"


typedef struct {
    const char * name;
    void (*func)(void);
} stateFunctionRow_t;


/// \brief  Maps a state to it's state transition function, which should be called
///         when the state transitions into this state.
/// \warning    This has to stay in sync with the state_t enum!
static stateFunctionRow_t stateFunctionA[] = {
      // NAME         // FUNC
    { "ST_GREEN",      &Green_Light    },      // ST_GREEN
    { "ST_YELLOW",     &Yellow_Light   },      // ST_YELLOW
    { "ST_RED",        &Red_Light      },      // ST_RED
};

typedef struct {
    state_t currState;
    event_t event;
    state_t nextState;
} stateTransMatrixRow_t;

static stateTransMatrixRow_t stateTransMatrix[] = {
    // CURR STATE  // EVENT        // NEXT STATE
    { ST_RED,      EV_TIMER_32,    ST_GREEN   },
    { ST_YELLOW,   EV_TIMER_8,     ST_RED     },
    { ST_GREEN,    EV_TIMER_50,    ST_YELLOW  },
};

void StateMachine_Init(stateMachine_t * stateMachine) {
    printf("Initialising state machine.\r\n");
    stateMachine->currState =ST_RED;
}

void StateMachine_RunIteration(stateMachine_t *stateMachine, event_t event) {

    // Iterate through the state transition matrix, checking if there is both a match with the current state
    // and the event
    for(int i = 0; i < sizeof(stateTransMatrix)/sizeof(stateTransMatrix[0]); i++) {
        if(stateTransMatrix[i].currState == stateMachine->currState) {
            if((stateTransMatrix[i].event == event) || (stateTransMatrix[i].event == EV_ANY)) {

                // Transition to the next state
                stateMachine->currState =  stateTransMatrix[i].nextState;

                // Call the function associated with transition
                (stateFunctionA[stateMachine->currState].func)();
                break;
            }
        }
    }
}

const char * StateMachine_GetStateName(state_t state) {
    return stateFunctionA[state].name;
}