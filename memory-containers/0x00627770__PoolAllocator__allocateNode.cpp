// FUNC_NAME: PoolAllocator::allocateNode
// Function address: 0x00627770
// Role: Allocates a node of 0x58 bytes from a pool allocator. Inserts node into free list and initializes its fields.

#include <cstdint>

class PoolAllocator {
public:
    // Pool state fields (offsets relative to this):
    // +0x10: Free list head pointer (pointer to next available node)
    // +0x40: Some metadata value (copied to new node)
    // +0x44: Another metadata value

    void* allocateNode() __thiscall {
        // Global allocation function (likely malloc or custom allocator)
        // Signature: void* __cdecl allocate(size_t size)
        auto allocFunc = reinterpret_cast<void* (*)(int, int)>(DAT_012059dc);

        void* newNode = allocFunc(0, 0x58);  // Allocate 0x58 bytes

        if (newNode == nullptr) {
            // Allocation failed: if pool not null, try alternate allocator
            if (this != nullptr) {
                // Fallback allocation from another pool
                return reinterpret_cast<void*>(FUN_00635a80());
            }
            return nullptr;
        }

        // Update pool's allocation statistics if pool is valid
        if (this != nullptr) {
            // Increment allocated size by 0x58 (stored at *(+0x10) + 0x24)
            int* sizeCounter = reinterpret_cast<int*>(
                *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x10) + 0x24
            );
            *sizeCounter += 0x58;
        }

        // Link the new node into the free list (head insertion)
        // First, set node's next pointer to current head
        *reinterpret_cast<uint32_t*>(newNode) = *reinterpret_cast<uint32_t*>(
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x10) + 0xc
        );
        // Update head to point to new node
        *reinterpret_cast<uint32_t*>(
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x10) + 0xc
        ) = reinterpret_cast<uint32_t>(newNode);

        // Zero out various fields (offsets relative to newNode base)
        // Offset +0x05: byte = 0
        *reinterpret_cast<uint8_t*>(reinterpret_cast<char*>(newNode) + 5) = 0;
        // Offset +0x04: byte = 8 (flags?)
        *reinterpret_cast<uint8_t*>(reinterpret_cast<char*>(newNode) + 4) = 8;
        // Offset +0x1C (word?) Actually puVar2[7] -> offset 0x1C
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(newNode) + 0x1C) = 0;
        // Offset +0x20
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(newNode) + 0x20) = 0;
        // Offset +0x50
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(newNode) + 0x50) = 0;
        // Offset +0x3C
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(newNode) + 0x3C) = 0;
        // Offset +0x32: byte = 0
        *reinterpret_cast<uint8_t*>(reinterpret_cast<char*>(newNode) + 0x32) = 0;
        // Offset +0x30: byte = 0
        *reinterpret_cast<uint8_t*>(reinterpret_cast<char*>(newNode) + 0x30) = 0;
        // Offset +0x34
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(newNode) + 0x34) = 0;
        // Offset +0x31: byte = 1
        *reinterpret_cast<uint8_t*>(reinterpret_cast<char*>(newNode) + 0x31) = 1;
        // Offset +0x38
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(newNode) + 0x38) = 0;
        // Offset +0x48
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(newNode) + 0x48) = 0;
        // Offset +0x2C: short
        *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(newNode) + 0x2C) = 0;
        // Offset +0x2E: short
        *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(newNode) + 0x2E) = 0;
        // Offset +0x14
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(newNode) + 0x14) = 0;
        // Offset +0x28
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(newNode) + 0x28) = 0;
        // Offset +0x54
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(newNode) + 0x54) = 0;
        // Offset +0x40
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(newNode) + 0x40) = 0;

        // Set node's pool reference (offset +0x10) to pool's list head
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(newNode) + 0x10) =
            *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(this) + 0x10);

        // Call additional initialization function (likely sets more fields)
        FUN_00627430();

        // Copy metadata from pool to node (offsets +0x40 and +0x44)
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(newNode) + 0x40) =
            *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(this) + 0x40);
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(newNode) + 0x44) =
            *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(this) + 0x44);

        return newNode;
    }

private:
    // Global allocation function pointer (likely from import)
    static inline void* (*DAT_012059dc)(int, int) = reinterpret_cast<void* (*)(int, int)>(nullptr);
    // External helper functions (callees)
    void FUN_00627430(); // Internal initialization
    void* FUN_00635a80(); // Fallback allocation
};