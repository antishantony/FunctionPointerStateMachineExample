///
/// \file 				main.c
/// \author 			Geoffrey Hunter (www.mbedded.ninja) <gbmhunter@gmail.com>
/// \edited             n/a
/// \created			2017-04-15
/// \last-modified		2018-03-19
/// \brief 				Contains the main entry point to the state machine example.
/// \details
///		See README.md in root dir for more info.

/* Modelling a Traffic light State machine

State	Input	    Next state	    Output
Green	Timer 50s	Yellow	        Green light on, others off
Yellow	Timer 8s	Red	            Yellow light on, others off
Red	    Timer 32s	Green	        Red light on, others off

*/
#include <stdio.h>
#include <stdbool.h>

#include "StateMachine.h"

int main() {
    printf("main() called.\r\n");

    // Create new state machine object
    stateMachine_t stateMachine;

    StateMachine_Init(&stateMachine);
    printf("State is now in default RED Light %s.\r\n", StateMachine_GetStateName(stateMachine.currState));

    printf("32 Sec Time Out.\r\n");
    StateMachine_RunIteration(&stateMachine, EV_TIMER_32);
    printf("State is now %s.\r\n", StateMachine_GetStateName(stateMachine.currState));

    // Timeout
    printf("50 Sec Time Out.\r\n");
    StateMachine_RunIteration(&stateMachine, EV_TIMER_50);
    printf("State is now %s.\r\n", StateMachine_GetStateName(stateMachine.currState));

    // Timeout
    printf("8 Sec Time Out.\r\n");
    StateMachine_RunIteration(&stateMachine, EV_TIMER_8);
    printf("State is now %s.\r\n", StateMachine_GetStateName(stateMachine.currState));

    printf("32 Sec Time Out.\r\n");
    StateMachine_RunIteration(&stateMachine, EV_TIMER_32);
    printf("State is now %s.\r\n", StateMachine_GetStateName(stateMachine.currState));

    return 0;
}