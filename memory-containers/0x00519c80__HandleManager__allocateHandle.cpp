// FUNC_NAME: HandleManager::allocateHandle

#include <windows.h>

// Global handle manager singleton
extern HandleManager* g_handleManager; // DAT_0120541c

// Base address for handle offsets
extern int g_handleBase; // DAT_01205410

// Some constant type ID or version
extern int g_handleTypeId; // DAT_00e2b1a4

// Handle structure returned to caller
struct Handle {
    int index;   // +0x00
    int flags;   // +0x04
};

// Per-thread handle table entry (size 0x34 = 52 bytes)
struct HandleEntry {
    int field0;      // +0x00
    int field4;      // +0x04
    int field8;      // +0x08
    int fieldC;      // +0x0C
    int field10;     // +0x10
    int field14;     // +0x14
    int field18;     // +0x18
    int field1C;     // +0x1C
    int field20;     // +0x20
    int field24;     // +0x24
    int typeId1;     // +0x28
    int typeId2;     // +0x2C
    int field30;     // +0x30
};

// Manager structure (partial)
struct HandleManager {
    // ... other fields ...
    CRITICAL_SECTION* criticalSection; // +0x1B8
    // ... other fields ...
    int fallbackHandle; // +0x17C (used when allocation fails)
};

// Allocation function (size 0x34)
void* __cdecl allocateMemory(int size); // FUN_00649040

// Constructor/initializer for HandleEntry
void __cdecl initializeHandleEntry(void* entry); // FUN_006492f0

void HandleManager::allocateHandle(Handle* outHandle)
{
    HandleManager* manager = g_handleManager;
    CRITICAL_SECTION* cs = manager->criticalSection;
    int handleIndex = 0;

    if (cs != nullptr) {
        EnterCriticalSection(cs);
    }

    // Attempt to allocate a new handle entry
    HandleEntry* entry = (HandleEntry*)allocateMemory(0x34);
    if (entry == nullptr) {
        // Allocation failed, use fallback handle from manager
        if (cs != nullptr) {
            LeaveCriticalSection(cs);
        }
        handleIndex = manager->fallbackHandle;
    } else {
        // Initialize the new entry
        initializeHandleEntry(entry);
        handleIndex = entry->field8; // Some index stored at offset 8

        if (cs != nullptr) {
            LeaveCriticalSection(cs);
        }
    }

    // Get per-thread handle table pointer from TLS (FS:[0x2C])
    int* tlsArray = *(int**)(__readfsdword(0x2C));
    int* handleTable = *(int**)(tlsArray[0] + 8); // Dereference TLS slot 0 + 8

    if (handleIndex != 0) {
        int offset = handleIndex - g_handleBase;
        HandleEntry* slot = (HandleEntry*)(handleTable + offset);

        if (slot != nullptr) {
            // Zero out the slot (12 dwords = 48 bytes)
            slot->field0 = 0;
            slot->field4 = 0;
            slot->field8 = 0;
            slot->fieldC = 0;
            slot->field10 = 0;
            slot->field14 = 0;
            slot->field18 = 0;
            slot->field1C = 0;
            slot->field20 = 0;
            slot->field24 = 0;
            slot->field28 = 0;
            slot->field2C = 0;
            slot->field30 = 0;

            // Set type ID fields
            slot->typeId1 = g_handleTypeId;
            slot->typeId2 = g_handleTypeId;
        }
    }

    // Fill output handle structure
    outHandle->index = handleIndex;
    outHandle->flags = 1;
}