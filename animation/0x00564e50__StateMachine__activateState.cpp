// FUNC_NAME: StateMachine::activateState
// Address: 0x00564e50
// Role: Attempts to activate a new state in a state machine. Calls a setup function, then checks if the current state (vfptr at +0x20) can activate (virtual call at vtable+8). If not, returns 0. Otherwise calls the state's activate method (vtable+4) and sets a flag at +0x238 to 1, returning 1.

class StateMachine {
public:
    // +0x00: vtable pointer (inherited)
    // ... other members ...
    // +0x20: pointer to current state object (has its own vtable)
    class State* m_pCurrentState;
    // +0x238: flag indicating state is active
    bool m_bStateActive;

    // Internal setup function (callee at 0x00565280)
    void setupState(/* unknown parameters */); // Actually FUN_00565280(this)

    // Virtual functions of the state object (offsets relative to State vtable)
    // State vtable:
    // +0x00: unknown
    // +0x04: bool activate(int param)  // virtual function at vtable+4
    // +0x08: bool canActivate()        // virtual function at vtable+8

    // This function:
    int activateState() {
        setupState(); // prior setup/cleanup
        if (m_pCurrentState != nullptr) {
            if (!m_pCurrentState->canActivate()) {
                return 0;
            }
        }
        m_pCurrentState->activate(0);
        m_bStateActive = true;
        return 1;
    }
};