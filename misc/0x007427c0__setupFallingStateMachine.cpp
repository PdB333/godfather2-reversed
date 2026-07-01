// FUNC_NAME: setupFallingStateMachine

#include <cstdint>

// Forward declarations of state machine system functions
// These would be part of the EARS engine's state machine system
static uint32_t getStateTable(const char* name);
static bool isStateTableNull(uint32_t table);
static uint32_t createEmptyStateTable();
static void registerStateTable(const char* name, uint32_t table);
static void setStateDefaultTransition(const char* state, int32_t defaultTransition);
static void addState(uint32_t stateId, uint32_t param1, uint32_t param2); // FUN_004ad0f0
static void addStateSimple(uint32_t stateId); // FUN_004acf70
static void addStateAlt(uint32_t stateId); // FUN_004acff0
static void addStateAnother(uint32_t stateId); // FUN_004ad070
static void addTransition(const char* fromState, uint32_t toState); // FUN_004acc70
static void addConditionalTransition(const char* fromState, uint32_t eventId, uint32_t data, uint32_t flags); // FUN_004acd80
static void registerStateLogic(uint32_t stateHash, void* functionPtr, const char* name); // FUN_004adc90
static void finalizeStateMachine(); // FUN_004ada40

// External data references (likely string constants)
extern const char* DAT_00d63ba4; // Some string, probably "ragdollDeath" variant
extern uint32_t DAT_00d5d7b8;   // Some data value for transition
extern uint32_t DAT_00d58cbc;   // Another data value

// External function reference for the falling state machine logic (at address 0x00742390)
extern void FallSM();

// 0x007427c0 - Initialization of the falling animation state machine
void setupFallingStateMachine()
{
    uint32_t fallingTable = getStateTable("fallingStateTable");
    if (isStateTableNull(fallingTable))
    {
        // Create and register the new state table
        uint32_t newTable = createEmptyStateTable();
        registerStateTable("fallingStateTable", newTable);

        // Configure default transition for "falling" state (to -1 = no transition)
        setStateDefaultTransition("falling", 0xffffffff);

        // Add states with properties: stateId=5, param1=0x400, param2=1
        addState(5, 0x400, 1);

        // Add simple states (IDs: 10, 14)
        addStateSimple(10);
        addStateSimple(14); // 0xe

        // Add alternate states (IDs: 11, 12)
        addStateAlt(11); // 0xb
        addStateAlt(12); // 0xc

        // Add another set of states (IDs: 13, 15)
        addStateAnother(13); // 0xd
        addStateAnother(15); // 0xf

        // Transition from "ragdollDeath" state to state 11
        addTransition("ragdollDeath", 11);

        // Transition from DAT_00d63ba4 (unknown string) to state 10
        addTransition(DAT_00d63ba4, 10);

        // Conditional transition from DAT_00d63ba4: event 2, data from DAT_00d5d7b8, flags 1
        addConditionalTransition(DAT_00d63ba4, 2, DAT_00d5d7b8, 1);

        // Set default transition for "ragdollDeath" (no effect since it's already at -1? but explicitly done)
        setStateDefaultTransition("ragdollDeath", 0xffffffff);

        // Add more states
        addStateSimple(16); // 0x10

        // Transition from DAT_00d63ba4 to state 12
        addTransition(DAT_00d63ba4, 12);

        // Conditional transition from DAT_00d63ba4: event 2, data from DAT_00d58cbc, flags 1
        addConditionalTransition(DAT_00d63ba4, 2, DAT_00d58cbc, 1);

        // Set default transition for DAT_00d63ba4
        setStateDefaultTransition(DAT_00d63ba4, 0xffffffff);

        // Add state 2
        addStateSimple(2);

        // Register the state logic function for the falling state machine (hash 0xd495fec9, function FallSM)
        registerStateLogic(0xd495fec9, reinterpret_cast<void*>(&FallSM), "FallSM");

        // Finalize the state machine
        finalizeStateMachine();
    }
}