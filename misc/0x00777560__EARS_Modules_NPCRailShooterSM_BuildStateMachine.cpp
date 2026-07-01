// Xbox PDB: EARS_Modules_NPCRailShooterSM_BuildStateMachine
// FUNC_NAME: buildNPCRailShooterStateMachine
// Address: 0x00777560
// Role: Constructs the state machine for NPC rail shooter behavior (shooting from car windows)
// Uses EA EARS engine state machine builder API

void buildNPCRailShooterStateMachine(void)
{
    // Allocate a new state machine handle
    uint stateMachineHandle = allocateStateMachine();

    // Create the state table with a name
    createStateTable("NPCRailShooterStateTable", stateMachineHandle);

    // --- State definitions and transitions ---

    // State: enterVehicle (ID: 0xFFFFFFFF means no transition? Or initial?)
    addTransition("enterVehicle", 0xFFFFFFFF);
    addState(3, 0x80001, 1); // state ID 3 with flags

    // State: windowRollDown (ID: 1)
    addState("windowRollDown", 1);
    setInitialState(0x34); // initial state ID 0x34

    // Transition from windowRollDown to something
    addTransition("windowRollDown", 0xFFFFFFFF);
    addTransition(0x23); // target state ID
    addTransition(0x24); // target state ID

    // State: leanOut (ID: 0x13)
    addState("leanOut", 0x13);
    addTransition(&DAT_00d63370, 0x21, 1, 1); // condition-based transition
    addTransition("leanOut", 0xFFFFFFFF);

    // State transitions for leanOut
    addTransition(0x29);
    addTransition(&DAT_00d63370, 0x21, 1, 1);

    // State: updateLeanedOut (ID: 7)
    addState("updateLeanedOut", 7);
    addTransition("updateLeanedOut", 0xFFFFFFFF);

    // State: death (ID: 0x22)
    addState(5, 0x40, 1);
    addTransition(0x2a);
    addTransition(0x2b);
    addTransition(0x35);
    addState("death", 0x22);
    addTransition(&DAT_00d63370, 0x21, 1, 1);
    addTransition("updateLeanedOut", 6, 0x40, 1);

    // State: leanIn (ID: 0x12)
    addState("leanIn", 0x12);
    addState("shoot", 0x16);
    addState("reload", 0x18);
    addState("switchSidesLeanIn", 0x1a);
    addState("goBackInCar", 0x20);
    addState("goBackInCar", 0x23);
    addTransition("switchSidesLeanIn", 6, 0x80000, 1);

    // State: shoot (ID: 0x16) with transitions
    addState(4, 0x40, 1);
    addTransition("shoot", 0xFFFFFFFF);
    addTransition(0x2c);
    addTransition(0x2d);
    addTransition(0x35);
    addState("leanIn", 0x12);
    addState("updateLeanedOut", 0x17);
    addState("goBackInCar", 0x20);
    addState("goBackInCar", 0x23);
    addTransition(&DAT_00d63370, 0x21, 1, 1);

    // State: reload (ID: 0x18)
    addTransition("reload", 0xFFFFFFFF);
    setInitialState(0x2e);
    addTransition(0x35);
    addState("leanIn", 0x12);
    addState("updateLeanedOut", 0x19);
    addState("goBackInCar", 0x23);
    addTransition(&DAT_00d63370, 0x21, 1, 1);

    // State: leanIn (ID: 0x12) transitions
    addTransition("leanIn", 0xFFFFFFFF);
    addTransition(0x31);
    addTransition(0x35);
    addState("windowRollUp", 7);
    addTransition(&DAT_00d63370, 0x21, 1, 1);
    addTransition("windowRollUp", 0xFFFFFFFF);
    addTransition(0x25);
    setInitialState(0x37);
    addTransition(0x26);
    addState("terminate", 0x14);

    // State: switchSidesLeanIn (ID: 0x1a)
    addTransition("switchSidesLeanIn", 0xFFFFFFFF);
    addTransition(0x32);
    addTransition(0x35);
    addState("switchSidesWindowRollup", 7);
    addTransition(&DAT_00d63370, 0x21, 1, 1);
    addTransition("switchSidesWindowRollup", 0xFFFFFFFF);
    addTransition(0x27);
    addTransition(0x28);
    addState("switchSidesFinish", 0x15);
    addTransition("switchSidesFinish", 0xFFFFFFFF);
    addTransition(0x33);
    addTransition(0x35);
    addState("windowRollDown", 0x1b);
    addState("terminate", 0x1e);
    addTransition(&DAT_00d63370, 0xFFFFFFFF);
    addTransition(0x2f);
    addState("leanOut", 0x1c);
    addState("death", 0x1d);
    addTransition("death", 0xFFFFFFFF);
    addTransition(0x30);
    addState("corpse", 7);
    addTransition("corpse", 0xFFFFFFFF);
    addTransition(0x38);
    addTransition(0x14);
    addTransition("goBackInCar", 0xFFFFFFFF);
    addTransition(0x31);
    addState("terminate", 7);
    addTransition("terminate", 0xFFFFFFFF);

    // Final state setup
    addState(4, 1, 1);
    addTransition(2);

    // Register the state machine with a hash and callback
    registerStateMachine(0x55662773, &buildNPCRailShooterStateMachine, "NPCRailShooterSM");

    // Finalize (or return)
    finalizeStateMachine();
}