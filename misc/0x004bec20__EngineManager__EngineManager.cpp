// FUNC_NAME: EngineManager::EngineManager
// Address: 0x004bec20
// Role: Constructor for the main engine manager class, initializes vtable pointers and core subsystems.

class EngineManager {
public:
    void** vtable;        // +0x00
    void** vtable2;       // +0x0C
    void** vtable3;       // +0x10
    // ... other members
};

// Global subsystem instances (size unknown, but assumed constructed elsewhere)
extern uint32_t g_memoryManager;    // DAT_01206940
extern uint32_t g_resourceManager;  // DAT_01218050

// Forward declarations of subsystem initialization functions
void __cdecl memoryManagerInit(uint32_t* mgr);   // FUN_004086d0
void __cdecl resourceManagerInit(uint32_t* mgr); // FUN_00408310
void __cdecl audioSystemInit();                  // FUN_005667d0
void __cdecl inputSystemInit();                  // FUN_004083d0

// Vtable pointers (addresses of global function pointer arrays)
extern void* PTR_FUN_00e35c7c;   // first vtable entry
extern void* PTR_FUN_00e35c90;   // second vtable entry at +0x0C
extern void* PTR_LAB_00e35d28;   // third vtable entry at +0x10

void __fastcall EngineManager::EngineManager(void* thisPtr) {
    uint32_t* obj = (uint32_t*)thisPtr;

    // Set up virtual function tables (multiple inheritance)
    obj[0] = (uint32_t)&PTR_FUN_00e35c7c;   // primary vtable
    obj[3] = (uint32_t)&PTR_FUN_00e35c90;   // secondary vtable
    obj[4] = (uint32_t)&PTR_LAB_00e35d28;   // tertiary vtable

    // Initialize core engine subsystems
    memoryManagerInit(&g_memoryManager);   // init memory pool
    resourceManagerInit(&g_resourceManager); // init resource cache
    audioSystemInit();                     // init audio engine
    inputSystemInit();                     // init input system
}