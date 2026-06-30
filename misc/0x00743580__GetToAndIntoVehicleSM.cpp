// FUNC_NAME: GetToAndIntoVehicleSM
// Function at 0x00743580: Builds the NPC "GetToAndIntoVehicle" state machine.
// This constructs a complex hierarchical state machine for NPC vehicle entry behavior,
// using the EARS state machine framework (likely EA's state machine system).
// States include: vehicleIdle, moveToVehicleDoor, pickVehicleDoor, waitAtDoor,
// yellAtCarToSlowDown, goInOtherDoor, waitForBlockerAtDoor, allDoorsBlocked,
// noSeatsStayPut, enterVehicle, someoneIsInMySeat, etc.

// Helper function prototypes (inferred from usage):
static void addState(const char* stateName, int stateId);                          // FUN_004acc70
static void setDefaultState(const char* stateName, int transitionId);              // FUN_004adae0
static void addTransition(int fromState, int toState);                             // FUN_004acf70
static void setTransitionCondition(int fromState, int conditionType, float value); // FUN_004acd80 (variant with float)
static void setStateTimer(int state, int time, uint something);                    // FUN_004ad0f0
static void setStateIntProperty(int state, int property, int value);               // FUN_004ad170
static void setStateFlags(int state, int flags);                                   // FUN_004acff0
static void registerStateMachine(uint hash, void* table, const char* name);        // FUN_004adc90
static void finalizeStateMachine();                                                // FUN_004ada40
// Also: FUN_004ad070 (set something on state? probably setStateFlagOrTransition)
// FUN_004acf10 (maybe set substate machine?)
// FUN_004acd20 (maybe set error transition?)

// Global state machine data (addresses from Ghidra):
extern int DAT_00d63420;     // +0x??? - likely a state variable (e.g., initial state)
extern int DAT_00d63afc;     // +0x??? - another state variable (e.g., "vehicleIdle" state ID)
extern float DAT_00d5779c;   // +0x??? - some float parameter (maybe timeout or distance)

void FUN_00743580(void)
{
    // Get a hash or id for the state machine (possibly based on input context)
    uint inputHash = FUN_009c8f80();  // likely getContextHash() or similar

    // Log the state machine creation (debug string)
    FUN_004ad9d0("GetToAndIntoVehicleST", inputHash);

    // Set default state for some global state variable to invalid (-1)
    setDefaultState(&DAT_00d63420, 0xffffffff);   // DAT_00d63420 -> initial state = invalid

    // Add a state with ID 10 (likely "vehicleIdle"?)
    addState(&DAT_00d63afc, 10);                  // DAT_00d63afc = state vehicleIdle? (ID 10)
    addState("pickVehicleDoor", 4);
    setDefaultState("pickVehicleDoor", 0xffffffff);

    // Add transition from state 0xd (13?) -> probably "moveToVehicleDoor"
    addTransition(0xd);                            // add a transition (target state ID? Or from-to?)
    addState(&DAT_00d63afc, 10);                  // re-set same state? (maybe duplicate)
    addState("allDoorsBlocked", 0x14);            // 20
    addState("noSeatsStayPut", 0x15);             // 21
    addState("moveToVehicleDoor", 0x13);          // 19
    setDefaultState("moveToVehicleDoor", 0xffffffff);

    // Set timer for state 3 with timeout 0x20 and flag 1
    setStateTimer(3, 0x20, 1);
    
    // Set substate machine for state 1 to "NPCChaseST"
    setSubstateMachine("NPCChaseST", 1);          // FUN_004acf10
    
    // Set error transition for state "pathError" with conditions
    setErrorTransition("pathError", 6, 0x20, 1); // FUN_004acd20

    // Add state with ID 10 again?
    addState(&DAT_00d63afc, 10);
    addState("waitForBlockerAtDoor", 0x16);       // 22
    addState("yellAtCarToSlowDown", 0xd);         // 13
    addState("waitAtDoor", 0xb);                  // 11
    addState("goInOtherDoor", 0xc);               // 12
    addState("waitAtDoor", 1);                    // duplicate with new ID=1?

    // Set property: state 4 with parameter 0x20 and flag 1
    setStateIntProperty(4, 0x20, 1);               // FUN_004ad170
    
    setDefaultState("goInOtherDoor", 0xffffffff);
    addTransition(0x13);                           // add transition to state 19

    // Add state with ID 10 again
    addState(&DAT_00d63afc, 10);
    addState("pickVehicleDoor", 4);
    setDefaultState("waitForBlockerAtDoor", 0xffffffff);

    // Add transitions: from 0xb (11), from 8, to 8, to 0x11 (17)
    addTransition(0xb);
    addTransition(8);
    setTransitionFlags(8);                        // FUN_004acff0 (set flags on state)
    setTransitionFlags(0x11);                     // FUN_004acff0

    addState(&DAT_00d63afc, 10);
    addState("moveToVehicleDoor", 0x17);          // 23
    addState(&DAT_00d63420, 0x18);                // 24
    setDefaultState("noSeatsStayPut", 0xffffffff);
    addTransition(0xb);
    addState(&DAT_00d63afc, 10);

    // Set condition for state transition (from state 2 with float 1.0 and flag 1)
    setTransitionCondition(&DAT_00d63afc, 2, 1.0f, 1); // FUN_004acd80
    
    setDefaultState("waitAtDoor", 0xffffffff);
    addTransition(0xb);
    addTransition(0xf);
    setTransitionFlags(0xf);

    addState(&DAT_00d63afc, 10);
    addState("someoneIsInMySeat", 0x19);          // 25
    addState("enterVehicle", 0x11);               // 17
    setTransitionCondition(&DAT_00d63afc, 2, DAT_00d5779c, 1); // use global float

    setDefaultState("yellAtCarToSlowDown", 0xffffffff);
    setSubstateMachine("NPCFollowST", 1);          // FUN_004acf10

    addTransition(0xe);
    addState(&DAT_00d63afc, 10);
    addState("moveToVehicleDoor", 0xe);           // 14
    setDefaultState("pathError", 0xffffffff);

    addTransition(0x10);                          // 16
    addTransition(0xb);
    addTransition(0xe);

    addState(&DAT_00d63afc, 10);
    addState("pickVehicleDoor", 0xf);             // 15
    setDefaultState("allDoorsBlocked", 0xffffffff);

    addTransition(0x10);
    addTransition(0xb);
    addTransition(0xe);

    addState(&DAT_00d63afc, 10);
    addState("pickVehicleDoor", 0xf);             // duplicate?
    setDefaultState("someoneIsInMySeat", 0xffffffff);

    addTransition(0x10);
    addTransition(0xb);
    addTransition(0xe);

    addState(&DAT_00d63afc, 10);
    addState("pickVehicleDoor", 0x1a);            // 26
    addState("pickVehicleDoor", 0xf);             // 15
    setDefaultState("enterVehicle", 0xffffffff);

    setStateTimer(5, 1, 1);                       // state 5 timer with 1 sec?
    addTransition(0x14);                          // 20
    addTransition(0x12);                          // 18

    setSubstateMachine("vehicleEntryStateTable", 1); // FUN_004acf10

    addState(&DAT_00d63afc, 10);
    addState("vehicleIdle", 0x10);                // 16
    addState(&DAT_00d63afc, 0x12);                // 18
    addState(&DAT_00d63420, 1);                   // 1

    // Set additional flags/properties on states
    setStateFlag(0x15);                           // FUN_004ad070
    setStateFlag(0x10);
    setStateIntProperty(4, 1, 1);                 // state 4, property 1, value 1

    setDefaultState("vehicleIdle", 0xffffffff);
    addTransition(10);
    addState(&DAT_00d63afc, 4);
    setDefaultState(&DAT_00d63afc, 0xffffffff);

    addTransition(2);

    // Register the state machine with a hash, function table, and name
    registerStateMachine(0xd7440380, &LAB_007434f0, "GetToAndIntoVehicleSM");

    // Finalize (likely compile or validate the state machine)
    finalizeStateMachine();
    return;
}