// Xbox PDB: EARS_Modules_NPCPlantCarBombSM_BuildStateTable
// FUNC_NAME: setupPlantCarBombStates
// Function address: 0x0076a300
// Role: Registers states and transitions for the NPC "Plant Car Bomb" behavior state machine.

#include <cstdint>

// Forward declarations for EA EARS state machine functions (assumed from Ghidra analysis)
void registerStateTable(const char* name, uint32_t context);
void setDefaultState(const char* state, uint32_t defaultId);
void pushState(uint32_t stateId);
void addTransition(const char* state, uint32_t eventId);
void addConditionalTransition(const char* state, uint32_t eventId, uint32_t flags1, uint32_t flags2);
void addTimedTransition(uint32_t hash, uint32_t param1, uint32_t param2, uint32_t flags, float duration);
void subStateMachine(const char* name, uint32_t priority);
void finalizeStateMachine(const char* name, uint32_t somePtr, const char* machineName);
void buildMachine();

// Likely returns a context ID for the state machine
uint32_t getMachineContext();

void setupPlantCarBombStates()
{
    uint32_t context = getMachineContext();

    // Register the main state table for NPC plant car bomb behavior
    registerStateTable("npcPlantCarBombST", context);

    // Set default initialization state
    setDefaultState("plantBombInit", 0xffffffff);

    // Push states for various phases
    pushState(0x23); // e.g., STATE_IDLE or STATE_INIT

    // Add transitions from "terminate" to event 0x13
    addTransition("terminate", 0x13);

    // Add transition to play intro animation
    addTransition("playIntroAnim", 0x12);

    // Add transition to approach vehicle target
    addTransition("approachVehicleTarget", 4);

    // Set default for approach state
    setDefaultState("approachVehicleTarget", 0xffffffff);

    // Use a sub-state machine: NPC chase state table with priority 1
    subStateMachine("NPCChaseST", 1);

    // Additional transitions
    addTransition("terminate", 0x13);
    addTransition("playIntroAnim", 1);
    addTransition("playIntroAnim", 0x12);

    // Conditional transitions (flags: 0x20, 0x4000, etc.)
    addConditionalTransition("terminate", 6, 0x20, 1);
    addConditionalTransition("terminate", 6, 0x4000, 1);

    // Reset default for intro animation
    setDefaultState("playIntroAnim", 0xffffffff);

    // Push another state
    pushState(0x25);

    // Timed transition (hash 0x1b4e393d, param1=1, param2=1, flags=0, duration=1.0f)
    addTimedTransition(0x1b4e393d, 1, 1, 0, 1.0f);

    // Use a tracking sub-state machine
    subStateMachine("trackToPositionAndDirectionStateTable", 1);

    addTransition("terminate", 0x13);
    addTransition("plantBomb", 7);

    setDefaultState("plantBomb", 0xffffffff);

    pushState(0x24);

    addTimedTransition(0x642b1003, 1, 1, 0, 1.0f);

    pushState(8);
    // Enable/disable states (0x8 and 0x27)
    // FUN_004acff0 might be enableState/disableState
    disableState(8);
    disableState(0x27);

    addTransition("terminate", 0x13);
    addTransition("playOutroAnim", 7);

    setDefaultState("playOutroAnim", 0xffffffff);

    addTimedTransition(0xed6145d4, 1, 1, 0, 1.0f);

    disableState(0x27);

    addTransition("terminate", 0x13);
    addTransition("terminate", 0x14);
    addTransition("terminate", 7);

    // Prioritize state 0x26
    prioritizeState(0x26);

    setDefaultState("terminate", 0xffffffff);

    pushState(2);

    // Finalize the state machine with name "NPCPlantCarBombSM"
    finalizeStateMachine(0xc5459866, &someLabel, "NPCPlantCarBombSM");

    // Build the complete machine
    buildMachine();
}