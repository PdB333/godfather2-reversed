// FUNC_NAME: setFlagInEntityList
// Function at 0x00572db0: Sets or clears a flag (bit 0x80) on an entity identified by targetId.
// Searches two arrays of 0x20-byte entries (offsets +0xa0/+0xa8 and +0xa4/+0xaa) for matching id at offset 0.
// Flag is at offset 6 (ushort). Used for marking entities (e.g., occupied, selected).
// Note: param_1 (ecx) is unused; targetId is passed implicitly via EDI in original asm.
// We add explicit targetId parameter for clarity.

#include <cstdint>

#define FLAG_BIT 0x80

struct EntityEntry {
    int32_t id;           // +0x00
    uint8_t _pad[2];      // +0x04..0x05
    uint16_t flags;       // +0x06
    // entry total 0x20 bytes
};

struct EntityManager {
    int32_t* array1;      // +0xa0
    int32_t* array2;      // +0xa4
    int16_t count1;       // +0xa8
    int16_t count2;       // +0xaa
};

void __fastcall setFlagInEntityList(int unused, EntityManager* manager, int32_t targetId, bool setFlag) {
    // Search first array
    for (int16_t i = 0; i < manager->count1; ++i) {
        if (manager->array1[i * 8] == targetId) {  // each entry is 0x20 bytes = 8 int32s, id at offset 0
            uint16_t* flagPtr = reinterpret_cast<uint16_t*>(&manager->array1[i * 8 + 2]); // offset 6 from base
            if (setFlag) {
                *flagPtr |= FLAG_BIT;
            } else {
                *flagPtr &= ~FLAG_BIT;
            }
            return;
        }
    }

    // Search second array
    for (int16_t i = 0; i < manager->count2; ++i) {
        if (manager->array2[i * 8] == targetId) {
            uint16_t* flagPtr = reinterpret_cast<uint16_t*>(&manager->array2[i * 8 + 2]);
            if (setFlag) {
                *flagPtr |= FLAG_BIT;
            } else {
                *flagPtr &= ~FLAG_BIT;
            }
            return;
        }
    }
}