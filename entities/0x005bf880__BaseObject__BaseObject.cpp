// FUNC_NAME: BaseObject::BaseObject

#include <cstdint>

extern class MemoryManager* g_memoryManager; // DAT_012234ec
extern void* BASE_VTABLE;                   // PTR_FUN_00e3e78c
extern void* OWN_VTABLE;                    // PTR_LAB_00e3e74c

class BaseObject {
public:
    void* vtable;          // +0x00
    void* m_data;          // +0x04
    uint32_t m_field0x08;  // +0x08
    uint32_t m_field0x0C;  // +0x0C

    // Constructor with dynamic allocation flag
    __thiscall BaseObject(uint8_t isDynamicAllocation);
};

__thiscall BaseObject::BaseObject(uint8_t isDynamicAllocation) {
    // Set vtable to base class before calling base constructor
    this->vtable = &BASE_VTABLE;

    // Call base class constructor (sets m_data, etc.)
    FUN_005c0360();  // baseConstruct()

    // Initialize own member fields
    this->m_field0x0C = 0;
    this->m_field0x08 = 0;

    // Release any resource that the base constructor may have allocated
    if (this->m_data != nullptr) {
        // Use global memory manager to free the resource
        // (**(code **)(**(int **)(g_memoryManager + 4) + 4))(this->m_data, 0);
        g_memoryManager->free(this->m_data, 0);
        this->m_data = nullptr;
    }

    // Override vtable to own class vtable
    this->vtable = &OWN_VTABLE;

    // If dynamically allocated, perform a post-construction check
    if (isDynamicAllocation & 1) {
        // Call a function that may indicate construction failure (e.g., resource load)
        char result = FUN_005c43d0(this);  // postConstruct()
        if (result == 0) {
            // Construction failed – free the memory via the same manager
            // (**(code **)(**(int **)(g_memoryManager + 4) + 4))(this, 0);
            g_memoryManager->free(this, 0);
        }
    }
}