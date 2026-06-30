// FUNC_00646cf0: alignedPoolAlloc (PoolAllocator::allocateAligned? At 0x00646cf0)
// Allocates aligned memory from a pool. The pool structure has a capacity at offset +4.
// The alignment is passed in EAX (first param here), blockHeader in EDX (second param),
// requested size on stack (third), and output pointer on stack (fourth).
// Uses a preserved register (unaff_EDI) as heap base.

int __fastcall alignedPoolAlloc(int alignment, int blockHeader, int requestedSize, int* outPtr)
{
    int heapBase; // unaff_EDI – base of the heap region
    int alignedAddr;
    int blockSize;

    // Initial aligned address candidate relative to heapBase
    alignedAddr = blockHeader + alignment + heapBase;
    alignedAddr = ((alignedAddr + 7) & -alignment) - heapBase - 8;

    // Pool capacity from header, mask off low bits
    blockSize = *(int*)(blockHeader + 4) & 0x7ffffff8;

    if (alignedAddr != blockHeader) {
        // If the requested aligned area is too close to the block header (< 16 bytes), realign with a larger offset.
        if ((uint)(alignedAddr - blockHeader) < 0x10) {
            alignedAddr = ((blockHeader + alignment + 0x10 + heapBase + 7) & -alignment) - heapBase - 8;
        }
        // Verify remaining space is sufficient (if not zero, must be at least 16 bytes)
        int leftover = ((blockSize - alignedAddr) - requestedSize) + blockHeader;
        if ((leftover != 0) && ((uint)leftover < 0x10)) {
            return 0; // Not enough space
        }
    }

    if (alignedAddr != 0) {
        // Compute and store the free space pointer (or some other output) in outPtr
        *outPtr = (((blockSize - requestedSize) + blockHeader + 8 + heapBase) & -alignment) - heapBase - 8;
    }

    return alignedAddr; // Returns the allocated address
}