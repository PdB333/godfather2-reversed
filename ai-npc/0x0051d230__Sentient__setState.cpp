// FUNC_NAME: Sentient::setState
// Reconstructed from Ghidra decompilation at 0x0051d230
// Sets the state for a Sentient entity, cleaning up previous behavior if leaving state 4 (likely "dead").

#include <cstdint>

class Sentient {
public:
    // +0x78: Pointer to state-specific data table (indexed by state)
    const void* p_stateData; // offset +0x78

    // +0xB0: Current state ID
    int state; // offset +0xB0

    // +0xC0: Pointer to active behavior instance (if any)
    void* p_currentBehavior; // offset +0xC0

    // Global pointer to a behavior manager (e.g., g_pBehaviorManager from DAT_01194538)
    // *g_pBehaviorManager is a struct with a virtual function table; offset +4 is the destroy function.
    extern struct BehaviorManager* g_pBehaviorManager;

    // Table of pointers to state-specific data, indexed by state ID
    extern const void* stateBehaviorTable[]; // PTR_LAB_00e38260

    void setState(int newState);
};

void __thiscall Sentient::setState(int newState) {
    // If current state is 4 (e.g., "dead" or "ending") and there is an active behavior,
    // destroy it via the behavior manager.
    if (this->state == 4 && this->p_currentBehavior != nullptr) {
        // Call destroyBehavior(g_pBehaviorManager, this->p_currentBehavior, 0)
        // The behavior manager's vtable at index 1 is the destroy method.
        (**(void (__thiscall**)(void*, int))(*reinterpret_cast<int*>(g_pBehaviorManager) + 4))(
            this->p_currentBehavior, 0);
        this->p_currentBehavior = nullptr;
    }

    // Set new state and update the state-specific data pointer.
    this->state = newState;
    this->p_stateData = stateBehaviorTable[newState];
}