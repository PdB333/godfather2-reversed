// Xbox PDB: EARS::Modules::DrawGunSM::BuildDrawGunStateTable
// FUNC_NAME: PlayerDrawGunStateMachine::initialize
void PlayerDrawGunStateMachine::initialize()
{
    // Get a hash or resource ID for "DrawGun" concept
    uint drawGunHash = getStringHash(); // FUN_009c8f80()

    // Register the main label for the draw gun state machine
    registerString("DrawGunST", drawGunHash); // FUN_004ad9d0()

    // Set global state indicator (maybe DAT_00d63420 is a global state variable) to -1 (reset)
    setGlobalStateVariable(&DAT_00d63420, 0xffffffff); // FUN_004adae0()

    // Add a state with ID 0x12 (18) bound to "drawGun"
    addState("drawGun", 0x12); // FUN_004acc70()

    // Add another state referencing global data (DAT_00d63afc) with flag 4
    addState(&DAT_00d63afc, 4); // FUN_004acc70()

    // Reset the "drawGun" state to -1 (clear)
    setState("drawGun", 0xffffffff); // FUN_004adae0()

    // Set entry action for state 0x23 (35)
    setStateEntryAction(0x23); // FUN_004acf70()

    // Set exit action for state 0x24 (36)
    setStateExitAction(0x24); // FUN_004acff0()

    // Add another state with global data and flag 7
    addState(&DAT_00d63afc, 7); // FUN_004acc70()

    // Reset that state to -1
    setState(&DAT_00d63afc, 0xffffffff); // FUN_004adae0()

    // Set entry action for state 2
    setStateEntryAction(2); // FUN_004acf70()

    // Create a state machine with a specific hash (0x3b6dbfa9) and jump label
    createStateMachine(0x3b6dbfa9, &LAB_00768be0, "DrawGunSM"); // FUN_004adc90()

    // Finalize or apply changes to the state machine configuration
    finalizeStateMachine(); // FUN_004ada40()
}