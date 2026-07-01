// Xbox PDB: EARS_Modules_PlayerInventoryBrowserSM_BuildStateMachine
// FUNC_NAME: PlayerInventoryBrowser::initStateMachine
// Function at 0x007de690: Sets up the state machine for the player inventory browser UI state.

#include <cstdint>

// Forward declarations of internal helper functions (EA EARS engine)
// Note: These are educated guesses based on usage patterns.
static int getInventoryBrowserStateTableHandle();                              // FUN_009c8f80
static void registerStateTable(const char* tableName, int handle);             // FUN_004ad9d0
static void setStateTransition(const char* stateName, int targetStateId);      // FUN_004adae0 (0xFFFFFFFF = no transition)
static void addState(const char* stateName, int stateId);                      // FUN_004acc70
static void setEntryState(int stateId);                                        // FUN_004acf70
static void createStateMachine(int vtableOffset, void* updateFunc, const char* name); // FUN_004adc90
static void finalizeStateMachine();                                            // FUN_004ada40

// Constants
static const char* kStateTableName = "playerInventoryBrowserStateTable";
static const char* kDefaultState  = "default";  // DAT_00d64b74
static const char* kStateDisabled = "disabled";
static const char* kStateNextItem = "nextitem";
static const char* kStatePrevItem = "previousitem";
static const char* kStateGhostUpdate = "ghostupdate";

// State IDs (mapped from the integer constants in the binary)
enum InventoryBrowserState : int {
    kStateInvalid   = -1,
    kStateGhostUpdate = 0x13, // 19
    kStateNextItem    = 0x14, // 20
    kStatePrevItem    = 0x15, // 21
    kStateDisabled    = 0x16, // 22
    kStateSomeOther   = 0x17, // 23 (used for DAT_00d64b74)

    kEntry1           = 0x31, // 49
    kEntry2           = 0x32, // 50
    kEntry3           = 0x34, // 52
    kEntry4           = 0x35  // 53
};

// External function for state machine update (referenced by LAB_007de620)
extern void updateInventoryBrowserStateMachine(void* stateMachine);

void PlayerInventoryBrowser::initStateMachine() {
    // Get the handle for the inventory browser state table (likely a game-wide context)
    int stateTableHandle = getInventoryBrowserStateTableHandle();

    // Register the name of the state table with the engine
    registerStateTable(kStateTableName, stateTableHandle);

    // Set default transition to nothing (0xFFFFFFFF => disabled)
    setStateTransition(kDefaultState, kStateInvalid);    // 0xFFFFFFFF

    // Add all states with their respective IDs
    addState(kStateDisabled,    kStateDisabled);    // 0x16
    addState(kStateNextItem,    kStateNextItem);    // 0x14
    addState(kStatePrevItem,    kStatePrevItem);    // 0x15
    addState(kStateGhostUpdate, kStateGhostUpdate); // 0x13

    // Configure transitions from "nextitem"
    setStateTransition(kStateNextItem, kStateInvalid);  // no transition
    setEntryState(kEntry1);                              // set entry state to 0x31

    // Configure transitions from "disabled" & kDefaultState (id 3)
    addState(kStateDisabled,  kStateSomeOther);   // re-register? Actually id=3
    addState(kDefaultState,   kStateSomeOther);   // id=3
    setStateTransition(kStatePrevItem, kStateInvalid);
    setEntryState(kEntry2);                         // 0x32

    addState(kStateDisabled,  kStateSomeOther);   // id=3 again
    addState(kDefaultState,   kStateSomeOther);
    setStateTransition(kStateGhostUpdate, kStateInvalid);
    setEntryState(kEntry3);                         // 0x34

    addState(kDefaultState,   kStateSomeOther);   // id=3
    setStateTransition(kStateDisabled, kStateInvalid);
    setEntryState(kEntry4);                         // 0x35

    // Re-register default state with id 0x17
    addState(kDefaultState,   kStateSomeOther);   // 0x17

    // Create the actual state machine object
    // 0xde87e228 is likely the vtable for the state machine class
    // LAB_007de620 is a function pointer for the state machine's update method
    createStateMachine(0xde87e228, (void*)updateInventoryBrowserStateMachine, "PlayerInventoryBrowserSM");

    // Finalize the state machine creation
    finalizeStateMachine();
}