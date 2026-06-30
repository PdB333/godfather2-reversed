// FUNC_NAME: EntityManager::getObjectByIndex
// Function address: 0x00558b00
// Role: Retrieves a pointer to an object (size 0x70) by index, with overflow handling.
// The object array has a 0x48-byte header before the first element.
// Primary array info is stored at this+0x04 (pointer to a struct with base and count).
// Overflow array is accessed via this+0x1c if non-null, else a global fallback.

struct ObjectArrayInfo {
    int baseAddress; // +0x00: base pointer of the primary object array
    int count;       // +0x04: number of elements in the primary array
};

struct OverflowManager {
    int field_0x00[4]; // +0x00..0x0C: unknown
    int* somePointer;  // +0x10: pointer to a struct containing overflow array base
};

struct OverflowArrayInfo {
    int field_0x00[12]; // +0x00..0x2C: unknown
    int baseAddress;    // +0x30: base pointer of the overflow object array
};

// Global fallback base pointer (likely set during initialization)
extern int* g_globalObjectArrayBase; // *piRam00000030

int __thiscall EntityManager::getObjectByIndex(int this, int index) {
    ObjectArrayInfo* arrayInfo = *(ObjectArrayInfo**)(this + 0x4);
    int primaryCount = arrayInfo->count;
    int relativeIndex = index - primaryCount;

    if (relativeIndex < 0) {
        // Index is within the primary array
        return arrayInfo->baseAddress + 0x48 + index * 0x70;
    }

    // Index is beyond primary array; try overflow
    int* overflowManagerPtr = *(int**)(this + 0x1c);
    if (overflowManagerPtr != nullptr) {
        OverflowManager* overflowMgr = (OverflowManager*)overflowManagerPtr;
        OverflowArrayInfo* overflowInfo = *(OverflowArrayInfo**)(overflowMgr->somePointer + 0x10);
        int overflowBase = overflowInfo->baseAddress;
        return overflowBase + 0x48 + relativeIndex * 0x70;
    }

    // Fallback to global array
    int globalBase = *g_globalObjectArrayBase;
    return globalBase + 0x48 + relativeIndex * 0x70;
}