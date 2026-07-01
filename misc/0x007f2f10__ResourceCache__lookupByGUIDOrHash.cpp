// FUNC_NAME: ResourceCache::lookupByGUIDOrHash
// Function address: 0x007f2f10
// Purpose: Look up a 128-bit key (4 uint32) in an internal table and return a 32-bit handle.
// The key is compared against a known magic "null" GUID (0xBADBD9BA, 0xBEEFBBEF, 0xEAC15A55, 0x91100911)
// and against all-zeroes; both cases return 0 (not found). Otherwise, hashes the key to an index
// and retrieves the first uint32 from the entry at that index in a 20-byte stride table.

// Assumed class layout:
// +0x00: vtable (4 bytes)
// +0x04: ... other members
// +0x10: pointer to table of entries (struct Entry)
//
// Entry structure (0x14 bytes each):
// +0x00: uint32 handle;  // returned value
// +0x04: ... other fields (16 more bytes, total 20)

struct ResourceCacheEntry {
    uint32 handle;      // +0x00
    uint8 padding[16];  // +0x04 (unspecified, but entry size is 0x14)
};

class ResourceCache {
public:
    // Assumes this pointer at ecx
    uint32 lookupByGUIDOrHash(const uint32 key[4]) {
        // Magic GUID considered invalid (all zeroes also invalid)
        static const uint32 kMagicGUID[4] = {
            0xBADBD9BA,  // -0x45245246
            0xBEEFBBEF,  // -0x41104111
            0xEAC15A55,  // -0x153ea5ab
            0x91100911   // -0x6eeff6ef
        };

        // If the key matches the magic GUID or is all zeroes, treat as invalid
        if ( (key[0] == kMagicGUID[0] && key[1] == kMagicGUID[1] &&
              key[2] == kMagicGUID[2] && key[3] == kMagicGUID[3]) ||
             (key[0] == 0 && key[1] == 0 && key[2] == 0 && key[3] == 0) )
        {
            return 0;
        }

        // Hash the key to get an index (internal function at 0x007f2be0)
        int index = hashIndexFromKey(key);
        if (index < 0)
            return 0;

        // Table pointer is at +0x10; each entry is 0x14 bytes starting at +0x10 within the table
        ResourceCacheEntry* base = reinterpret_cast<ResourceCacheEntry*>(*(int*)(this + 0x10));
        ResourceCacheEntry* entry = reinterpret_cast<ResourceCacheEntry*>(
            reinterpret_cast<uint8*>(base) + 0x10 + index * 0x14);
        if (entry == nullptr)
            return 0;

        return entry->handle;
    }

private:
    // Forward declaration of the hash-to-index function (defined elsewhere at 0x007f2be0)
    int hashIndexFromKey(const uint32 key[4]);
};