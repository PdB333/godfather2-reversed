// Xbox PDB: EARS::Modules::ReloadGunSM::BuildReloadGunStateTable
// FUNC_NAME: initializeReloadGunStateMachine
void initializeReloadGunStateMachine(void)
{
    // Get a new state ID from the state machine manager
    int reloadStateId = getNewStateId();

    // Register the "ReloadGunST" state with the new ID
    registerState("ReloadGunST", reloadStateId);

    // Add a transition from "reload" state to an invalid state (0xffffffff = none)
    addStateTransition("reload", 0xffffffff);

    // Enable specific transition flags (0x23 and 0x24)
    enableTransitionFlag(0x23);
    enableTransitionFlag(0x24);

    // Add a state (ID 0x12) to the global reload state machine
    addStateToReloadMachine(&gReloadStateMachine, 0x12);

    // Add a transition from the state machine itself to none
    addStateTransition(&gReloadStateMachine, 0xffffffff);

    // Enable another transition flag (2)
    enableTransitionFlag(2);

    // Set the entry point function for the "ReloadGunSM" state machine
    setStateMachineEntryPoint(0x77a4600c, &ReloadGunSMEntryFunc, "ReloadGunSM");

    // Finalize and initialize the state machine
    finalizeStateMachine();
}