// FUNC_NAME: ObjectRegistry::findByExtendedGuid

// Address: 0x0043d0d0
// Role: Looks up an entry in a fixed-size hash table using a 192-bit key (six uint32 words).
//       Returns the first field (presumably a pointer or handle) of the matching entry, or 0.
//       The table is stored at this+0x10, with entry array at offset 0x18 from the table base.
//       Each entry is 28 bytes (0x1c) large.

#include <cstdint>

// Forward declaration of the hash/index function (defined elsewhere)
int32_t hashTableLookupKey(uint32_t key[6]); // actually FUN_0043db90

class ObjectRegistry {
public:
    // this+0x10: pointer to table base (contains header, then entry array at offset 0x18)
    uint32_t findByExtendedGuid(uint32_t keyWords[4], uint32_t extra1, uint32_t extra2) {
        // Build full 6-word key (192 bits)
        uint32_t fullKey[6];
        fullKey[0] = keyWords[0];
        fullKey[1] = keyWords[1];
        fullKey[2] = keyWords[2];
        fullKey[3] = keyWords[3];
        fullKey[4] = extra1;   // from param_3
        fullKey[5] = extra2;   // from param_4

        // Get index into the hash table (-1 if not found)
        int32_t index = hashTableLookupKey(fullKey);
        if (index < 0) {
            return 0;
        }

        // Access the table structure
        uint8_t* tableBase = *(uint8_t**)(this + 0x10); // pointer to table header
        if (tableBase == nullptr) {
            return 0;
        }

        // +0x18: offset to start of entry array
        // Each entry is 0x1c bytes
        uint32_t* entry = (uint32_t*)(tableBase + 0x18 + index * 0x1c);
        return *entry; // first field of the entry (e.g., a pointer to the actual object)
    }
};