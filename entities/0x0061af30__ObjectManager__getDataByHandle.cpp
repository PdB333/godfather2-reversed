//FUNC_NAME: ObjectManager::getDataByHandle
// Function address: 0x0061af30
// Role: Retrieves a 4-byte value from a data block associated with a handle.
// Uses a global pool of 0x38-byte entries indexed by handle (max 0x1000).
// Each entry has a pointer at +0x20 to a data block containing an array of 8-byte elements.
// Calls FUN_0061b210 to get an index into that array, then returns the first uint of the element.

#include <cstdint>

// Forward declaration of the helper function (address 0x0061b210)
// Returns an index into the data array, or -1 on failure.
int32_t getDataIndex(void* param);

// Global pool of object entries (size 0x38 each, max 0x1000)
// Defined elsewhere, likely in a manager singleton.
extern uint8_t g_objectPool[0x1000 * 0x38]; // DAT_011a0f38

// Structure of a pool entry (size 0x38)
struct ObjectPoolEntry {
    uint8_t unknown[0x20];   // +0x00 to +0x1F
    void* dataBlock;         // +0x20: pointer to a data block
    uint8_t unknown2[0x14];  // +0x24 to +0x37 (size 0x38 total)
};

// Structure of an element in the data block (size 8)
struct DataElement {
    uint32_t value;          // +0x00: first 4 bytes (returned)
    uint32_t extra;          // +0x04: next 4 bytes
};

// The data block structure (starting at offset 4 from the pointer)
struct DataBlock {
    uint32_t header;         // +0x00: possibly count or flags
    DataElement elements[1]; // +0x04: array of 8-byte elements (size varies)
};

// __fastcall or __thiscall? Using __fastcall convention for handle in ECX? 
// The decompiler shows in_EAX used, so we assume handle is passed in EAX.
// We'll use a static function with an explicit parameter.
uint32_t __fastcall getDataByHandle(uint32_t handle) {
    // Check handle validity
    if (handle >= 0x1000) {
        return 0; // or undefined (unaff_EDI)
    }

    // Calculate offset into global pool
    uint32_t entryOffset = handle * 0x38;
    ObjectPoolEntry* entry = reinterpret_cast<ObjectPoolEntry*>(&g_objectPool[entryOffset]);

    // Check if entry is valid (non-zero)
    if (entry->dataBlock == nullptr) {
        return 0;
    }

    // Get the data block pointer from the entry
    DataBlock* dataBlock = reinterpret_cast<DataBlock*>(entry->dataBlock);

    // Call helper to get an index (parameter is likely a key or context)
    // The decompiler shows FUN_0061b210(&stack0x00000004) - passing address of local variable.
    // We'll assume it takes a pointer to a structure or a value.
    // For reconstruction, we pass nullptr or a dummy.
    int32_t index = getDataIndex(nullptr); // placeholder

    if (index < 0) {
        return 0;
    }

    // Access the element at the given index
    DataElement* element = &dataBlock->elements[index];
    return element->value;
}