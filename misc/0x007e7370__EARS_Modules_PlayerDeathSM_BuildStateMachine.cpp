// Xbox PDB: EARS_Modules_PlayerDeathSM_BuildStateMachine
// FUNC_NAME: Player::initDeathStateMachine
// Address: 0x007e7370
// Creates and configures the player death state machine with all states and transitions.

#include <cstdint>

// Forward declarations of helper functions (assumed from decompiled names)
namespace StateMachine {
    // Returns a state machine instance by name, creating if needed.
    void* getStateMachine(const char* name);
    // Returns 0 if not yet initialized
    int isStateMachineInitialized(void* sm);
    // Sets an owner/context for the state machine
    void setStateMachineOwner(void* sm, void* owner);
    // Adds a state with a numeric ID
    void addState(void* sm, uint32_t stateId);
    // Adds a named state with numeric ID
    void addNamedState(void* sm, const char* name, uint32_t stateId);
    // Adds a transition from a named state to a target state ID (0xFFFFFFFF = from any)
    void addTransition(void* sm, const char* fromState, uint32_t toStateId);
    // Registers a callback for a state machine function
    void registerCallback(void* sm, uint32_t callbackId, void* func, const char* name);
    // Finalizes/initializes the state machine for use
    void finalizeStateMachine(void* sm);
}

// Get the player object (assumed)
void* getPlayerObject();

void Player::initDeathStateMachine() {
    void* deathSM = StateMachine::getStateMachine("playerDeathSM");

    // Check if already initialized (returns 0 if not)
    if (StateMachine::isStateMachineInitialized(deathSM) == 0) {
        void* player = getPlayerObject();
        StateMachine::setStateMachineOwner(deathSM, player);

        // Define states (numeric IDs from enum, actual values unknown)
        // deathAnim (ID 4)
        StateMachine::addTransition(deathSM, "deathAnim", 0xFFFFFFFF);
        StateMachine::addState(deathSM, 0x31);
        StateMachine::addState(deathSM, 0x32);

        // respawnChoice (ID 4)
        StateMachine::addNamedState(deathSM, "respawnChoice", 4);
        StateMachine::addTransition(deathSM, "respawnChoice", 0xFFFFFFFF);

        // WaitForInput (ID 0x15 = 21)
        StateMachine::addNamedState(deathSM, "WaitForInput", 0x15);
        // respawn (ID 4)
        StateMachine::addNamedState(deathSM, "respawn", 4);
        StateMachine::addTransition(deathSM, "WaitForInput", 0xFFFFFFFF);

        // Additional states (IDs 0x36, 0x35 = 54, 53)
        StateMachine::addState(deathSM, 0x36);
        StateMachine::addState(deathSM, 0x35);

        // RespawnDelay (IDs 0x17, 0x18 = 23, 24)
        StateMachine::addNamedState(deathSM, "RespawnDelay", 0x17);
        StateMachine::addNamedState(deathSM, "RespawnDelay", 0x18);
        StateMachine::addTransition(deathSM, "RespawnDelay", 0xFFFFFFFF);

        // More states (IDs 0x34, 0x33, 0x37, 0x39, 0x38 = 52, 51, 55, 57, 56)
        StateMachine::addState(deathSM, 0x34);
        StateMachine::addState(deathSM, 0x33);
        StateMachine::addState(deathSM, 0x37);
        StateMachine::addState(deathSM, 0x39);
        StateMachine::addState(deathSM, 0x38);

        // Transition from respawn to any
        StateMachine::addTransition(deathSM, "respawn", 0xFFFFFFFF);

        // Additional states (IDs repeated)
        StateMachine::addState(deathSM, 0x34);
        StateMachine::addState(deathSM, 0x33);

        // Terminate state
        StateMachine::addTransition(deathSM, "terminate", 0xFFFFFFFF);
        StateMachine::addState(deathSM, 2); // State ID 2

        // Register a callback (value 0x3018ACC3 likely a hash/ID)
        StateMachine::registerCallback(deathSM, 0x3018ACC3, &PlayerDeathSM_callback, "PlayerDeathSM");

        // Finalize the state machine
        StateMachine::finalizeStateMachine(deathSM);
    }
    // If already initialized, do nothing
}

// External callback function (placeholder)
extern void PlayerDeathSM_callback();