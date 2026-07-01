// Xbox PDB: EARS_Modules_VehicleExitSM_BuildStateMachine
// FUNC_NAME: VehicleExitStateMachine::initializeStateTable
// Function address: 0x008850a0
// Creates the state table for vehicle exit state machine if not already registered.

// Known state IDs (deduced from transitions):
enum VehicleExitStateId : unsigned int {
    kStateTerminate        = 0xb,  // 11
    kStateWaitForClearExit = 0x4,  // 4
    kStateSpawnOnVehicle   = 0xe,  // 14
    kStateChangeSeat       = 0xc,  // 12
    kStateDespawn          = 0xd,  // 13
    kStateExitVehicle      = 0xf,  // 15
    // Additional IDs used: 0x12 (18), 0x13 (19), 0x10 (16), 0x11 (17), 0x14 (20), 0x15 (21), 0x16 (22), 0x17 (23)
};

void VehicleExitStateMachine::initializeStateTable() {
    // Look up existing state table by name
    HashTable* stateTable = findStateTable("vehicleExitStateTable");
    if (stateTable != nullptr) {
        return; // Already initialized
    }

    // Create and register the state table
    StateTable* newTable = createStateTableObject(); // Allocates a new state table instance
    registerStateTable("vehicleExitStateTable", newTable);

    // Set initial state: state ID 0
    setInitialState(0, &DAT_00d63420); // DAT likely a sentinel or constant

    // Add states
    addState(0x12);    // Some state
    addState(0x11);    // Some state

    // Add transitions from state 0xb ("terminate") to various states
    addTransition("terminate", 0xb);  // transition to state 0xb
    addTransition("waitForClearExit", 4);
    addTransition("spawnOnVehicle", 0xe);
    addTransition("changeSeat", 0xc);
    addTransition("despawn", 0xd);
    addTransition("exitVehicle", 0xf);

    // Set initial states for specific transitions (maybe default state after transition)
    setInitialState("waitForClearExit", 1);
    setInitialState("changeSeat", 2);
    setInitialState("exitVehicle", 3);
    setInitialState("spawnOnVehicle", 4);
    setInitialState("despawn", 5);
    setInitialState("terminate", 6);

    // Additional states
    addState(0x13);
    addState(0x10);
    addState(2);
    addState(8);
    addState(0xe);
    addState(0xd);
    addState(0xc);
    addState(0xf);
    addState(0x14);
    addState(0x15);
    addState(0x16);
    addState(0x17);

    // Clear some states (likely flags or conditions)
    clearState(8);
    clearState(0xe);
    clearState(0x15);
    clearState(0xc);

    // Register a callback for the state machine named "VehicleExitSM"
    // The callback function is at 0x00885050, handles state transitions?
    registerStateMachineCallback(0xff45bbca, FUN_00885050, "VehicleExitSM");

    // Finalize and build the state table (might initialize internal data structures)
    finalizeStateTable();
}