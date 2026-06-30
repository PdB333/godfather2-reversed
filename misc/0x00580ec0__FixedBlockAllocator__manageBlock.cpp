// FUNC_NAME: FixedBlockAllocator::manageBlock
// Address: 0x00580ec0
// This function handles allocation/deallocation of fixed-size blocks in a pool.
// The pool is aligned to 16 bytes. Each block has a header with a usage flag (offset 0)
// and zones for free list management and user data.

class FixedBlockAllocator {
public:
    // +0x00: uint inUse;       // non-zero if block is currently allocated
    // +0x24: int blockSize;     // size of each block
    // +0x3C: int userData;      // user-set value (param_2)
    // +0x48: void* dataArea;    // pointer to block data (at +0x80 from header start)
    // +0x94: int nextFree;      // next free block offset (or pointer)
    // +0x98: int prevFree;      // previous free block offset (or pointer)
    // +0x9C: void* freeListHead; // head of free list (points to +0xF0 area)

    // The actual data area for each block starts at header offset 0x80.
    // Free blocks are linked using the area at +0xF0 (next/prev pointers).

    int __thiscall manageBlock(void* blockMemory, int param2) {
        int alignmentOffset = 0x10 - ((uint)blockMemory & 0xf);
        if (alignmentOffset == 0x10) {
            alignmentOffset = 0;
        }

        int* header = (int*)((char*)blockMemory + alignmentOffset); // aligned to 16 bytes

        if (*header != 0) {
            // Block is currently in use – handle as deallocation or reuse
            header[0xf] = param2;                           // +0x3C: store user parameter
            header[0x12] = (int)(header + 0x20);            // +0x48: set dataArea pointer
            // Call function to return block to free list (address = dataArea + ushort at +0x1A)
            FUN_0057f750((uint)*(ushort*)((int)header + 0x1a) + (int)(header + 0x20));
            return extraout_ECX;
        } else {
            // Block is free – prepare for allocation
            header[0x27] = (int)(header + 0x3c);            // +0x9C: freeListHead = &header[0x3C] (offset 0xF0)
            int freeChunkStart = (int)(header + 0x3c) + header[9]; // +0x24: blockSize
            header[0x25] = freeChunkStart;                  // +0x94: nextFree
            header[0x26] = freeChunkStart;                  // +0x98: prevFree
            FUN_00580ca0();                                 // Initialize block for use (e.g., clear data)
            return extraout_ECX_00;
        }
    }
};