// FUNC_NAME: CombatPathStateMachine::init
void CombatPathStateMachine::init(void)
{
    // Get a unique state machine ID (likely from a manager)
    int stateMachineID = getStateMachineID();

    // Register the state machine with a name ("CombatPathST" is the initial state name?)
    registerStateMachine("CombatPathST", stateMachineID);

    // Set up the initial state "CombatPathST" with no transition (0)
    setStateTransition(&s_combatPathST, 0);

    // Add states with their IDs
    addState("strafeAttackPathing", 10);
    addState(&s_strafeAttackPathing, 0xC); // &DAT_00d65648 is a global string constant
    addState("smoothPathing", 4);

    // Add a transition from "strafeAttackPathing" to state ID 1
    setStateTransition("strafeAttackPathing", 1);

    // Set default state ID to 0xB (11)
    setDefaultState(0xB);

    // Set state flags (maybe enable/disable)
    setStateFlag(10);  // Enable state 10
    setStateFlag(0xB); // Enable state 11

    // Add a transition from "FollowPathST" to state ID 1
    addStateTransition("FollowPathST", 1);

    // Add state "terminate" with ID 0xB
    addState("terminate", 0xB);

    // Set a transition for &s_strafeAttackPathing to state ID 2
    setStateTransition(&s_strafeAttackPathing, 2);

    // Add another transition from "FollowPathST" to state ID 1 (duplicate?)
    addStateTransition("FollowPathST", 1);

    // Add state "strafeAttackPathing" with ID 10 again (maybe re-add with different role?)
    addState("strafeAttackPathing", 10);

    // Add state "terminate" with ID 1
    addState("terminate", 1);

    // Set transition for "smoothPathing" to state ID 3
    setStateTransition("smoothPathing", 3);

    // Add transition from "SmootherPathST" to state ID 1
    addStateTransition("SmootherPathST", 1);

    // Add state &s_strafeAttackPathing with ID 0xC again
    addState(&s_strafeAttackPathing, 0xC);

    // Add state "strafeAttackPathing" with ID 10 again
    addState("strafeAttackPathing", 10);

    // Add state "terminate" with ID 1
    addState("terminate", 1);

    // Set transition for "terminate" to state ID 4
    setStateTransition("terminate", 4);

    // Set default state to ID 2
    setDefaultState(2);

    // Register the state machine instance with a hash, callback, and name
    registerStateMachineInstance(0x6D994273, &stateUpdateCallback, "CombatPathSM");

    // Finalize state machine registration
    finalizeStateMachineRegistration();
}