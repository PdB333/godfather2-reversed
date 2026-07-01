// Xbox PDB: EARS_Modules_PlayerGenericCSASM_BuildStateMachine
// FUNC_NAME: PlayerGenericCSA::initStateMachine

// Reconstructed C++ for function at 0x007c0060 - Initializes the player generic CSA state machine
// The game uses EA's Character State Architecture (CSA) for animation/behavior state machines.

#include "earscore/CommonCSA.h" // Hypothetical include for CSA utilities

void PlayerGenericCSA::initStateMachine() {
    // Get the state table from the CSA system
    void* stateTable = GenericCSA::getStateTable(); // FUN_009c8f80

    // Register the state table with a unique name
    GenericCSA::registerStateTable("playerGenericCSAStateTable", stateTable); // FUN_004ad9d0

    // Set default transitions (to no target) for the state machine
    GenericCSA::setDefaultTransition(0x00d63420, -1); // FUN_004adae0 - string at 0x00d63420 likely "initial" or similar

    // Define states with their IDs
    GenericCSA::addState("WaitForAuthority", 0x16); // FUN_004acc70
    GenericCSA::addState("Working", 0x14);
    GenericCSA::addState("terminate", 4);
    GenericCSA::addState("terminate", 0x15); // Reuse "terminate" with a different ID? Possibly a transition condition.
    GenericCSA::addState("terminate", 0x19);
    GenericCSA::addState("terminate", 0x1a);
    GenericCSA::addState("Working", 0x18);
    GenericCSA::addState("WaitForAuthority", 0x17);

    // Reset default transition for "WaitForAuthority" (clear previous)
    GenericCSA::setDefaultTransition("WaitForAuthority", -1); // FUN_004adae0

    // Add a transition from state 0x36 (likely "WaitForAuthority"?) to something
    GenericCSA::addTransition(0x36, 0x00); // FUN_004acf70 - exact args unknown, assume from 0x36

    // Add more state definitions (likely conditional transitions)
    GenericCSA::addState("terminate", 0x1b);
    GenericCSA::addState("terminate", 0x16);
    GenericCSA::addState("Success", 0x13);

    // Add an action on state 0x35
    GenericCSA::addAction(0x35); // FUN_004ad070

    // Reset default transition for "Success"
    GenericCSA::setDefaultTransition("Success", -1); // FUN_004adae0

    // Add a transition from state 0x33
    GenericCSA::addTransition(0x33); // FUN_004acf70

    // Add conditions for transitions (0x31, 0x32)
    GenericCSA::addCondition(0x31); // FUN_004acff0
    GenericCSA::addCondition(0x32);

    // Add state "terminate" with condition 3
    GenericCSA::addState("terminate", 3);

    // Set default transition for "terminate" to none
    GenericCSA::setDefaultTransition("terminate", -1); // FUN_004adae0

    // Add a transition from state 2
    GenericCSA::addTransition(2); // FUN_004acf70

    // Register the complete state machine with a debug name and a unique ID
    GenericCSA::registerStateMachine(0xd0a403f5, &LAB_007bfee0, "PlayerGenericCSASM"); // FUN_004adc90

    // Finalize the state machine initialization
    GenericCSA::finalize(); // FUN_004ada40
}