// Xbox PDB: EARS_Modules_PlayerMasterSM_BuildStateMachine
// FUNC_NAME: PlayerMasterSM::initStateTables
// Function address: 0x007aaa00
// Role: Initializes the player master state table and all sub-state machines.
// Registers the state tables for logical, lower body, upper body, camera, and face-to-face states,
// sets the initial "start" state, and registers the master state machine with its handler function.

static void initStateTables(void)
{
    // Get the hash ID for the player master state table (likely generated from its name)
    uint32_t masterTableHash = stringToHash(); // FUN_009c8f80 (unknown input, returns a hash)

    // Register the main state table with its hash
    registerStateTable("playerMasterStateTable", masterTableHash); // FUN_004ad9d0

    // Define the initial "start" state with ID 0xFFFFFFFF (invalid/initial)
    addStateToTable("start", 0xFFFFFFFF); // FUN_004adae0

    // Set up each sub-state table with capacity/ID of 1
    setupSubStateTable("playerLogicalStateTable", 1); // FUN_004acf10
    setupSubStateTable("playerLowerBodyStateTable", 1);
    setupSubStateTable("playerUpperBodyStateTable", 1);
    setupSubStateTable("playerCameraStateTable", 1);
    setupSubStateTable("playerF2FStateTable", 1);

    // Register the master state machine: associate a hash ID (0xB08AE1F6) with a handler function and name
    registerStateMachine(0xB08AE1F6, &stateMachineHandler, "PlayerMasterSM"); // FUN_004adc90 (LAB_007aa9c0 is likely the handler)

    // Finalize the state machine setup (e.g., commit all registrations)
    finalizeStateMachines(); // FUN_004ada40
}