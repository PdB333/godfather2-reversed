// FUNC_NAME: GameManager::registerModule

// Registers a module system (size 0xF0) using hash constants and a unique module ID.
// The module is identified by the constants 0x38703377 and 0x6333C951.
// The function allocates memory, initializes the module, sets its name/tag,
// and finalizes registration in the game manager context.

#include <cstdint>

// Assuming these are in-scope helper functions (from Ghidra analysis):
void debugScopeEnter(uint32_t lineNum, uint32_t contextOffset);  // +0x80 +0x20 in this
void debugScopeExit();
void formatAndAllocateString(void* pool, char* buffer, char** outAllocated, const char* fmt, ...);
void* allocateMemory(uint32_t size);           // operator new / malloc
void initializeModule(void* module, int zero); // constructor-like (0xF0 size object)
void setModuleName(void* module, const char* name);
void finalizeModuleRegistration();

// Extern data (from global references)
extern void* g_globalStringPool;               // DAT_012234a4
extern const char* g_defaultModuleName;         // DAT_0120546e
extern void s_moduleHandlerFunction();          // LAB_0096a4e0 (handler address)

void __fastcall GameManager::registerModule()
{
    // Begin profiling/debug scope with line number and context pointer offset
    debugScopeEnter(0x6A, *(uint32_t*)(this + 0x80) + 0x20);

    char buffer[4112];                    // Stack buffer for formatted name
    char* allocatedName = nullptr;        // Heap-allocated copy of formatted name
    uint32_t nameSize = 0;                // Unused output from format function
    uint32_t nameHash = 0;                // Unused output from format function
    void (*nameCleanup)(void*) = nullptr; // Cleanup function for the allocated string

    // Format the module tag using a unique ID: "{#467}" (0x1BED1520 = 467)
    formatAndAllocateString(g_globalStringPool, buffer, &allocatedName, "{#%u}", 0x1BED1520);

    // Allocate the module object (size 0xF0 = 240 bytes)
    void* module = allocateMemory(0xF0);
    if (module != nullptr)
    {
        // Initialize the module (constructor call with argument 0)
        initializeModule(module, 0);
    }

    // Use default module name if allocation failed
    const char* moduleName = (allocatedName != nullptr) ? allocatedName : g_defaultModuleName;

    // Associate the name with the module
    setModuleName(module, moduleName);

    // Set module type and identifier fields
    *(uint32_t*)((uintptr_t)module + 0x0C) = 2;           // +0x0C: Module type indicator
    *(uint32_t*)((uintptr_t)module + 0x20) = 0x38703377;  // +0x20: Magic hash 1
    *(uint32_t*)((uintptr_t)module + 0x1C) = 0x6333C951;  // +0x1C: Magic hash 2
    *(void**)((uintptr_t)module + 0x14)  = &s_moduleHandlerFunction; // +0x14: Handler function pointer

    // Finalize registration (e.g., add to global list)
    finalizeModuleRegistration();

    // Free the heap-allocated string if present
    if (nameCleanup != nullptr && allocatedName != nullptr)
    {
        nameCleanup(allocatedName);
    }

    // End profiling/debug scope
    debugScopeExit();
}