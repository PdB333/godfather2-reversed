// FUNC_NAME: ResourceManager::releaseResource

#include <cstdint>

// --- Forward Declarations ---
struct ResourceEntry;
struct ResourceObject; // Unknown internal type
int32_t ResourceObject_Destroy(ResourceObject* obj); // FUN_0049d7a0
void   ResourceEntry_Free(ResourceEntry* entry);     // FUN_004d2640
void   ResourceManager_ProcessDeferred();            // FUN_004d20d0

// --- Global Data (from game binary) ---
// Hash table: 0x2000 entries, each entry is a pointer to a ResourceEntry
extern ResourceEntry* g_resourceHashTable[0x2000]; // DAT_012054ac

// VTable of some default resource object class (used to call destructor)
extern void** g_defaultResourceVTable; // DAT_01205868

// Deferred release queue structure (at DAT_012068e8 + 0x14)
struct DeferredReleaseQueue {
    // +0x00: base of pre‑allocated buffer? Usually a pointer to a label.
    // +0x14: current write pointer (offset by 4 each push)
    uint32_t* writePtr; // at base + 0x14
};
extern DeferredReleaseQueue g_deferredQueue; // DAT_012068e8

// --- Resource Entry Structure ---
struct ResourceEntry {
    int32_t   refCount;     // +0x00
    int32_t   pendingLock;  // +0x04 (atomic lock for pending release)
    ResourceObject* object; // +0x08
    uint32_t  handle;       // +0x0C
    ResourceEntry* next;    // +0x10 (collision chain in hash table)
};

// --- Helper: LOCK / UNLOCK macros (assumed platform specific) ---
// In the original binary these are inline asm implementing a mutex.
#define LOCK()   /* platform specific acquire */
#define UNLOCK() /* platform specific release */

// --- Function Implementation ---
int32_t __cdecl ResourceManager::releaseResource(uint32_t handle)
{
    ResourceEntry* entry;
    int32_t result;

    // Hash into global table
    entry = g_resourceHashTable[handle & 0x1FFF];

    if (entry != nullptr) {
        // Walk collision chain to find exact match
        while (entry->handle != handle) {
            entry = entry->next;
            if (entry == nullptr) {
                return -1; // Not found
            }
        }

        // Entry found
        if (entry != nullptr) {
            // Check if we are on the main thread (FS segment +0x2C -> thread info, +0x34 flags)
            // If the main thread flag is zero, we can free immediately.
            bool isMainThread = (*(int32_t*)(**(int32_t**)(__readfsdword(0x2C) + 0x34)) == 0);

            if (isMainThread) {
                // Main thread: decrement reference count
                LOCK();
                result = entry->refCount;
                entry->refCount = entry->refCount - 1;
                UNLOCK();
                result = result - 1;

                if (result == 0) {
                    // No more references: destroy the resource object
                    ResourceObject* obj = entry->object;
                    ResourceObject_Destroy(obj);

                    // Call virtual destructor (offset 0x04 in vtable)
                    void** vtable = *reinterpret_cast<void***>(g_defaultResourceVTable);
                    reinterpret_cast<void(*)(ResourceObject*, int32_t)>(vtable[1])(obj, 0);

                    // Free the entry from hash table
                    ResourceEntry_Free(entry);

                    // Process any pending deferred releases
                    ResourceManager_ProcessDeferred();

                    result = 0;
                }
                return result;
            }
            else {
                // Not main thread: queue the release for later processing
                LOCK();
                result = entry->pendingLock;
                entry->pendingLock = entry->pendingLock + 1;
                UNLOCK();

                if (result == 0) {
                    // First pending reference: push handle to deferred queue
                    uint32_t* writePtr = &g_deferredQueue.writePtr;
                    *writePtr = reinterpret_cast<uint32_t>(&g_deferredQueue.writePtr); // tricky initialization
                    writePtr[0] = writePtr[0] + 4; // advance by 4
                    *reinterpret_cast<uint32_t*>(writePtr[0]) = handle;
                    writePtr[0] = writePtr[0] + 4; // advance by 4 again
                }

                return entry->refCount;
            }
        }
    }

    return -1;
}