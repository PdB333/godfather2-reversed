// FUNC_NAME: ResourceManager::~ResourceManager

#include <cstdint>

// Forward declarations of internal helpers (from other modules)
void destroySubObject(void* obj);   // FUN_004086d0
void resetSubObject(void* obj);     // FUN_00408310
void freeMemory(void* ptr);         // FUN_004daf90
void finalizeCleanup();             // FUN_0046c640

// Global data (not defined here)
extern int32_t s_instanceCount;          // DAT_0112b9d0
extern int32_t g_someGlobal;             // DAT_0120e93c (assumed int)

// Sub-objects stored inline (size 8 bytes each, two dwords)
struct SubObject {
    // placeholder – exact fields unknown
    uint32_t data[2];
};

class ResourceManager {
public:
    // virtual function table at offset 0
    // +0x3C: pointer to static function table (offset 0xf * 4)
    // +0x48: another static pointer (offset 0x12 * 4)
    // +0x10C: pointer to allocated memory (offset 0x43 * 4)
    // Sub-objects are stored at various offsets (relative to this pointer base)
    
    // Destructor
    ~ResourceManager();
};

ResourceManager::~ResourceManager() {
    // Set vtable to base class vtable
    *reinterpret_cast<void**>(this) = &PTR_FUN_00d6bb10;  // static vtable pointer
    this->staticFuncTable1 = &PTR_LAB_00d6bb00;           // offset 0xf
    this->staticFuncTable2 = &PTR_LAB_00d6bafc;           // offset 0x12

    // Decrement reference count, clamp to 0
    s_instanceCount--;
    if (s_instanceCount < 0) {
        s_instanceCount = 0;
    }

    // Destroy and reset multiple sub-objects at various offsets
    // The pattern: destroySubObject then resetSubObject for each 8‑byte region
    // Offsets in dword indices: 0x15..0x3b step 2, 0x3e, 0x40, 0x49
    // Convert to byte offsets: multiply by sizeof(uint32_t) = 4
    // Indices 0x15..0x3b (21..59) step 2 → 20 elements
    for (int i = 0x15; i <= 0x3b; i += 2) {
        void* obj = reinterpret_cast<uint32_t*>(this) + i;
        destroySubObject(obj);
        resetSubObject(obj);
    }

    // Two additional sub‑objects at indices 0x3e and 0x40
    destroySubObject(reinterpret_cast<uint32_t*>(this) + 0x3e);
    resetSubObject(reinterpret_cast<uint32_t*>(this) + 0x3e);

    destroySubObject(reinterpret_cast<uint32_t*>(this) + 0x40);
    resetSubObject(reinterpret_cast<uint32_t*>(this) + 0x40);

    // One more at index 0x49
    destroySubObject(reinterpret_cast<uint32_t*>(this) + 0x49);
    resetSubObject(reinterpret_cast<uint32_t*>(this) + 0x49);

    // Destroy a global object (probably a shared resource)
    destroySubObject(&g_someGlobal);

    // Free an allocated block if present (offset 0x43 * 4 = 0x10C)
    uint32_t* allocPtr = reinterpret_cast<uint32_t*>(this) + 0x43;
    if (*allocPtr != 0) {
        freeMemory(allocPtr);
    }

    // Final cleanup
    finalizeCleanup();
}