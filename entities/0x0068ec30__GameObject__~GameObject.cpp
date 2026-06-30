// FUNC_NAME: GameObject::~GameObject
// Destructor at 0x0068ec30 - Calls global manager release, switches vtable, and resets instance counter
class GameObject {
public:
    void** vtable; // +0x00

    // __thiscall (this in ECX)
    void __thiscall destructor() {
        // Set initial vtable (likely derived class vtable)
        this->vtable = &g_vtable_phase1; // PTR_FUN_00d5c8d4

        // If a global manager exists, call its first virtual method with argument 1 (e.g., release or decrement)
        if (g_pGlobalManager != nullptr) {
            // Manager's vtable entry 0 is called (interpretation varies)
            auto managerVtable = *reinterpret_cast<void***>(g_pGlobalManager);
            auto managerFunc = reinterpret_cast<void(__thiscall*)(void*, int32_t)>(managerVtable[0]);
            managerFunc(g_pGlobalManager, 1);
        }

        // Switch to final vtable (likely base class vtable or stub to prevent further calls)
        this->vtable = &g_vtable_phase2; // PTR_LAB_00d5c858

        // Reset global object counter to zero
        g_nObjectCounter = 0; // DAT_011299d0
    }
};

// Global variables (inferred from binary)
extern void* g_pGlobalManager; // DAT_01129bb4 (pointer to singleton manager)
extern int32_t g_nObjectCounter; // DAT_011299d0 (instance count)
extern void* g_vtable_phase1; // PTR_FUN_00d5c8d4
extern void* g_vtable_phase2; // PTR_LAB_00d5c858