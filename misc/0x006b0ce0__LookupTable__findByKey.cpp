// FUNC_NAME: LookupTable::findByKey
// Function at 0x006b0ce0: Searches a table of 8-byte entries (key? + offset 0, value at offset 4).
// Returns the value (4 bytes) of the first entry for which a predicate on param_2 is true.
// If no entry matches, returns 0.
// Note: The predicate (called at 0x006aed40) only receives param_2, not the entry data,
// so its return value is constant for a given param_2.

#include <stdint.h>

class LookupTable {
private:
    // +0x28: pointer to array of 8-byte entries (first 4 bytes unused in this function? +4 is value)
    uint8_t* entries;
    // +0x2c: number of entries
    uint32_t count;

public:
    uint32_t findByKey(uint32_t key) { // param_2 is interpreted as a key/index
        uint32_t value = 0;
        uint32_t index = 0;

        if (count != 0) {
            while (true) {
                // Each entry is 8 bytes: first 4 bytes (maybe key), offset+4 is value
                // Read value at (entries + 4 + index*8)
                value = *(uint32_t*)(entries + 4 + index * 8);
                // Call external key comparison function; param_2 passed as key
                bool match = keyMatches(key); // FUN_006aed40
                if (match) break;
                index++;
                if (index >= count) {
                    return 0; // not found
                }
            }
        }
        return value;
    }
};

extern bool keyMatches(uint32_t key); // defined elsewhere, 0x006aed40