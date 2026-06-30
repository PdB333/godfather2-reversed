// FUNC_NAME: PlayerActionDispatcher::dispatchAction

class PlayerActionDispatcher {
public:
    // +0x00: vtable? not used
    // +0x08: pointer to state data
    // +0x0C: valid flag
    void* stateData;   // at +0x08
    bool isActive;     // at +0x0C

    void dispatchAction(int param1);
};

struct ActionStateData {
    // +0x00: not used here
    // +0x04: flags (low byte = age counter)
    uint32_t flags;

    // For age < 10
    // +0x20: action type (young)
    uint32_t actionTypeYoung;
    // +0x24: action pointer (young)
    void* actionYoung;

    // For age >= 10
    // +0x28: action type (old)
    uint32_t actionTypeOld;
    // +0x2C: action pointer (old)
    void* actionOld;
};

void PlayerActionDispatcher::dispatchAction(int param1) {
    ActionStateData* state = reinterpret_cast<ActionStateData*>(this->stateData);
    if (state == nullptr) return;

    // Determine age category from low byte of flags
    uint32_t ageCategory = state->flags & 0xFF;
    bool isYoung = (ageCategory < 10);

    // Select appropriate action pointer based on age
    void* actionPtr = isYoung ? state->actionYoung : state->actionOld;
    if (actionPtr == nullptr) return;

    // Ensure the dispatcher is active
    if (!this->isActive) return;

    // Select the action type
    uint32_t actionType = isYoung ? state->actionTypeYoung : state->actionTypeOld;
    actionType &= 0x0FFFFFFF; // Mask out higher bits

    // Dispatch to specific action handlers
    if (actionType == 0) {
        FUN_00580380(); // Action 0 - likely idle or default
    } else if (actionType == 1) {
        FUN_0057ece0(); // Action 1 - walk or move
    } else if (actionType == 3) {
        FUN_0057b8b0(); // Action 3 - attack or interact
    } else if (actionType == 4) {
        FUN_0057d140(param1); // Action 4 - with a parameter, maybe target or direction
    }
}