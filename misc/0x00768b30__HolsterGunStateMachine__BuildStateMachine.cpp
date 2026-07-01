// FUNC_NAME: HolsterGunStateMachine::BuildStateMachine
// Address: 0x00768b30
// This function initializes the HolsterGun state machine for player.
// It registers states, sets animations and flags, and links to the state machine entry point.

void BuildHolsterGunStateMachine()
{
    // Obtain a unique identifier for the new state
    uint32 holsterStateId = GetNextStateId();                     // FUN_009c8f80

    // Register the "HolsterGunST" state with this ID
    RegisterState("HolsterGunST", holsterStateId);                // FUN_004ad9d0

    // Define the "holster" animation for the state (0xFFFFFFFF = no animation)
    SetStateAnimation("holster", 0xFFFFFFFF);                     // FUN_004adae0

    // Enable state flags that likely control entering/exiting conditions (0x23, 0x24)
    EnableStateFlag(0x23);                                        // FUN_004acf70
    EnableStateFlag(0x24);                                        // FUN_004acf70

    // Set a data field (likely a string reference or additional animation name)
    // DAT_00d63afc is probably "holster" or a similar string constant
    SetStateData(&DAT_00d63afc, 0x12);                            // FUN_004acc70

    // Set animation for that data entry (again no animation)
    SetStateAnimation(&DAT_00d63afc, 0xFFFFFFFF);                 // FUN_004adae0

    // Enable another flag (2) – possibly enables the state after setup
    EnableStateFlag(2);                                           // FUN_004acf70

    // Register the state machine "HolsterGunSM" with a hash 0x2d48e99b
    // and point to its entry function at LAB_00768760
    RegisterStateMachine(0x2d48e99b, &LAB_00768760, "HolsterGunSM"); // FUN_004adc90

    // Finalize the state machine construction
    FinalizeStateMachine();                                       // FUN_004ada40
}