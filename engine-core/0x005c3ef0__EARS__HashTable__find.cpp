// FUNC_NAME: EARS::HashTable::find
// Reconstructed from Ghidra at 0x005c3ef0
// Looks up a key in a hash table (open addressing with global hash tables).
// The instance fields:
//   +0x00: vtable
//   +0x08: m_bucketArray (int**)
//   +0x0C: m_numBuckets (uint32)
//   +0xC0: m_directLookup (bool) -- if true, skip key comparison and return bucket directly

extern uint8 g_hashByteTable[256];          // DAT_00f17680
extern uint32 g_hashIntTable[256];          // DAT_00f17684

int* __thiscall HashTable::find(uint32 key)
{
    uint8* thisPtr = reinterpret_cast<uint8*>(this);
    int** bucketArray = *reinterpret_cast<int***>(thisPtr + 0x08);
    uint32 bucketCount = *reinterpret_cast<uint32*>(thisPtr + 0x0C);
    bool directLookup = *reinterpret_cast<bool*>(thisPtr + 0xC0);

    // Compute hash from key using global tables
    uint8 b0 = key & 0xFF;
    uint8 b1 = (key >> 8) & 0xFF;
    uint8 b2 = (key >> 16) & 0xFF;
    uint8 b3 = (key >> 24) & 0xFF;

    uint32 hash = g_hashByteTable[b2] + g_hashByteTable[b1] + g_hashByteTable[b3] + g_hashIntTable[b0];

    // Clamp to max bucket index (stored at g_hashByteTable[0])
    uint8 maxBucket = g_hashByteTable[0];
    if (hash > maxBucket) {
        hash = maxBucket;
    }

    // Direct lookup (flag set) – assume no collisions
    if (hash < bucketCount) {
        int* candidate = bucketArray[hash];
        if (candidate != nullptr) {
            if (directLookup) {
                return candidate;
            }
            // Compare key via virtual function at vtable+4
            uint32 objKey = (*(uint32 (__thiscall**)(int*))(*(int**)candidate)[1])(candidate); // vtable+4
            if (objKey == key) {
                return candidate;
            }
        }
    }

    // Linear probing if not direct or mismatch
    if (!directLookup) {
        for (uint32 i = hash + 1; i < bucketCount; ++i) {
            int* candidate = bucketArray[i];
            if (candidate != nullptr) {
                uint32 objKey = (*(uint32 (__thiscall**)(int*))(*(int**)candidate)[1])(candidate);
                if (objKey == key) {
                    return candidate;
                }
            }
        }
    }

    return nullptr;
}