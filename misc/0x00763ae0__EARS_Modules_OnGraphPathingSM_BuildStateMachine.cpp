// Xbox PDB: EARS::Modules::OnGraphPathingSM::BuildStateMachine
// FUNC_NAME: setupOnGraphPathingStateMachine

// Function: 0x00763ae0
// Purpose: Builds the hierarchical state machine for OnGraphPathing behavior (AI patrolling graph).
// This function registers states, transitions, and sub-state machines (ST = state table, SM = state machine).
void setupOnGraphPathingStateMachine()
{
    // Get a unique state machine identifier (likely from a factory)
    uint stateMachineID = getStateMachineID(); // FUN_009c8f80

    // Register a new state table (ST) named "OnGraphPathingST"
    addStateTable("OnGraphPathingST", stateMachineID); // FUN_004ad9d0

    // Create an initial state "initPatrol" with invalid state index (-1) meaning root or default
    addState("initPatrol", 0xFFFFFFFFU); // FUN_004adae0

    // Add several child states by their integer IDs (likely enum values)
    addState(0x11); // FUN_004acf70 - state 17
    addState(0x0C); // state 12
    addState(0x0D); // state 13
    addState(0x0E); // state 14
    addState(0x10); // state 16

    // Add a transition from "patrolGraph" to state 4 (maybe a sub-state machine)
    addTransition("patrolGraph", 4); // FUN_004acc70

    // Register a state "patrolGraph" with invalid index (full tree)
    addState("patrolGraph", 0xFFFFFFFFU); // FUN_004adae0

    // Add more states to the patrol graph
    addState(0x0D); // state 13 (again)
    addState(0x08); // state 8

    // Add sub-state machines or default states (maybe with flags)
    addSubStateMachine(0x10); // FUN_004acff0 - state 16
    addSubStateMachine(0x0E); // state 14
    addSubStateMachine(0x08); // state 8

    // Define transitions for leaf states
    addTransition("terminate", 0x0D); // FUN_004acc70 - state 13 leads to terminate state
    addTransition("specialNode", 0x0E); // state 14 leads to special node

    // Register the "specialNode" state
    addState("specialNode", 0xFFFFFFFFU); // FUN_004adae0

    // Add a sub-state machine "SpecialMotionST" as initial state 1
    addSubStateMachineWithInitial("SpecialMotionST", 1); // FUN_004acf10

    // Add transition from "patrolGraph" to state 1 (perhaps the SpecialMotionST entry)
    addTransition("patrolGraph", 1); // FUN_004acc70

    // Set terminal state (maybe a default end) for state 0x0F (15)
    setTerminalState(0x0F); // FUN_004ad070

    // Add the "terminate" state with invalid index
    addState("terminate", 0xFFFFFFFFU); // FUN_004adae0

    // Add final states for cleanup
    addState(0x12); // state 18
    addState(0x02); // state 2

    // Link the state machine to a specific graph pathing behavior (using hash ID and label as callback)
    // 0x6B4FE568 is likely a unique identifier for this state machine type
    // &LAB_00763a90 points to a transition handler function (probably "onGraphPathingCallback")
    linkStateMachineToBehavior(0x6B4FE568, &onGraphPathingCallback, "OnGraphPathingSM"); // FUN_004adc90

    // Finalize and lock the state machine (prevent further edits)
    finalizeStateMachine(); // FUN_004ada40

    return;
}