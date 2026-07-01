// FUNC_NAME: SomeClass::checkStateAndCall
// Address: 0x0090a8f0
// Role: If the state member (offset +0x8) is non-zero and not equal to 0x48 (kStateExcluded),
//        call some function (FUN_00791a70) and return immediately.
// Note: The inner branch is logically dead because the outer condition already ensures the state is non-zero.
//       This is likely a compiler artifact; the intended logic is a single condition.

class SomeClass {
public:
    // offset +0x00: vtable pointer (implied)
    // offset +0x04: unknown (possibly size or flags)
    // offset +0x08: m_state (int32) - state identifier
    int m_state; // +0x08

    void checkStateAndCall() {
        // Original decompiled logic (with dead branch preserved for accuracy)
        if (m_state != 0 && m_state != 0x48) {
            // The inner check is always true; the compiler emitted a redundant else
            if (m_state != 0) {
                FUN_00791a70(); // Some underlying function
                return;
            }
            // This branch is never reached
            FUN_00791a70();
            return;
        }
        // else: do nothing
    }
};

// Note: The constant 0x48 likely represents a specific state (e.g., kStateInactive, kStateExcluded).
//       The function is called when the state is active and not that excluded value.
//       FUN_00791a70 is presumably a shared routine (e.g., trigger, cleanup, or state transition).