// FUNC_NAME: ResourceManager::shutdown
// Function at 0x00674eb0: Releases three resource handles (stored at +0x180->+0x78, +0x50, +0x54)
// belonging to a container structure (at +0x4) and deregisters this instance from a global
// table of up to 2 instances. Typical EA EARS engine resource cleanup with ref-counted handles.

#include <cstdint>

// Global variables (external definitions)
extern void* DAT_01206694;          // Function pointer to memory deallocator (like operator delete)
extern uint8_t DAT_012058ba;        // Global shutdown/initialization flag
extern void* DAT_012066a4[2];       // Global instance list (this object pointers)
extern int32_t DAT_012066ac[2];     // Global instance flags (0 = inactive)

// Internal helper functions (callees)
void releaseSharedResources(int32_t stage);   // FUN_00673ad0 - stage 2 indicates full shutdown
void clearResourceList();                     // FUN_00673210
void finalizeCleanup();                       // FUN_00672fd0

// Custom memory deallocation function pointer type
typedef void (*FreeFunc)(void*);
static FreeFunc pfnFree = reinterpret_cast<FreeFunc>(&DAT_01206694);

class ResourceManager {
public:
    void __thiscall shutdown();
};

void __thiscall ResourceManager::shutdown() {
    // Step 1: Begin shutdown process with stage 2
    releaseSharedResources(2);

    // ----- Release first handle (nested at this+0x180, then +0x78) -----
    int32_t* pResource = reinterpret_cast<int32_t*>(
        *reinterpret_cast<int32_t*>(
            *reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(this) + 0x180) + 0x78
        )
    );
    int32_t* pContainer = *reinterpret_cast<int32_t**>(reinterpret_cast<uint8_t*>(this) + 0x4);

    if (pResource != nullptr) {
        // The handle stores its own index at offset -8 from the resource data
        int32_t index = pResource[-2];  // *(int*)(pResource - 8)

        // Remove from container's array (+0xc points to an array of pointers)
        int32_t* arrayBase = *reinterpret_cast<int32_t**>(reinterpret_cast<uint8_t*>(pContainer) + 0xc);
        arrayBase[index] = 0;

        // Decrement container reference count (at container+0x4)
        int32_t* refCount = reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(pContainer) + 0x4);
        (*refCount)--;

        // Free the allocation (actual block starts 0x10 bytes before the handle)
        pfnFree(reinterpret_cast<uint8_t*>(pResource) - 0x10);
    }

    // Clear the pointer in the nested structure
    int32_t* nestedPtr = reinterpret_cast<int32_t*>(*reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(this) + 0x180) + 0x78);
    nestedPtr = nullptr;

    // ----- Release second handle (at this+0x50) -----
    pResource = reinterpret_cast<int32_t*>(*reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(this) + 0x50));
    pContainer = *reinterpret_cast<int32_t**>(reinterpret_cast<uint8_t*>(this) + 0x4);

    if (pResource != nullptr) {
        int32_t index = pResource[-2];
        int32_t* arrayBase = *reinterpret_cast<int32_t**>(reinterpret_cast<uint8_t*>(pContainer) + 0xc);
        arrayBase[index] = 0;

        int32_t* refCount = reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(pContainer) + 0x4);
        (*refCount)--;

        pfnFree(reinterpret_cast<uint8_t*>(pResource) - 0x10);
    }
    *reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(this) + 0x50) = 0;

    // ----- Release third handle (at this+0x54) -----
    pResource = reinterpret_cast<int32_t*>(*reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(this) + 0x54));
    pContainer = *reinterpret_cast<int32_t**>(reinterpret_cast<uint8_t*>(this) + 0x4);

    if (pResource != nullptr) {
        int32_t index = pResource[-2];
        int32_t* arrayBase = *reinterpret_cast<int32_t**>(reinterpret_cast<uint8_t*>(pContainer) + 0xc);
        arrayBase[index] = 0;

        int32_t* refCount = reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(pContainer) + 0x4);
        (*refCount)--;

        pfnFree(reinterpret_cast<uint8_t*>(pResource) - 0x10);
    }
    *reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(this) + 0x54) = 0;

    // Step 2: Additional cleanup
    clearResourceList();
    finalizeCleanup();

    // Step 3: Clear global shutdown flag
    DAT_012058ba = 0;

    // Step 4: Remove this instance from the global instance table (2 slots)
    for (uint32_t i = 0; i < 2; ++i) {
        if (DAT_012066a4[i] == this) {
            DAT_012066ac[i] = 0;
            return;
        }
    }
}