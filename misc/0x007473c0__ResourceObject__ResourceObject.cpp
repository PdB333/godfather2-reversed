// FUNC_NAME: ResourceObject::ResourceObject
// Constructor for a ResourceObject class (vtable at 0x00d6402c).
// Initializes a resource handle from a manager and attaches a memory buffer.
// Offsets: +0x00 vtable, +0x48 bufferPointerOrSize, +0x50 bufferData, +0x54 field1, +0x58 field2, +0x5c resourceHandle, +0x6c byteFlag

#include <cstdint>

class ResourceObject {
public:
    void* vtable; // +0x00

    // Constructor taking two arguments that are passed to base class initialization.
    ResourceObject(int arg1, int arg2) {
        // Call base class constructor FUN_004ac120 (likely BaseObject::init)
        BaseObjectInit(arg1, arg2); // FUN_004ac120

        // Set vtable pointer
        vtable = (void*)0x00d6402c; // PT1

        // Pointer or size at offset 0x48 (param_1[0x12])
        void* bufferOrSize = *(void**)((uint8_t*)this + 0x48);
        if (bufferOrSize == nullptr) {
            // No buffer, clear everything
            *(void**)((uint8_t*)this + 0x50) = nullptr; // param_1[0x14]
        } else {
            // Subtract header size 0x48 to get actual data pointer
            *(void**)((uint8_t*)this + 0x50) = (void*)((uint8_t*)bufferOrSize - 0x48);
        }
        *(int*)((uint8_t*)this + 0x54) = 0; // param_1[0x15]
        *(int*)((uint8_t*)this + 0x58) = 0; // param_1[0x16]

        // If buffer data pointer is non-null, acquire a resource from the global manager
        if (*(void**)((uint8_t*)this + 0x50) != nullptr) {
            // FUN_0043b870: Probably ResourceManager::acquire or create
            *(void**)((uint8_t*)this + 0x5c) = GlobalResourceManager::acquire((void*)0x0112af58); // DAT_0112af58
        } else {
            *(void**)((uint8_t*)this + 0x5c) = nullptr;
        }
        // Clear byte flag at offset 0x6c (low byte of element at index 0x1b)
        *(uint8_t*)((uint8_t*)this + 0x6c) = 0;
    }

private:
    // Forward declaration of base class init
    void BaseObjectInit(int, int);
};

// Global resource manager (DAT_0112af58)
extern void* g_ResourceManager; // 0x0112af58

// Helper function that acquires a resource (likely from a manager)
void* GlobalResourceManager::acquire(void* manager); // FUN_0043b870