// FUNC_NAME: PlayerStateMachine::updateState
// Address: 0x00642f70
// Role: Updates the player state machine, handling state 0xB (likely a specific state like "entering cover" or "ragdoll") with comparison of two counters and a global threshold.

class PlayerStateMachine {
public:
    int m_type;            // +0x00: state type (0xB = state 11)
    int m_param1;          // +0x04: parameter (e.g., distance, target ID)
    int pad_0x08[1];       // +0x08: padding
    int m_counter1;        // +0x0C: some internal counter 1
    int m_counter2;        // +0x10: some internal counter 2
};

// Global pointer to a manager/database (e.g., SimManager)
extern int* g_someGlobal; // actually unaff_ESI +0x34 is a threshold value

extern void baseUpdate();                    // FUN_00642b00
extern void handleTypeBwithCounter(int val); // FUN_00642d90
extern void handleOther();                   // FUN_00642ec0

void __thiscall PlayerStateMachine::updateState(void) {
    if (this->m_counter1 == this->m_counter2) {
        baseUpdate();
        return;
    }
    baseUpdate();

    if (this->m_type == 0xB) {
        // Check again because baseUpdate may have changed the counters
        if (this->m_counter1 == this->m_counter2) {
            return;
        }
        // Compare param with global threshold (offset 0x34 from global)
        if (*(int*)(g_someGlobal + 0x34 / sizeof(int)) <= this->m_param1) {
            handleTypeBwithCounter(this->m_param1);
            return;
        }
    }
    handleOther();
}