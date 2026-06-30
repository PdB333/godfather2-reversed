// FUNC_NAME: EARSBase::EARSBase (constructor at 0x004c26c0)
// Sets up vtable pointer and calls base initialization

class EARSBase {
public:
    // +0x00: vtable pointer
    void* m_vtable;

    // Constructor
    __thiscall EARSBase() {
        // Set vtable to this class's vtable
        m_vtable = &PTR_FUN_00e361ec;

        // Perform base class initialization (e.g., zero fields, set defaults)
        // FUN_004c2840 is likely "BaseInit" (pure virtual or default init)
        BaseInit();
    }

    virtual void BaseInit(); // defined elsewhere at 0x004c2840
};