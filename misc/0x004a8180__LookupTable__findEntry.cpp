// FUNC_NAME: LookupTable::findEntry

#include <cstdint>

// Structure of each entry in the table (size 20 bytes = 5 * 4 bytes)
struct LookupEntry {
    uint32_t id;      // +0x00: unique numeric identifier
    char*    name;    // +0x04: pointer to null-terminated string (may be nullptr if entry is empty)
    // +0x08, +0x0C, +0x10: unknown additional fields (padding or other data)
};

// Class representing a sorted lookup table supporting both ID and name searches
class LookupTable {
public:
    // Offsets:
    // +0x00: vtable pointer (assumed)
    // +0x08: uint16_t entryCount
    // +0x10: LookupEntry* entries (array of 5-int structures)
    uint16_t entryCount;     // at offset 0x08
    LookupEntry* entries;    // at offset 0x10

    // Uses case-insensitive string comparison (ASCII only, uppercase lowering)
    static bool strCaseEquals(const char* a, const char* b) {
        while (*a && *b) {
            int ca = static_cast<unsigned char>(*a);
            int cb = static_cast<unsigned char>(*b);
            if (ca >= 'a' && ca <= 'z') ca -= 0x20;
            if (cb >= 'a' && cb <= 'z') cb -= 0x20;
            if (ca != cb) break;
            ++a; ++b;
        }
        // If we reached end of a, check b: either b is also at end or b is '.' (wildcard)
        return (*a == '\0') && (*b == '.' || *b == '\0');
    }

    // Find an entry by ID (if id != 0) or by name (if id == 0 and name is provided).
    // Uses binary search for ID, linear search for name.
    // Returns pointer to the matching entry, or nullptr if not found.
    __thiscall LookupEntry* findEntry(uint32_t id, const char* name) {
        LookupEntry* base = entries;
        uint16_t count = entryCount;

        if (id == 0) {
            // Search by name (case-insensitive, with '.' wildcard)
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            for (uint16_t i = 0; i < count; ++i) {
                LookupEntry* entry = &base[i];
                // Skip entries with id == 0 (empty/uninitialized)
                if (entry->id != 0) continue;
                // name should be non-null for valid entries
                const char* entryName = entry->name;
                if (strCaseEquals(entryName, name)) {
                    return entry;
                }
            }
            return nullptr;
        } else {
            // Binary search by ID (array must be sorted by id)
            uint32_t low = 0;
            uint32_t high = count;
            while (low < high) {
                uint32_t mid = (low + high) >> 1;
                uint32_t midId = base[mid].id;
                if (midId < id) {
                    low = mid + 1;
                } else {
                    high = mid;
                }
            }
            if (low < count && base[low].id == id) {
                return &base[low];
            }
            return nullptr;
        }
    }
};