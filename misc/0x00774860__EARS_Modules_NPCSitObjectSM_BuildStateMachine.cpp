// Xbox PDB: EARS_Modules_NPCSitObjectSM_BuildStateMachine
// FUNC_NAME: NPCSitObjectSM::buildStateMachine
// Function address: 0x00774860
// Builds the state machine for NPC sit-object behavior, defining states (cower, standUp, corpse, terminate, etc.) and transitions.

#include <cstdint>

// Forward declarations for engine functions (stub)
extern uint32_t createStateMachineHandle(void);
extern void addStateTable(const char* name, uint32_t handle);
extern void addTransition(const char* stateName, int32_t targetStateId);
extern void setStateFlags(int32_t stateId, int32_t flag1, int32_t flag2);
extern void addState(int32_t stateId);
extern void addStateFlag(int32_t stateId);
extern void addTransitionCondition(const char* stateName, int32_t eventId);
extern void setStateAnimation(const char* stateName, int32_t animIndex, int32_t unk1, int32_t unk2);
extern void setStateExitProperty(int32_t stateId);
extern void registerStateMachine(uint32_t machineId, void (*updateFunc)(), const char* name);
extern void finalizeStateMachine(void);

// Unknown data symbols (likely string/state constants)
extern const char* DAT_00d64b74;   // e.g., "idle" or "sit"
extern const char* DAT_00e41d10;   // e.g., "entering" or "start"
extern const char* DAT_00d63370;   // e.g., "exit" or "transition"

// Update function for the sit object state machine (from address 0x00774810)
extern void NPCSitObjectSM_update(void);

// State IDs (guessed from constants)
enum SitObjectState {
    kSitState_Terminate = 0x12,   // 18
    kSitState_Cower     = 0x13,   // 19
    kSitState_Cower2    = 0x25,   // 37
    kSitState_Cower3    = 0x26,   // 38
    kSitState_StandUp   = 0x17,   // 23
    kSitState_StandUp2  = 0x24,   // 36
    kSitState_StandUp3  = 0x27,   // 39
    kSitState_StandUp4  = 0x28,   // 40
    kSitState_StandUp5  = 0x29,   // 41
    kSitState_Corpse    = 0x15,   // 21
    kSitState_Corpse2   = 0x13,   // 19 (maybe different)
    kSitState_Corpse3   = 0x14,   // 20
    kSitState_Default   = 2       // 2
};

// Event IDs (guessed from constants)
enum SitObjectEvent {
    kEvent_Terminate = 0xc,   // 12
    kEvent_StandUp   = 0x14,  // 20
    kEvent_Exit      = 0x16,  // 22
    kEvent_Sit       = 7      // 7
};

void NPCSitObjectSM_buildStateMachine(void)
{
    // Create a handle for the state table
    uint32_t stateTableHandle = createStateMachineHandle();
    addStateTable("npcSitObjectStateTable", stateTableHandle);

    // Define transitions from state "DAT_00d64b74" (likely initial sit state) to terminate (any? -1)
    addTransition(DAT_00d64b74, -1);

    // Set flags for state 5 (unknown)
    setStateFlags(5, 1, 1);

    // Register state IDs 0x23 and 0x2a
    addState(0x23);
    addStateFlag(0x2a);

    // Add transition conditions for state "terminate" (event 0x12)
    addTransitionCondition("terminate", 0x12);
    // Add transition condition from DAT_00e41d10 (event 0xc)
    addTransitionCondition(DAT_00e41d10, 0xc);
    // Set animation for state DAT_00d63370 (6, 1, 1)
    setStateAnimation(DAT_00d63370, 6, 1, 1);

    // Cower state
    addTransitionCondition("cower", 0x13);
    addTransition("cower", -1);          // transition out of cower (any target)
    addState(0x25);
    addStateFlag(0x26);
    addTransitionCondition("terminate", 0x12);
    addTransitionCondition(DAT_00e41d10, 0xc);
    setStateAnimation(DAT_00d63370, 6, 1, 1);

    // StandUp state
    addTransitionCondition("standUp", 0x17);
    addTransitionCondition(DAT_00d64b74, 0x14);  // from initial sit state on event 0x14
    setStateExitProperty(0x27);
    addTransition("standUp", -1);
    addState(0x24);
    addState(8);
    addStateFlag(8);
    addTransitionCondition(DAT_00e41d10, 0xc);
    addTransitionCondition("terminate", 7);
    addTransition(DAT_00d63370, -1);
    addState(0x28);
    addTransitionCondition("terminate", 0x12);
    addTransitionCondition(DAT_00e41d10, 0xc);
    addTransitionCondition(DAT_00d63370, 0x16);
    addTransitionCondition(DAT_00d64b74, 7);
    addTransition(DAT_00e41d10, -1);
    addState(0x29);
    addTransitionCondition("terminate", 0x12);

    // Corpse state
    addTransitionCondition("corpse", 0x15);
    addTransition("corpse", -1);
    addState(0x13);
    addStateFlag(0x14);
    addTransition("terminate", -1);
    addState(2);

    // Register the state machine with unique ID, update function, and name
    registerStateMachine(0x1e9ba656, NPCSitObjectSM_update, "NPCSitObjectSM");

    // Finalize
    finalizeStateMachine();
}