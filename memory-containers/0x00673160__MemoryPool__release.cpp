// FUNC_NAME: MemoryPool::release
// Function address: 0x00673160
// Role: Releases a slot in a fixed-size memory pool. Clears the slot pointer in the pool's index table,
// decrements the active count, and calls a global deallocation routine on the full allocation header.
// The object pointer (edx) is expected to point to the user data area; the pool header is at objPtr - 0x10.
// The slot index is stored at objPtr - 8 (two ints before the user data).
// Pool member offsets: +0x4 = activeCount, +0xC = slotArray (array of pointers indexed by slot index)

void __fastcall MemoryPool::release(void* objPtr)
{
    // Ensure objPtr is valid
    if (objPtr != 0) {
        // Retrieve the slot index from the pool header (located at objPtr - 8)
        int slotIndex = *reinterpret_cast<int*>(static_cast<char*>(objPtr) - 8);
        
        // Clear the slot pointer in the pool's array (this+0xC is the base of the slot pointer array)
        *(reinterpret_cast<int**>(this) + 0xC)[slotIndex] = 0;
        
        // Decrement the active slot count (this+0x4)
        *(reinterpret_cast<int*>(this) + 1) -= 1;  // +4 offset = int at index 1

        // Call the global deallocation function on the full header (objPtr - 0x10)
        // DAT_01206694 is a global function pointer
        extern void (*s_deallocateFunc)(void* header);
        s_deallocateFunc(static_cast<char*>(objPtr) - 0x10);
    }
}