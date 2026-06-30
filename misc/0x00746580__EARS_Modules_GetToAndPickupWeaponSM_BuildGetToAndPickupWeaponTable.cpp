// Xbox PDB: EARS::Modules::GetToAndPickupWeaponSM::BuildGetToAndPickupWeaponTable
// FUNC_NAME: NPCStateMachineFactory::createGetToAndPickupWeaponStateMachine
void NPCStateMachineFactory::createGetToAndPickupWeaponStateMachine()
{
    // Get state machine manager instance
    StateMachineManager* manager = getStateMachineManager();
    
    // Set the name for this state machine
    setStateMachineName(manager, "GetToAndPickupWeaponST");
    
    // Add base state (index 0xFFFFFFFF = -1 means no parent?)
    addState(manager, &DAT_00d63afc, 0xFFFFFFFF); // &DAT_00d63afc likely "root" or "default"
    
    // Add states with IDs
    addState(manager, &DAT_00d63afc, 10);        // state 10: maybe "idle"?
    addState(manager, "moveToWeapon", 4);        // state 4
    setStateExit(manager, "moveToWeapon", 0xFFFFFFFF); // exit condition -1 means always?
    
    // Add transition from state 3 to something with flag 0x20, target 1
    addTransition(manager, 3, 0x20, 1);
    
    // Set initial state to "NPCChaseST" with parameter 1
    setInitialState(manager, "NPCChaseST", 1);
    
    // Add more states
    addState(manager, &DAT_00d63afc, 10);
    addState(manager, "pickupWeaponLow", 0xB);    // 11
    addState(manager, "pickupWeaponMedium", 0xC); // 12
    addState(manager, "pickupWeaponHigh", 0xD);   // 13
    
    // Add transition with condition for pickup failure
    addTransitionWithCondition(manager, "pickupWeaponFailure", 6, 0x20, 1);
    
    // Add more states
    addState(manager, &DAT_00d63afc, 0xE); // 14
    addState(manager, &DAT_00d63afc, 1);   // state 1
    
    // Set entry action for state 4
    setEntryAction(manager, 4, 0x20, 1);
    
    // Set exit action for pickupWeaponLow
    setStateExit(manager, "pickupWeaponLow", 0xFFFFFFFF);
    setExitAction(manager, 10); // action for state 10?
    
    // Add states again (seems redundant, maybe different contexts)
    addState(manager, &DAT_00d63afc, 10);
    addState(manager, &DAT_00d63afc, 7);
    setStateExit(manager, "pickupWeaponMedium", 0xFFFFFFFF);
    setUpdateAction(manager, 0xB); // update action for state 11?
    
    addState(manager, &DAT_00d63afc, 10);
    addState(manager, &DAT_00d63afc, 0xF); // 15
    setStateExit(manager, "pickupWeaponHigh", 0xFFFFFFFF);
    setUpdateAction(manager, 0xB);
    
    addState(manager, &DAT_00d63afc, 10);
    addState(manager, &DAT_00d63afc, 0xF);
    setStateExit(manager, "pickupWeaponFailure", 0xFFFFFFFF);
    
    // Add transition from state 6 with flag 0x40000 to target 1
    addTransition(manager, 6, 0x40000, 1);
    
    // Set exit actions for state 2 twice? (maybe different contexts)
    setExitAction(manager, 2);
    setStateExit(manager, &DAT_00d63afc, 0xFFFFFFFF);
    setExitAction(manager, 2);
    
    // Register the state machine with a hash and callback function
    registerStateMachine(manager, 0xEF2BFAD8, (StateMachineCallback)&LAB_00746550, "GetToAndPickupWeaponSM");
    
    // Finalize the state machine construction
    finalizeStateMachine(manager);
}