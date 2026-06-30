// FUNC_NAME: RefCounted::setupSecondary
// Address: 0x005d9fb0
// Purpose: Initialize secondary reference with optional object, calling virtual lifecycle methods.
// The object (this) has a vtable at offset 0 and a 32-bit field at offset 4 (m_pSecondary).
// Virtual method indices: vtable[1] (offset 4), vtable[2] (offset 8), vtable[3] (offset 12).

class RefCounted {
public:
    // Virtual table layout:
    // vtable[0]: unknown
    // vtable[1]: (offset 4) called with (param2, 0) during setup
    // vtable[2]: (offset 8) called first during setup
    // vtable[3]: (offset 12) called last during setup
    virtual void onPreAttach() = 0;      // vtable[2] - called at start
    virtual void onAttach(int param, int zero) = 0; // vtable[1] - if param != 0
    virtual void onPostAttach() = 0;     // vtable[3] - called at end

    // Offset 0x04: pointer to secondary object or data (m_pSecondary)
    int* m_pSecondary; 
};

// External helper: creates/obtains a secondary reference
int* __stdcall AcquireSecondaryReference(int* obj, int* thisPtr); // Address 0x004265d0

void __thiscall RefCounted::setupSecondary(int* param2) {
    // Call virtual lifecycle method: pre-attach
    this->onPreAttach();

    if (param2 != nullptr) {
        // Acquire a secondary reference object using the helper
        int* secondary = AcquireSecondaryReference(param2, this); // Returns a pointer
        this->m_pSecondary = secondary;

        // Call virtual method: attach with param2 and zero
        this->onAttach(param2, 0);
    } else {
        // No secondary object: clear field
        this->m_pSecondary = nullptr;
    }

    // Post-attach lifecycle
    this->onPostAttach();
}