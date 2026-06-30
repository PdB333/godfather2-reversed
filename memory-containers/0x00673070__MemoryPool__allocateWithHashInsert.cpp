// FUNC_NAME: MemoryPool::allocateWithHashInsert
// Function address: 0x00673070
// Allocates a memory block from a global allocator, initializes header, and inserts into a hash table with linear probing.
// The block layout: header (16 bytes: magic, size, slotIndex, padding?), user data, then sentinel bytes (0x5a, 0xf0).
// Returns pointer to user data section (offset 0x10 from block start).

#include <cstdint>

// Magic number to identify allocated blocks
constexpr uint32_t kBlockMagic = 0xAA53C5AA;

// External allocator function pointer (global)
extern void* (*g_allocator)(int size);

// Hash table structure (offset in EDI)
struct HashTable {
    int     count;        // +0x04: number of occupied slots
    uint32_t capacity;    // +0x08: total slots
    void**  slots;        // +0x0C: array of slot pointers
    uint32_t probeIndex;  // +0x88: current probe index for next allocation
};

// Block header (allocated block)
struct BlockHeader {
    uint32_t magic;       // +0x00: magic number
    uint32_t size;        // +0x04: size of user data (in_EAX)
    uint32_t slotIndex;   // +0x08: index in hash table
    uint32_t padding;     // +0x0C: reserved (maybe alignment)
    // user data starts at offset 0x10
};

// Returns pointer to user data or nullptr on failure
void* __fastcall MemoryPool::allocateWithHashInsert(HashTable* hashTable, uint32_t userDataSize)
{
    // in_EAX is userDataSize, in_EDI is hashTable
    if (g_allocator == nullptr)
        return nullptr;

    void* rawBlock = g_allocator(userDataSize + 0x12); // size + header(0x10) + sentinel(2)
    if (rawBlock == nullptr)
        return nullptr;

    BlockHeader* header = (BlockHeader*)rawBlock;
    header->magic = kBlockMagic;
    header->size = userDataSize;
    header->slotIndex = 0; // will be set below

    // Write sentinel bytes at end of user data
    uint8_t* sentinel = ((uint8_t*)rawBlock) + userDataSize + 0x10;
    sentinel[0] = 0x5A;
    sentinel[1] = 0xF0;

    // Insert into hash table with linear probing
    uint32_t capacity = hashTable->capacity;
    uint32_t index = hashTable->probeIndex;
    int count = hashTable->count;
    void** slots = hashTable->slots;

    int i = 0;
    if (count > 0 && (int)capacity > 0) {
        while (slots[index] != nullptr) {
            i++;
            index = (index + 1) % capacity;
            if (i >= (int)capacity) {
                // All slots full; still return pointer, but not inserted?
                hashTable->probeIndex = index;
                return (void*)((uint8_t*)rawBlock + 0x10); // user data
            }
        }
        slots[index] = rawBlock;
        header->slotIndex = index;
        hashTable->count = count + 1;
    }

    hashTable->probeIndex = index;
    return (void*)((uint8_t*)rawBlock + 0x10); // user data
}