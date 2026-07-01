// FUNC_NAME: NPCIntimidateSM::initialize
// Address: 0x007481d0
// This function initializes the NPC intimidation state machine (state machine name: "NPCIntimidateST").
// It defines states, transitions, and substate machines for the Godfather 2 NPC intimidation behavior.

void NPCIntimidateSM::initialize() {
    // Get some identifier (e.g., a memory block ID) from the state machine system.
    int smId = stateMachineAllocateId();

    // Create the top-level state machine named "NPCIntimidateST" with the allocated ID.
    stateMachineCreate("NPCIntimidateST", smId);

    // Set a default transition from a global/generic state (DAT_00d63420) to 0xFFFFFFFF (likely "no state" or "any state"?).
    stateMachineSetTransition(&DAT_00d63420, 0xFFFFFFFF);

    // Add states to the state machine (IDs: 10, 14, 12, 13, etc.).
    // These likely correspond to intimidation phases: e.g., 10 = "approach", 14 = "taunt", 12 = "fail", 13 = "success".
    stateMachineAddState(&DAT_00d63afc, 10);
    stateMachineAddState(&DAT_00d63afc, 14);       // 0xE
    stateMachineAddState("intimidateFailure", 13); // 0xD
    stateMachineAddState("intimidateFailure", 12); // 0xC
    stateMachineAddState("moveToTarget", 4);

    // Set a transition for "moveToTarget" state to 0xFFFFFFFF (e.g., exit or default).
    stateMachineSetTransition("moveToTarget", 0xFFFFFFFF);

    // Add a transition: from state 3 → state 0x20 (32) with condition 1.
    // State 0x20 might be an "attack" or "stop" state.
    stateMachineAddTransition(3, 0x20, 1);

    // Push another state machine "NPCChaseST" as a substate (flag 1).
    stateMachinePushSubstate("NPCChaseST", 1);

    // Add another state to "intimidateFailure" and a transition from state 6 to 0x20.
    stateMachineAddState("intimidateFailure", 13); // 0xD
    stateMachineAddTransition("intimidateFailure", 6, 0x20, 1);

    // Re-add states to the global container (DAT_00d63afc) for the main intimidation sequence.
    stateMachineAddState(&DAT_00d63afc, 10);
    stateMachineAddState(&DAT_00d63afc, 14);
    stateMachineAddState(&DAT_00d63afc, 12);
    stateMachineAddState("preIntimidate", 11); // 0xB
    stateMachineAddState(&DAT_00d63afc, 1);

    // Add transition from state 4 to 0x20.
    stateMachineAddTransition(4, 0x20, 1);

    // Set transition for "preIntimidate" to default.
    stateMachineSetTransition("preIntimidate", 0xFFFFFFFF);

    // Add state "intimidate" with ID 11 and state ID 1.
    stateMachineAddState(&DAT_00d63afc, 12); // 0xC
    stateMachineAddState("intimidate", 11);  // 0xB
    stateMachineAddState(&DAT_00d63afc, 1);

    // Set transition for "intimidate" to default.
    stateMachineSetTransition("intimidate", 0xFFFFFFFF);

    // Set initial state to 10.
    stateMachineSetInitialState(10);

    // Push "seekTargetTable" substate machine.
    stateMachinePushSubstate("seekTargetTable", 1);

    // Add state 11 (0xB) with some property (likely an "on-enter" action?).
    stateMachineAddStateWithProperty(11); // 0xB

    // Re-add states 10 and 14 to global container.
    stateMachineAddState(&DAT_00d63afc, 10);
    stateMachineAddState(&DAT_00d63afc, 14);

    // Add state 12 (0xC) with another property.
    stateMachineAddStateWithProperty(12); // 0xC

    // Set transition for "intimidateFailure" to default.
    stateMachineSetTransition("intimidateFailure", 0xFFFFFFFF);

    // Set initial state to 13 (0xD).
    stateMachineSetInitialState(13); // 0xD

    // Add state 4 to global container.
    stateMachineAddState(&DAT_00d63afc, 4);

    // Set transition for global container to default.
    stateMachineSetTransition(&DAT_00d63afc, 0xFFFFFFFF);

    // Set initial state to 2.
    stateMachineSetInitialState(2);

    // Register the update function for this state machine.
    // Float 0x40a5817f ≈ 5.169f (maybe a time scale or priority).
    // The function pointer is at LAB_00748150, named "NPCIntimidateSM" (the update callback).
    stateMachineRegisterUpdateFunction(5.169f, &NPCIntimidateSM_update, "NPCIntimidateSM");

    // Finalize the state machine construction.
    stateMachineFinalize();
}