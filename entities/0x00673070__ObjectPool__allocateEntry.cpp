// FUNC_NAME: ObjectPool::allocateEntry
// Address: 0x00673070
// Allocates a new entry in a fixed-size pool with linear probing for free slots.
// Uses global allocator function pointer (likely malloc) and stores a magic number, key, and slot index.
// Returns pointer to user data area (offset 4 of allocated block) or null on failure.

#include <cstdint>

// Global allocator function pointer (initialized externally)
extern void* (*g_allocatorFunc)(uint32_t size);

class ObjectPool {
public:
    // Offsets (relative to this):
    // +0x04: m_usedCount  (uint32)
    // +0x08: m_capacity   (uint32)
    // +0x0C: m_slots      (uint32* -> array of pointers to allocated blocks)
    // +0x88: m_nextSlot   (uint32, starting index for linear probing)

    // Allocate and insert a new entry with the given key (stored as size/ID).
    // The allocated block has the following layout:
    //   +0x00: magic (0xaa53c5aa)
    //   +0x04: key (the size parameter)
    //   +0x08: slotIndex (inserted slot)
    //   +0x10+size: two marker bytes (0x5a, 0xf0)
    //
    // Returns pointer to the user data area (offset 0x04 from block start).
    void* allocateEntry(uint32_t key) {
        // Check global allocator
        if (g_allocatorFunc == nullptr) {
            return nullptr;
        }

        // Allocate block: header (12 bytes) + key bytes + 2 marker bytes
        uint32_t allocSize = key + 0x12;
        uint32_t* newBlock = (uint32_t*)(*g_allocatorFunc)(allocSize);
        if (newBlock == nullptr) {
            return nullptr;
        }

        // Initialize header
        newBlock[0] = 0xaa53c5aa;          // Magic number
        newBlock[1] = key;                  // Stored key (size/ID)
        // Write marker bytes at end of user area
        uint8_t* bytePtr = (uint8_t*)newBlock;
        bytePtr[key + 0x10] = 0x5a;
        bytePtr[key + 0x11] = 0xf0;

        // Linear probe for free slot
        uint32_t capacity = *(uint32_t*)((uint8_t*)this + 8);
        uint32_t startIndex = *(uint32_t*)((uint8_t*)this + 0x88);
        uint32_t* slotArray = *(uint32_t**)((uint8_t*)this + 0x0C);
        uint32_t searchCount = 0;

        if (capacity > 0) {
            while (slotArray[startIndex] != 0) {  // Slot is occupied
                searchCount++;
                startIndex = (startIndex + 1) % capacity;
                if (searchCount >= capacity) {
                    // All slots full – update next slot and return user data pointer even though no insert? 
                    // Original code returns the pointer anyway after updating state.
                    // This seems like a bug or intentional: it returns block even if not inserted.
                    *(uint32_t*)((uint8_t*)this + 0x88) = startIndex;
                    return newBlock + 1;  // Return pointer to user data (offset 4)
                }
            }
            // Found empty slot
            slotArray[startIndex] = (uint32_t)newBlock;
            newBlock[2] = startIndex;       // Store slot index
            // Increment used count
            uint32_t usedCount = *(uint32_t*)((uint8_t*)this + 4);
            *(uint32_t*)((uint8_t*)this + 4) = usedCount + 1;
        }

        // Update next slot index
        *(uint32_t*)((uint8_t*)this + 0x88) = startIndex;
        return newBlock + 1;  // Return pointer to user data (offset 4)
    }
};