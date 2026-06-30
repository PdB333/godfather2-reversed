// FUNC_NAME: allocateObject
// Address: 0x00615ec0
// Role: Custom memory allocator with per-thread fast path and global free list fallback.
// Allocates a fixed-size block (at least 8 bytes) and stores a vtable pointer and the given argument.
// Fast path uses a bump allocator from a global buffer; slow path uses a linked list of free blocks.

#include <cstdint>

// Forward declaration of a spin-wait or yield function used in slow path.
void spinLockWait(); // Address: 0x00485280

// Global data: pointer to a bump allocator buffer (fast path).
// +0x00: pointer to current free position? Actually used as a pointer to a pointer to vtable.
// +0x14: offset to a pointer that holds the next free slot.
extern uint8_t* g_bumpAllocatorBase; // DAT_01206880

// Global free list head (slow path).
extern uint8_t* g_freeListHead; // PTR_DAT_01117bb0

// Global tail of free list (used for appending).
extern uint8_t* g_freeListTail; // DAT_01117bc0

// Another global pointer, possibly the last allocated block in slow path.
extern uint8_t* g_freeListLast; // DAT_01117bbc

// Vtable pointer for the allocated object type.
extern void* g_objectVtable; // PTR_LAB_01127730

// Label used as a return address or cleanup trampoline in slow path blocks.
extern void* g_slowPathLabel; // LAB_00615e40

void allocateObject(uint32_t size) // param_1
{
    // Check thread-local storage (FS:[0x2c] + 0x34) for a flag indicating fast path availability.
    // In Windows, FS:[0x2c] points to the thread-local storage array.
    // The value at offset 0x34 is likely a per-thread flag (0 = fast path allowed).
    uint32_t* tlsFlag = reinterpret_cast<uint32_t*>(*(uint32_t*)(__readfsdword(0x2c) + 0x34));
    if (*tlsFlag == 0)
    {
        // Fast path: bump allocator from a global buffer.
        // The buffer at g_bumpAllocatorBase + 0x14 holds a pointer to the next free slot.
        uint32_t** nextSlotPtr = reinterpret_cast<uint32_t**>(g_bumpAllocatorBase + 0x14);
        *nextSlotPtr = &g_objectVtable; // Write vtable pointer to the slot.
        *nextSlotPtr = reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(*nextSlotPtr) + 4); // Advance pointer by 4 (vtable size).
        uint32_t* alignedSlot = reinterpret_cast<uint32_t*>((reinterpret_cast<uint32_t>(*nextSlotPtr) + 3) & ~3); // Align to 4 bytes.
        *nextSlotPtr = alignedSlot;
        *alignedSlot = size; // Store the argument (size or object ID).
        *nextSlotPtr = reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(*nextSlotPtr) + 4); // Advance past the stored value.
        return;
    }

    // Slow path: allocate from a global free list of fixed-size blocks.
    uint32_t* block = reinterpret_cast<uint32_t*>(g_freeListHead);
    if (block == nullptr)
    {
        // Spin-wait until a block becomes available.
        do {
            spinLockWait();
            block = reinterpret_cast<uint32_t*>(g_freeListHead);
        } while (block == nullptr);
    }

    // Remove block from free list.
    g_freeListHead = reinterpret_cast<uint8_t*>(block[3]); // Next block is at offset 12 (3 * 4).
    block[3] = 0; // Clear next pointer.

    // Initialize the block: first word is a label (likely a cleanup trampoline or return address).
    block[0] = reinterpret_cast<uint32_t>(g_slowPathLabel);
    block[1] = size; // Store the argument.
    block[2] = 0; // Clear third word.

    // Append the block to the tail of the free list? Actually, this seems to be adding to a separate list.
    if (g_freeListTail != nullptr)
    {
        // Link the new block after the current tail.
        *reinterpret_cast<uint32_t**>(reinterpret_cast<uint32_t>(g_freeListTail) + 12) = block;
        g_freeListTail = reinterpret_cast<uint8_t*>(block);
    }
    else
    {
        // First block in the list.
        g_freeListLast = reinterpret_cast<uint8_t*>(block);
        g_freeListTail = reinterpret_cast<uint8_t*>(block);
    }
}