// FUN_0047f2b0: EarsObject::Construct
// Custom placement constructor for EARS objects.
// Initializes memory at `this` and optionally calls virtual destructor (index 1) with deleteFlag=0 when flags & 1.
// Returns the constructed object pointer.

class EarsObject {
public:
    // Custom constructor that takes a memory address and initialization flags.
    // flags & 0x01: after initialization, call the destructor (likely for reconstruction).
    static EarsObject* Construct(void* memory, byte flags);

private:
    // Internal initializer (no arguments) – called first.
    static void Initialize(); // FUN_0047f2e0

    // VTable function type (__thiscall with an int parameter).
    typedef void (__thiscall *VTableMethod)(void*, int);

    // Retrieves the static vtable pointer from the engine globals.
    // Offset 0x2d4 into the global structure (g_pEngine) is a pointer to the vtable.
    static VTableMethod* GetVTable() {
        extern int* g_pEngine; // DAT_01223410
        return *(VTableMethod**)(g_pEngine + 0x2d4); // vtable array
    }
};

// Implementation
EarsObject* EarsObject::Construct(void* memory, byte flags) {
    // Step 1: Base initialization (e.g., zeroing fields, setting defaults)
    Initialize();

    // Step 2: If flag bit0 is set, invoke the virtual destructor (index 1)
    // with deleteFlag = 0 (destruct only, no operator delete call).
    if (flags & 1) {
        VTableMethod* vtable = GetVTable();
        vtable[1](memory, 0); // This calls the virtual destructor on the already‑initialized object
    }

    return static_cast<EarsObject*>(memory);
}