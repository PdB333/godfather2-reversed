// FUNC_NAME: TableManager::allocateIfNeeded

// Constructor/allocator for a table manager with 128 entries.
// Takes a pointer to a flag (param_1) that indicates whether to allocate or free.
// Uses global function pointers for memory allocation (DAT_01206690) and deallocation (DAT_01206694).
// Returns pointer to allocated structure on success, null if allocator missing or if param_1 indicates free.

#include <cstdint>

typedef uint16_t* (__cdecl *AllocFunc)(uint32_t size);
typedef void (__cdecl *FreeFunc)(void* ptr);

extern AllocFunc DAT_01206690;  // Allocation function
extern FreeFunc  DAT_01206694;  // Deallocation function

// Called before table initialization; returns some result stored at offset 0xF1C
extern uint32_t FUN_00672e60(int* param_1);

// Structure for each of the 128 table entries (size 0x1E bytes?)
struct TableEntry {
    // Layout inferred from initialization loop:
    // - short at offset -0x12 (18 bytes before entry start) is set to 0xFFFF
    // - two uint32_t at entry start set to 0
    // Total entry stride: 0xF (15 uint32_t? Actually 60 bytes per entry)
    uint8_t data[60];  // 60 bytes per entry
};

// Main table structure (size 0x1E3C = 7740 bytes)
struct TableManager {
    // Header fields (first 0x30 bytes)
    uint16_t field_00;       // +0x00
    uint32_t field_02;       // +0x02 (4 bytes, aligns to 2?)
    uint16_t field_04;       // +0x04
    uint32_t field_06;       // +0x06
    uint16_t field_08;       // +0x08
    uint32_t field_0A;       // +0x0A
    uint16_t field_0C;       // +0x0C
    uint16_t field_0D;       // +0x0D
    // padding? Then array starts at +0x18 (48 bytes)
    uint8_t padding[0x18 - 0x0E]; // to align to 0x18
    TableEntry entries[128];  // 128 * 60 = 7680 bytes
    // Tail fields at offset 0xF0E (in 2-byte units = 0x1E1C bytes from start)
    uint16_t field_F0E;      // +0x1E1C, set to 0xFFFF
    uint32_t field_F10;      // +0x1E20, set to 0
    uint32_t field_F12;      // +0x1E24, set to 0
    uint16_t field_F14;      // +0x1E28, set to 3
    uint16_t field_F15;      // +0x1E2A, set to 1
    uint16_t field_F16;      // +0x1E2C, set to 0x409
    uint16_t field_F17;      // +0x1E2E, set to 4
    uint32_t field_F18;      // +0x1E30, set to 0x48
    uint32_t field_F1A;      // +0x1E34, set to 0x48
    uint32_t field_F1C;      // +0x1E38, variable from FUN_00672e60
    // total size 0x1E3C
};

// Returns allocated structure or null
TableManager* FUN_006719c0(int* param_1) {
    if (DAT_01206690 == nullptr) {
        return nullptr;
    }

    TableManager* pTable = reinterpret_cast<TableManager*>(DAT_01206690(0x1E3C));
    if (pTable == nullptr) {
        return nullptr;
    }

    uint32_t initResult = FUN_00672e60(param_1);
    pTable->field_F1C = initResult;

    if (*param_1 == 0) {
        // Initialize all fields
        pTable->field_00 = 0;
        pTable->field_02 = 0;
        pTable->field_04 = 0;
        pTable->field_06 = 0;
        pTable->field_08 = 0;
        pTable->field_0A = 0;
        pTable->field_0D = 0;
        pTable->field_0C = 0;

        // Initialize 128 table entries
        uint32_t* pEntry = reinterpret_cast<uint32_t*>(&pTable->entries[0]);
        for (int i = 0; i < 128; i++) {
            // Write short at 18 bytes before entry start
            *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(pEntry) - 18) = 0xFFFF;
            // Zero first two uint32_t of the entry
            *pEntry = 0;
            *(pEntry + 1) = 0;
            // Advance to next entry (60 bytes)
            pEntry += 15; // 15 uint32_t = 60 bytes
        }

        // Initialize tail fields
        pTable->field_F0E = 0xFFFF;
        pTable->field_F10 = 0;
        pTable->field_F12 = 0;
        pTable->field_F14 = 3;
        pTable->field_F15 = 1;
        pTable->field_F16 = 0x409; // 1033
        pTable->field_F17 = 4;
        pTable->field_F18 = 0x48;  // 72
        pTable->field_F1A = 0x48;  // 72

        return pTable;
    } else {
        // Already allocated: free the memory and return null
        DAT_01206694(pTable);
        return nullptr;
    }
}