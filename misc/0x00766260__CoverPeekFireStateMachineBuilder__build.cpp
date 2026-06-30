// FUNC_NAME: CoverPeekFireStateMachineBuilder::build
// Address: 0x00766260
// Purpose: Constructs the state machine for cover peek/fire behavior.

// Note: This function uses EARS state machine framework calls.
// Data symbols (DAT_00d63420, DAT_00d63afc, DAT_00d657e4) are string constants
// whose exact values are unknown but likely correspond to state names like
// "CoverPeekFireRoot", "PeekFireA", "FromFireState", etc.

#include <cstdint>

// Forward declarations of state machine framework functions (renamed for clarity)
uint32_t stateMachineGetRegistry();                                        // FUN_009c8f80
void stateMachineRegisterName(const char* name, uint32_t handle);          // FUN_004ad9d0
void stateMachineAddState(const char* stateName, int32_t parentId);        // FUN_004adae0
void stateMachineSetTransition(int32_t transitionId);                      // FUN_004acf70
void stateMachineSetInitialState(const char* stateName, bool flag);        // FUN_004acf10
void stateMachineAddStateWithId(const char* stateName, int32_t stateId);   // FUN_004acc70
void stateMachineSetTransitionAction(int32_t transitionId);                // FUN_004acff0
void stateMachineSetStateAction(const char* stateName, int32_t conditionId,
                                float param, bool enable);                // FUN_004acd80
void stateMachineSetStateCallback(int32_t callbackId);                     // FUN_004ad070
void stateMachineCreate(uint32_t id, void (*updateFunc)(), const char* name); // FUN_004adc90
void stateMachineFinalize();                                                // FUN_004ada40

// Update function for this state machine (address 0x007661f0)
extern void CoverPeekFireSMUpdate();

// External string constants (Ghidra data refs)
extern const char* DAT_00d63420;   // e.g., "CoverPeekFireRoot"
extern const char* DAT_00d63afc;   // e.g., "PeekFireA"
extern const char* DAT_00d657e4;   // e.g., "FromFireState"

void buildCoverPeekFireStateMachine(void)
{
    uint32_t smHandle = stateMachineGetRegistry();

    // Register the overall state machine
    stateMachineRegisterName("CoverPeekFireST", smHandle);

    // Root state with no parent (ID = -1)
    stateMachineAddState(DAT_00d63420, 0xFFFFFFFF);

    // Set entry transition (ID 0xC)
    stateMachineSetTransition(0xC);

    // Set initial state for the "trackToPositionAndDirectionStateTable" sub-machine
    stateMachineSetInitialState("trackToPositionAndDirectionStateTable", 1);

    // State: "startPeekFire" (ID 1)
    stateMachineAddStateWithId("startPeekFire", 1);
    stateMachineAddState("startPeekFire", 0xFFFFFFFF);       // likely self-loop or unconditional

    // Transition index 0x25
    stateMachineSetTransition(0x25);

    // States for peekFire (multiple IDs using same string)
    stateMachineAddStateWithId(DAT_00d63afc, 0x12);   // state ID 18
    stateMachineAddStateWithId("peekFire", 0x13);     // state ID 19
    stateMachineAddStateWithId(DAT_00d63afc, 4);      // state ID 4 (reuse same string)
    stateMachineAddState("peekFire", 0xFFFFFFFF);     // transition from peekFire

    // Transition indices: 0x1F, then more
    stateMachineSetTransitionAction(0x1F);
    stateMachineAddStateWithId("toFire", 4);
    stateMachineAddState("toFire", 0xFFFFFFFF);

    stateMachineSetTransition(0x25);
    stateMachineSetTransition(0x23);
    stateMachineSetTransitionAction(8);
    stateMachineSetTransitionAction(0x1F);

    // State "fromFire" (using DAT_00d657e4) with ID 0x14
    stateMachineAddStateWithId(DAT_00d657e4, 0x14);
    stateMachineSetStateAction("fromFire", 2, 1.0f, 1);   // condition ID 2, float=1.0, enable
    stateMachineAddState(DAT_00d657e4, 0xFFFFFFFF);

    // Set initial state for "BurstFireST"
    stateMachineSetInitialState("BurstFireST", 1);
    stateMachineSetTransitionAction(8);

    stateMachineAddStateWithId("fromFire", 1);
    stateMachineAddState("fromFire", 0xFFFFFFFF);

    stateMachineSetTransition(0x25);
    stateMachineSetTransition(0x24);
    stateMachineSetTransitionAction(8);

    // Callback for transition 0x25 (exit action)
    stateMachineSetStateCallback(0x25);

    // Another peekFire state with ID 7
    stateMachineAddStateWithId(DAT_00d63afc, 7);
    stateMachineAddState(DAT_00d63afc, 0xFFFFFFFF);

    // Final transition set
    stateMachineSetTransition(2);

    // Create the actual state machine object
    stateMachineCreate(0x5A546DE2, CoverPeekFireSMUpdate, "CoverPeekFireSM");

    // Finalize the state machine definition
    stateMachineFinalize();
}