// FUNC_ADDR: 0x0079e5e0
// FUNC_NAME: InputController::updateInputFromFlags

// Reconstructed C++ for debug function that checks boolean flags and calls a virtual method to set corresponding input action flags.
// Offsets and virtual table index based on Ghidra decompilation.

#include <cstdint>

// Forward declaration of a function that checks if input processing is active (e.g., game not paused)
bool isInputProcessingActive(); // Address 0x00481620

class InputController {
public:
    // Virtual table pointer at +0x00 (implicit)
    // Member fields (offsets relative to this):

    // +0x58: Pointer to an object that has a virtual function at +0x28 (i.e., vtable[10])
    // This object is likely an internal input state aggregator.
    void* m_inputStateObject; // offset 0x58

    // Many boolean flags controlling which actions are mapped to logical inputs.
    // These appear to be set by some other logic (e.g., context-dependent input mapping).

    bool m_flagAction200;   // offset 0x26cc
    bool m_flagAction400;   // offset 0x26b4
    bool m_flagAction800;   // offset 0x26a8
    bool m_flagAction1000;  // offset 0x26c0
    bool m_flagAction2000;  // offset 0x274c
    bool m_flagAction4000;  // offset 0x24e0

    // Global input enabled flag accessed via DAT_0112991c + 0x10 (considered here as a static bool)
    static bool s_globalInputEnabled; // Approx at DAT_0112991c + 0x10

    // The virtual function in m_inputStateObject at vtable offset 0x28
    // It takes a uint32 flag value and likely sets an action.
    typedef void (__thiscall *SetActionFunc)(void* self, uint32_t flag);
    SetActionFunc getSetActionFunc() const {
        // Get vtable from m_inputStateObject
        void** vtable = *(void***)m_inputStateObject;
        // Offset 0x28 = 10th function pointer (since 0x28/4 = 10)
        return (SetActionFunc)(vtable[0x28 / 4]);
    }

    // Main update function
    void updateInputFromFlags() {
        if (!isInputProcessingActive()) {
            return;
        }

        SetActionFunc setAction = getSetActionFunc();

        // Check each boolean flag and forward the corresponding action mask
        if (m_flagAction200) {
            setAction(m_inputStateObject, 0x200);
        }
        if (m_flagAction400) {
            setAction(m_inputStateObject, 0x400);
        }
        if (m_flagAction800) {
            setAction(m_inputStateObject, 0x800);
        }
        if (m_flagAction1000) {
            setAction(m_inputStateObject, 0x1000);
        }
        if (m_flagAction2000) {
            setAction(m_inputStateObject, 0x2000);
        }
        if (m_flagAction4000) {
            setAction(m_inputStateObject, 0x4000);
        }
        // Global input flag (likely controller disconnected or something)
        if (s_globalInputEnabled) {
            setAction(m_inputStateObject, 0x8000);
        }
    }
};

// Stub for the external function – actual implementation likely checks game state.
bool isInputProcessingActive() {
    // In the real game, this probably returns whether the user is actively playing (not in menus, etc.)
    return true; // placeholder
}