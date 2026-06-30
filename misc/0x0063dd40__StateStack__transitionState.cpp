// FUNC_NAME: StateStack::transitionState
// Address: 0x0063dd40
// Role: Transitions the state machine to a new state or pops back to a previous state.
//       If pendingStateId (at +0x14) is not the sentinel 0x11F, it pushes a new state
//       (sets currentStateId to pendingStateId, currentData to pendingData).
//       Otherwise, it calls popState() to restore the previous state.
//       Returns the old currentData pointer.
//       Expects that at entry, m_currentStateId (at +0xc) is STATE_BASE (0x116).

#include <cassert>

// Forward declaration of the pop/restore function.
int popState(void* data);

// State id constants.
const int STATE_BASE = 0x116;       // Base/idle state
const int STATE_POP_SENTINEL = 0x11F; // Marks that a pop operation is requested

struct StateStack {
    int    m_savedState1;      // +0x4  (used during transition)
    int    m_currentStateCopy; // +0x8  (copy of m_savedState1)
    int    m_currentStateId;   // +0xc  (current state identifier)
    void*  m_currentData;      // +0x10 (data associated with current state)
    int    m_pendingStateId;   // +0x14 (if not sentinel, push this state)
    void*  m_pendingData;      // +0x18 (data for the pending state)
};

// __thiscall
void* __fastcall StateStack_transitionState(StateStack* this) {
    // Expect current state to be base state.
    if (this->m_currentStateId != STATE_BASE) {
        assert("<name> expected"); // FUN_00638b80
    }

    void* oldData = this->m_currentData; // Save current data to return later
    this->m_currentStateCopy = this->m_savedState1; // Backup the saved state

    if (this->m_pendingStateId != STATE_POP_SENTINEL) {
        // Push new state: update current state and data from pending fields.
        this->m_currentData = this->m_pendingData;
        this->m_currentStateId = this->m_pendingStateId;
        this->m_pendingStateId = STATE_POP_SENTINEL; // Clear pending
    } else {
        // Pop to previous state: call popState to restore from the data stack.
        this->m_currentStateId = popState(this->m_currentData); // FUN_00639c70
    }

    return oldData;
}