// Xbox PDB: EARS_Modules_PlayerF2FSM_BuildStateMachine
// FUNC_NAME: PlayerF2FSM::initStateTable
// Address: 0x007cf5b0
// Role: Builds and registers the player's face-to-face (F2F) state machine table
// This function initializes the F2F state machine with all states, transitions,
// and events used for the player's face-to-face interactions (e.g., dialogue, shopping, combat).

// Includes for state machine framework (hypothetical)
#include "StateMachineBuilder.h"

// Global condition variables / flags used in conditional transitions
extern int g_playerF2FCondition1; // DAT_00d5842c
extern int g_playerF2FCondition2; // DAT_00d5ddec
extern int g_playerF2FCondition3; // DAT_00d5eee4
extern int g_playerF2FCondition4; // DAT_00d5779c
extern int g_playerF2FCondition5; // DAT_00e448a4

void PlayerF2FSM::initStateTable()
{
    // Get or create the F2F state table
    void* stateTable = StateMachineBuilder::findTable("playerF2FStateTable");
    if (stateTable == nullptr) {
        // Create new state table
        stateTable = StateMachineBuilder::createTable();
        StateMachineBuilder::setTableName(stateTable, "playerF2FStateTable");

        // ----- State definitions (state name, state ID) -----
        // IDs: 0x31=49, 0x32=50, 0x33=51, 0x34=52, 0x35=53, 0x36=54,
        //       0x37=55, 0x38=56, 0x39=57, 0x3d=61, 0x3e=62, 0x3f=63, etc.
        StateMachineBuilder::addState(stateTable, "Inactive", 0xffffffff); // initial? ID = -1
        StateMachineBuilder::addTransition(stateTable, 0x31);             // event 0x31
        StateMachineBuilder::addState(stateTable, "Valid", 0x24);        // state 0x24
        StateMachineBuilder::addTransition(stateTable, 0x32);            // event 0x32
        StateMachineBuilder::addState(stateTable, "F2FEnd", 0xffffffff); // ID -1
        StateMachineBuilder::addTransition(stateTable, 0x46);            // event 0x46
        StateMachineBuilder::addState(stateTable, "Inactive", 4);        // state 4? maybe duplicate?
        StateMachineBuilder::addState(stateTable, "Valid", 0xffffffff);  // ID -1
        StateMachineBuilder::addTransition(stateTable, 0x33);            // event 0x33
        StateMachineBuilder::addState(stateTable, "F2FEnd", 0x14);       // state 0x14
        StateMachineBuilder::addState(stateTable, "F2FWaitingForLoad", 0x18); // 0x18
        StateMachineBuilder::addConditionalTransition(stateTable, "F2FEnd", 2, g_playerF2FCondition1, 1);
        StateMachineBuilder::addTransition(stateTable, 0x34);            // event 0x34
        StateMachineBuilder::addState(stateTable, "F2FActivate", 0xffffffff);
        StateMachineBuilder::addTransition(stateTable, 0x37);            // event 0x37
        StateMachineBuilder::addTransition(stateTable, 0x40);            // event 0x40
        StateMachineBuilder::addStateCondition(stateTable, 0x45);        // condition 0x45
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x13); // state 0x13
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x2b); // state 0x2b
        StateMachineBuilder::addState(stateTable, "F2FShopping", 0x25);  // 0x25
        StateMachineBuilder::addState(stateTable, "F2FVoiceover", 0x1d); // 0x1d
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x21); // 0x21
        StateMachineBuilder::addState(stateTable, "F2FIdleUserInput", 0x1a);
        StateMachineBuilder::addState(stateTable, "F2FIdleUserInputWithCountdownTimer", 0x1b);
        StateMachineBuilder::addState(stateTable, "F2FGetNextNode", 4);
        StateMachineBuilder::addTransition(stateTable, 0x38);
        StateMachineBuilder::addState(stateTable, "F2FWaitingForLoad", 0xffffffff);
        StateMachineBuilder::addTransition(stateTable, 0x35);
        StateMachineBuilder::addStateCondition(stateTable, 0x45);
        StateMachineBuilder::addState(stateTable, "F2FEnd", 0x14);
        StateMachineBuilder::addState(stateTable, "F2FWaitForSwing", 0x23);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x2c);
        StateMachineBuilder::addConditionalTransition(stateTable, "F2FDeactivate", 2, g_playerF2FCondition2, 1);
        StateMachineBuilder::addTransition(stateTable, 0x36);
        StateMachineBuilder::addState(stateTable, "F2FWaitForSwing", 0xffffffff);
        StateMachineBuilder::addStateCondition(stateTable, 0x45);
        StateMachineBuilder::addConditionalTransition(stateTable, "F2FDeactivate", 2, g_playerF2FCondition3, 1);
        StateMachineBuilder::addState(stateTable, "F2FActivate", 0x15);
        StateMachineBuilder::addState(stateTable, "F2FConcealWeapon", 0x16);
        StateMachineBuilder::addState(stateTable, "F2FEnd", 0x13);
        StateMachineBuilder::addState(stateTable, "F2FConcealWeapon", 0xffffffff);
        StateMachineBuilder::addSubStateTable(stateTable, "playerConcealItemStateTable", 1); // sub table
        StateMachineBuilder::addStateCondition(stateTable, 0x45);
        StateMachineBuilder::addState(stateTable, "F2FActivate", 1);
        StateMachineBuilder::addState(stateTable, "F2FEnd", 0x13);
        StateMachineBuilder::addConditionalTransition(stateTable, "F2FDeactivate", 2, g_playerF2FCondition4, 1);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0xffffffff);
        StateMachineBuilder::addTransition(stateTable, 0x39);
        StateMachineBuilder::addState(stateTable, "F2FEnd", 4);
        StateMachineBuilder::addState(stateTable, "F2FIdleUserInput", 0xffffffff);
        StateMachineBuilder::addTransition(stateTable, 0x3d);   // 61
        StateMachineBuilder::addTransition(stateTable, 0x40);
        StateMachineBuilder::addStateCondition(stateTable, 0x45);
        StateMachineBuilder::addStateCondition(stateTable, 0x44);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x13);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x2b);
        StateMachineBuilder::addState(stateTable, "F2FEvaluateNextNode", 0x1e);
        StateMachineBuilder::addTransition(stateTable, 0x48);   // 72
        StateMachineBuilder::addState(stateTable, "F2FIdleUserInputWithCountdownTimer", 0xffffffff);
        StateMachineBuilder::addTransition(stateTable, 0x3e);   // 62
        StateMachineBuilder::addTransition(stateTable, 0x40);
        StateMachineBuilder::addStateCondition(stateTable, 0x45);
        StateMachineBuilder::addStateCondition(stateTable, 0x44);
        StateMachineBuilder::addStateCondition(stateTable, 0x3f); // 63
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x13);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x2b);
        StateMachineBuilder::addState(stateTable, "F2FEvaluateNextNode", 0x1e);
        StateMachineBuilder::addState(stateTable, "F2FEvaluateNextNode", 0x1c);
        StateMachineBuilder::addTransition(stateTable, 0x48);
        StateMachineBuilder::addState(stateTable, "F2FIdleCityTravel", 0xffffffff);
        StateMachineBuilder::addTransition(stateTable, 0x4d);   // 77
        StateMachineBuilder::addTransition(stateTable, 0x40);
        StateMachineBuilder::addStateCondition(stateTable, 0x45);
        StateMachineBuilder::addStateCondition(stateTable, 0x44);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x13);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x2b);
        StateMachineBuilder::addState(stateTable, "F2FMoreCities", 0x30);
        StateMachineBuilder::addState(stateTable, "F2FEvaluateNextNode", 0x2f);
        StateMachineBuilder::addTransition(stateTable, 0x48);
        StateMachineBuilder::addState(stateTable, "F2FMoreCities", 0xffffffff);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x13);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x2b);
        StateMachineBuilder::addState(stateTable, "F2FIdleCityTravel", 4);
        StateMachineBuilder::addState(stateTable, "F2FGetNextNode", 0xffffffff);
        StateMachineBuilder::addTransition(stateTable, 0x42);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x13);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x2b);
        StateMachineBuilder::addState(stateTable, "F2FEvaluateNextNode", 3);
        StateMachineBuilder::addState(stateTable, "F2FEvaluateNextNode", 0xffffffff);
        StateMachineBuilder::addTransition(stateTable, 0x43);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x13);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x2b);
        StateMachineBuilder::addState(stateTable, "F2FShopping", 0x25);
        StateMachineBuilder::addState(stateTable, "F2FVoiceover", 0x1d);
        StateMachineBuilder::addState(stateTable, "F2FIdleCityTravel", 0x2e);
        StateMachineBuilder::addState(stateTable, "F2FIdleUserInput", 0x1a);
        StateMachineBuilder::addState(stateTable, "F2FIdleUserInputWithCountdownTimer", 0x1b);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x21);
        StateMachineBuilder::addState(stateTable, "F2FVoiceover", 0xffffffff);
        StateMachineBuilder::addTransition(stateTable, 0x41);
        StateMachineBuilder::addTransition(stateTable, 0x40);
        StateMachineBuilder::addStateCondition(stateTable, 0x45);
        StateMachineBuilder::addStateCondition(stateTable, 0x44);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x13);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x2b);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x31);
        StateMachineBuilder::addState(stateTable, "F2FGetNextNode", 0x20);
        StateMachineBuilder::addState(stateTable, "F2FGetNextNode", 0x19);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x17);
        StateMachineBuilder::addState(stateTable, "F2FVoiceover", 0x2d);
        StateMachineBuilder::addState(stateTable, "F2FEnd", 0x22);
        StateMachineBuilder::addState(stateTable, "F2FShopping", 0xffffffff);
        StateMachineBuilder::addTransition(stateTable, 0x47);
        StateMachineBuilder::addTransition(stateTable, 0x40);
        StateMachineBuilder::addStateCondition(stateTable, 0x45);
        StateMachineBuilder::addStateCondition(stateTable, 0x44);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x13);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x2b);
        StateMachineBuilder::addConditionalTransition(stateTable, "F2FShopping", 2, g_playerF2FCondition5, 1);
        StateMachineBuilder::addState(stateTable, "F2FDeactivate", 0x17);

        // Register the state machine with a hash and a debug label
        StateMachineBuilder::registerMachine(stateTable, 0xb47bb605, &F2FStateMachineCallback, "PlayerF2FSM");
        StateMachineBuilder::finalizeTable(stateTable);
    }
}