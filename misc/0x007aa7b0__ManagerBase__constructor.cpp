// FUNC_NAME: ManagerBase::constructor

// Reconstructed constructor for a base manager class (EA EARS engine, The Godfather 2).
// Address: 0x007aa7b0
// Sets vtable pointers, calls initialization routines, and handles allocation flag.

class ManagerBase {
public:
    // Vtable pointer at offset 0x00
    void* vtable;
    // Unknown members...
    // At offset 0x0C: pointer to another vtable (likely for derived interface)
    void* secondaryVtable;

    ManagerBase(void* memory, byte allocFlag) __thiscall {
        // Set primary vtable (base class)
        this->vtable = (void*)0x00d6b92c; // PTR_FUN_00d6b92c

        // Set secondary vtable (first assignment, possibly base of another class)
        this->secondaryVtable = (void*)0x00d6b928; // PTR_LAB_00d6b928

        // Initialize global structure at DAT_01206940
        // This likely sets up a singleton or shared state.
        FUN_004086d0(&DAT_01206940); // g_someGlobal

        // Update secondary vtable (final assignment, possibly after initialization)
        this->secondaryVtable = (void*)0x00d6b924; // PTR_LAB_00d6b924

        // Zero a global flag/counter
        DAT_01129954 = 0; // g_someFlag

        // Post-initialization (no arguments)
        FUN_004083d0(); // postInit()

        // If the allocation flag (bit 0) is set, call cleanup/destruction function
        // Note: This does NOT delete 'this'; it likely performs additional setup
        // or handles memory ownership. It returns 'this' regardless.
        if (allocFlag & 1) {
            FUN_009c8eb0(this); // handleAllocFlagCleanup
        }

        return this;
    }
};