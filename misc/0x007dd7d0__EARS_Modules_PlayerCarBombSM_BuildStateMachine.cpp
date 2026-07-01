// Xbox PDB: EARS_Modules_PlayerCarBombSM_BuildStateMachine
//FUNC_NAME: PlayerCarBombManager::initializeStateMachine
void PlayerCarBombManager::initializeStateMachine(void)
{
    // Look up or create the "playerCarBombTable" data structure
    // thunk_FUN_004dafd0 likely returns a handle/ID for the named table
    uint tableHandle = thunk_FUN_004dafd0("playerCarBombTable"); // 0x004dafd0

    // Check if the table already exists (returns 0 if not found)
    int exists = FUN_00621530(tableHandle); // 0x00621530
    if (exists == 0) {
        // Create a new table object
        uint newTable = FUN_009c8f80(); // 0x009c8f80

        // Register the table under the given name
        FUN_004ad9d0("playerCarBombTable", newTable); // 0x004ad9d0

        // Set the default state for the table to -1 (invalid/initial)
        FUN_004adae0(&DAT_00d63420, 0xffffffff); // 0x004adae0

        // Add state 0x31 (likely "Idle" or "Inactive")
        FUN_004acf70(0x31); // 0x004acf70

        // Add state 0x32 (likely "Armed" or "Active")
        FUN_004ad070(0x32); // 0x004ad070

        // Register a transition from state "Terminate" (0x13) to some state
        FUN_004acc70("Terminate", 0x13); // 0x004acc70

        // Add a transition condition: from "Terminate" state, on event 2, go to state _DAT_00d5c458 (some global state)
        FUN_004acd80("Terminate", 2, _DAT_00d5c458, 1); // 0x004acd80

        // Set the default state for "Terminate" to -1
        FUN_004adae0("Terminate", 0xffffffff); // 0x004adae0

        // Add state 2 (likely "Exploding" or "Done")
        FUN_004acf70(2); // 0x004acf70

        // Create a state machine instance with a unique ID (0x864ea6cf) and a callback at LAB_007dd760
        FUN_004adc90(0x864ea6cf, &LAB_007dd760, "PlayerCarBombSM"); // 0x004adc90

        // Finalize the table setup (e.g., compile transitions)
        FUN_004ada40(); // 0x004ada40
    }
    return;
}