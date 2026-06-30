// FUNC_NAME: buildSpecialMotionStateMachine
void buildSpecialMotionStateMachine(void)
{
    // Get a unique handle for the new state machine (e.g., from a manager)
    uint32_t machineHandle = getStateMachineHandle(); // FUN_009c8f80

    // Set the name of the state machine
    stateMachineSetName("SpecialMotionST", machineHandle); // FUN_004ad9d0

    // Add a transition from the "Default" state (DAT_00d63420) to any (0xffffffff)
    stateMachineAddTransition(&DAT_00d63420, 0xffffffff); // likely "Default" state

    // Add base states
    stateMachineAddState(&DAT_00d64b74, 0xB); // likely "Fall" state
    stateMachineAddState("DoVault", 0xD);
    stateMachineAddState("DoLadderClimb", 0xE);
    stateMachineAddState(&DAT_00d64b54, 0xF); // likely "Jump" state
    stateMachineAddState("Terminate", 4);

    // Allow any transition from the "Fall" state
    stateMachineAddTransition(&DAT_00d64b74, 0xffffffff);

    // Set initial states for sub‑machines or entry points
    stateMachineSetInitState(0x15); // FUN_004acf70
    stateMachineSetInitState(8);

    // Add a state with only an ID (no name? maybe for a sub‑state)
    stateMachineAddState(8); // FUN_004acff0

    // Add a sub‑state machine for turning to position termination
    stateMachineAddSubMachine("turnToPositionTerminateTable", 1); // FUN_004acf10

    // Reuse the "Default" state with id 0xC
    stateMachineAddState(&DAT_00d63420, 0xC);

    // Add a "Terminate" state with id 10
    stateMachineAddState("Terminate", 10);

    // Allow transition from "DoVault" to any
    stateMachineAddTransition("DoVault", 0xffffffff);

    // Set initial state for the NPC vault sub‑machine
    stateMachineSetInitState(0x14);

    // Add NPC vault sub‑state machine
    stateMachineAddSubMachine("NPCVaultST", 1);

    // Add a "Terminate" state inside the NPC vault machine
    stateMachineAddState("Terminate", 1);

    // Mark state 0x13 as terminal or special (FUN_004ad070)
    stateMachineSetStateFlag(0x13);

    // Allow transition from "DoLadderClimb" to any
    stateMachineAddTransition("DoLadderClimb", 0xffffffff);

    // Set initial state for the NPC ladder sub‑machine
    stateMachineSetInitState(0x14);

    // Add NPC ladder sub‑state machine
    stateMachineAddSubMachine("NPCLadderST", 1);

    stateMachineAddState("Terminate", 1);
    stateMachineSetStateFlag(0x13);

    // Allow transition from "Jump" (DAT_00d64b54) to any
    stateMachineAddTransition(&DAT_00d64b54, 0xffffffff);

    // Set entry states for the seek‑to‑position machine
    stateMachineSetInitState(0x16);
    stateMachineSetInitState(0x13);

    // Add seek‑to‑position sub‑state machine
    stateMachineAddSubMachine("SeekToPositionST", 1);

    // Add "Fall" and landing states
    stateMachineAddState(&DAT_00d64b74, 0xB);
    stateMachineAddState("FallLand", 1);
    stateMachineSetStateFlag(0x17);

    // Allow transition from "FallLand" to any
    stateMachineAddTransition("FallLand", 0xffffffff);

    stateMachineAddState("Terminate", 0x10);
    stateMachineSetStateFlag(0x14);
    stateMachineSetStateFlag(0x18);

    // Allow transition from "Terminate" to any
    stateMachineAddTransition("Terminate", 0xffffffff);

    // Final initial state settings
    stateMachineSetInitState(0x14);
    stateMachineSetInitState(2);

    // Finalize the state machine with a hash, an update function, and a name
    stateMachineFinalize(0x10ce9029, &specialMotionSMUpdate, "SpecialMotionSM"); // FUN_004adc90

    // Register the built state machine with the engine
    stateMachineRegister(); // FUN_004ada40

    return;
}