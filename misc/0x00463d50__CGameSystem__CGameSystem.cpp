// FUNC_NAME: CGameSystem::CGameSystem

class CGameSystem {
public:
    // Constructor: initializes the singleton system with a factory object
    // param_2: pointer to an interface (vtable) that provides a creation method at offset +8
    // This function is the constructor for the global game system (singleton registered at DAT_01223460)
    CGameSystem(void* pFactory) {
        // Base class initialization (field_4 = 0, field_8 = initial data)
        // Note: The decompilation shows two writes to the same field (offset 8).
        // The first is from the base class constructor, then overwritten below.
        field_4 = 0;
        field_8 = &PTR_LAB_00e31e68; // Base class initialization (overwritten below)

        // Register this instance as the global singleton
        g_pGameSystem = this; // DAT_01223460 = param_1

        // Set vtable pointer (first member)
        vtable = &PTR_FUN_00e31e58;

        // Override base class pointer with derived class data
        field_8 = &PTR_LAB_00e31e64;

        // Store factory pointer
        field_C = pFactory;

        // Call the factory's method at vtable offset 8 (index 2, assuming 4-byte entries)
        // This likely performs some engine-level initialization using the factory
        (**(void (__thiscall**)(void*))(*(unsigned int*)pFactory + 8))();

        // Additional initialization: register something with a global reference table
        FUN_0049c6e0(&PTR_DAT_00e31e54, 1);
    }

private:
    void* vtable;                // +0x00: virtual function table pointer
    int field_4;                 // +0x04: initialized to 0 (base class flag?)
    void* field_8;               // +0x08: pointer to static data or interface (overwritten)
    void* field_C;               // +0x0C: stored factory argument (param_2)
};

// Global singleton pointer (set during construction)
CGameSystem* g_pGameSystem; // DAT_01223460

// External functions and data references used
extern void PTR_LAB_00e31e68[];  // Base class data table
extern void PTR_LAB_00e31e64[];  // Derived class data table
extern void PTR_FUN_00e31e58[];  // VTBL for CGameSystem
extern void PTR_DAT_00e31e54;    // Global data reference for initialization
void FUN_0049c6e0(void* param1, int param2); // Engine initialization helper