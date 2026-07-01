// Xbox PDB: EARS_Modules_NPCWitnessIdleSM_BuildStateMachine
// FUNC_NAME: NPCWitnessIdleSM::setup
// Address: 0x007760d0
// Role: Constructs the NPC witness idle state machine with states, transitions, and condition table references.

void NPCWitnessIdleSM::setup(void) {
    // Allocate state machine handle and set its name
    uint32_t smHandle = StateMachine::allocate(); // +0x00: handle/ID
    StateMachine::setName("NPCWitnessIdleST", smHandle); // +0x04: name string

    // Initialize global variable (likely state machine context) to 0
    StateMachine::setVariable(&DAT_00d63420, 0); // DAT_00d63420: global context object

    // Add states with IDs
    StateMachine::addState("terminate", 10);          // state ID 10
    StateMachine::addState("canSeeCriminal", 11);     // state ID 11
    StateMachine::addState("witnessWait", 4);         // state ID 4

    // Set transition condition variable? (canSeeCriminal = 1)
    StateMachine::setVariable("canSeeCriminal", 1);

    // Setup state entry actions? (IDs: 10, 8)
    StateMachine::setStateEntryAction(10);
    StateMachine::setStateEntryAction(8);
    StateMachine::setStateExitAction(8); // +0x08? similar pattern

    // Add transition table for seeking target
    StateMachine::addTransitionTable("seekTargetTable", 1);

    // Add more states
    StateMachine::addState("witnessWait", 12);         // state ID 12
    StateMachine::addState("terminate", 10);           // duplicate? maybe transition target

    // Change condition variable
    StateMachine::setVariable("witnessWait", 2);

    // Add a transition with condition hash, from state 1 to state 1? (unclear)
    // Parameters: conditionHash, fromState, toState, unknown, priority(float)
    StateMachine::addTransition(0xc3a0619b, 1, 1, 0, 1.0f); // hash likely "witnessWaitComplete"

    // Add another transition table
    StateMachine::addTransitionTable("seekToPositionTerminateTable", 1);

    // Set state entry/exit actions again
    StateMachine::setStateEntryAction(8);
    StateMachine::setStateExitAction(8);

    // Change terminate condition to -1 (infinite?)
    StateMachine::setVariable("terminate", 0xFFFFFFFF);

    // Set state entry action for state 2
    StateMachine::setStateEntryAction(2);

    // Add transition with hash to external function label and table name
    StateMachine::addTransition(0xd2a854c6, &LAB_007760a0, "NPCWitnessIdleSM"); // hash likely "witnessIdleComplete"
    // Note: LAB_007760a0 is a code pointer for the transition's target state handler? Possibly a function pointer.

    // Finalize state machine construction
    StateMachine::finalize();
}