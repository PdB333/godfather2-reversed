// FUNC_NAME: SomeClass::~SomeClass (at 0x005686c0)
// Destructor for a class with a vtable pointer and a field at offset +0xC.
// Sets vtable to a specific derived vtable, calls an internal destructor helper,
// then resets vtable to base vtable and clears a global pointer.

// Global pointer to instance (likely a singleton, reset to 0 upon destruction)
static SomeClass* g_pSomeSingleton; // DAT_012234e0

// Derived vtable pointer (PTR_FUN_00e3aa80)
extern void* VtableSomeClassDerived;

// Base vtable pointer (PTR_LAB_00e3aad0)
extern void* VtableSomeClassBase;

// Internal destructor helper (likely performs actual cleanup)
void __fastcall callDestructorInternal(void); // FUN_00568740

class SomeClass {
public:
    void* vtable; // +0x00 vtable pointer

    // +0x04 ... (other fields)
    // +0x0C field that is checked for non-zero before calling destructor internal
    int m_fieldAt0xC;

    // Constructor would set vtable appropriately

    // Destructor
    void __fastcall ~SomeClass() {
        // Set vtable to derived class vtable (first, in case destructor is overridden)
        this->vtable = &VtableSomeClassDerived;

        // If field at +0x0C is non-zero, perform internal destruction
        if (this->m_fieldAt0xC != 0) {
            callDestructorInternal();
        }

        // Reset vtable to base class vtable (for possible inheritance chain)
        this->vtable = &VtableSomeClassBase;

        // Clear global singleton pointer
        g_pSomeSingleton = 0;
    }
};