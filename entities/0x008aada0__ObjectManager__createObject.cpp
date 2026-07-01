// FUNC_NAME: ObjectManager::createObject

#include <cstdint>

// Forward declarations for helper functions
bool isSystemReady();                          // FUN_00481660 - checks if system is initialized
void* allocateMemory(uint32_t size);           // FUN_009c8e50 - memory allocation (size 0x40 = 64 bytes)
void* initializeObject(void* memory);          // FUN_008aac50 - constructs/initializes object at given memory
void registerObject(void* object);             // FUN_00481690 - registers object with manager

// Global fallback pointer (used when allocation fails)
static void* g_fallbackObject = nullptr;       // _DAT_00000038

void __thiscall ObjectManager::createObject(void* param_2) {
    if (isSystemReady()) {
        void* obj = allocateMemory(0x40);
        if (obj != nullptr) {
            // Initialize the object using the manager's this pointer
            obj = initializeObject(this);
            // Store the second parameter at offset +0x38
            *(uint32_t*)((uint8_t*)obj + 0x38) = (uint32_t)param_2;
            registerObject(obj);
            return;
        }
        // Allocation failed: store param_2 in global fallback and register null
        g_fallbackObject = param_2;
        registerObject(nullptr);
    }
}