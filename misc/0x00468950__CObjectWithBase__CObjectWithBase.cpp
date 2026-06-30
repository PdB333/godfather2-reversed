// FUNC_NAME: CObjectWithBase::CObjectWithBase

// Constructor for a class with two vtable pointers (derived at +0x00, base at +0x04)
// Sets up vtable pointers, initializes base subobject, resets global flag,
// and conditionally calls a registration/finalization function.
// Address: 0x00468950

// Global flag reset during construction (address 0x01223474)
static int g_bSomeFlag = 0;

// Forward declarations of external functions
void __thiscall baseObjectInitialize(void *this);
void __thiscall registerWithManager(void *this);

// Vtables (external symbols)
extern void *g_vtableDerivedTemp;    // PTR_FUN_00e32028
extern void *g_vtableBaseTemp;       // PTR_LAB_00e32034
extern void *g_vtableBaseFinal;      // PTR_LAB_00e32038
extern void *g_vtableDerivedFinal;   // PTR_LAB_00e30ea0

// Class definition (assumed layout)
class CObjectWithBase {
public:
    // +0x00: vtable pointer for derived class (final vtable: g_vtableDerivedFinal)
    void *m_vtableDerived;

    // +0x04: vtable pointer for base class subobject (final vtable: g_vtableBaseFinal)
    void *m_vtableBase;

    // Constructor
    // @param shouldRegister - if bit 0 is set, calls registerWithManager(this) after construction
    void __thiscall constructor(byte shouldRegister) {
        // Set temporary vtables before base constructor
        m_vtableDerived = &g_vtableDerivedTemp;
        m_vtableBase = &g_vtableBaseTemp;

        // Call base class constructor (e.g., initializes base members)
        baseObjectInitialize(this);

        // Update base vtable to final derived override
        m_vtableBase = &g_vtableBaseFinal;

        // Reset a global flag (likely a singleton or state counter)
        g_bSomeFlag = 0;

        // Set derived vtable to its final value
        m_vtableDerived = &g_vtableDerivedFinal;

        // If object was heap-allocated or needs registration, call finalizer
        if ((shouldRegister & 1) != 0) {
            registerWithManager(this);
        }
    }
};