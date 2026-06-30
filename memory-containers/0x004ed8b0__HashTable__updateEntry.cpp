// FUNC_NAME: HashTable::updateEntry
// Function at 0x004ed8b0
// This function updates an entry in a global hash table (EARS engine).
// The hash table uses chained buckets with nodes of the form:
//   struct HashNode {
//       uint32_t key;     // +0x00
//       uint8_t* data;    // +0x04 (pointer to data block)
//       HashNode* next;   // +0x08
//   };
// The data block (pointed to by node->data) has the following layout:
//   +0x10: dataPart[0..3] (4 uint32)
//   +0x20: param2
//   +0x28: param7
//   +0x2c: param8
//   +0x30: param6
//   +0x34: param9
//   +0x3c: param10 (uint8)
// Offsets 0x00-0x0F in the data block are used for other purposes (unclear).
//
// When the key exists and node->data is non-null, the provided data is written
// directly into the existing data block. If the key does not exist or node->data
// is null, the decompiled code attempts to write to address 0x10 (null pointer
// dereference). This suggests the function is called *only* when the key already
// exists with a valid data block, or the global table is pre-initialized. For
// reconstruction, we assume the existing-entry path is the only used one.

#include <cstdint>

// Global hash table manager (from DAT_01223398)
extern void* g_hashTableManager;

void HashTable::updateEntry(uint32_t key,
                            uint32_t param2,
                            uint32_t /*param3*/,   // unused in this version
                            uint32_t /*param4*/,   // unused
                            uint32_t dataPart[4],  // pointer to 4 uint32s
                            uint32_t param6,
                            uint32_t param7,
                            uint32_t param8,
                            uint32_t param9,
                            uint8_t param10)
{
    // Navigate through the global hash table structure
    // g_hashTableManager + 8 → bucket descriptor (struct with +4 = bucket array, +8 = table size)
    struct BucketDescriptor {
        uint32_t** buckets;   // +0x04
        uint32_t  size;       // +0x08
    };
    
    BucketDescriptor* desc = *(BucketDescriptor**)((uint8_t*)g_hashTableManager + 8);
    uint32_t index = key % desc->size;
    uint32_t* node = (uint32_t*)desc->buckets[index];  // first node in the chain

    while (node != nullptr)
    {
        if (node[0] == key)   // key match
        {
            uint8_t* dataBlock = (uint8_t*)node[1];   // node->data
            if (dataBlock != nullptr)
            {
                // Write the provided data into the existing data block
                *(uint32_t*)(dataBlock + 0x10) = dataPart[0];
                *(uint32_t*)(dataBlock + 0x14) = dataPart[1];
                *(uint32_t*)(dataBlock + 0x18) = dataPart[2];
                *(uint32_t*)(dataBlock + 0x1c) = dataPart[3];
                *(uint32_t*)(dataBlock + 0x20) = param2;
                *(uint32_t*)(dataBlock + 0x28) = param7;
                *(uint32_t*)(dataBlock + 0x2c) = param8;
                *(uint32_t*)(dataBlock + 0x30) = param6;
                *(uint32_t*)(dataBlock + 0x34) = param9;
                *(uint8_t*)(dataBlock + 0x3c) = param10;
                return;
            }
            // If dataBlock is null, fall through to the "new entry" path below
            // (not expected in normal operation)
        }
        node = (uint32_t*)node[2];   // advance to next node
    }

    // New entry or null data pointer (path that would cause null write in original)
    // In the decompiled binary, this writes to address 0x10, which is a bug in
    // the decompilation or indicates this code path is intentionally unreachable.
    // We leave it as a no‑op to avoid undefined behavior.
    // (The original game likely never reaches this point.)
    return;
}