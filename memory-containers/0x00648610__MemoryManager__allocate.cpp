// FUNC_NAME: MemoryManager::allocate
void * __thiscall MemoryManager::allocate(uint size) {
  uint *blockHeader;
  DWORD allocationType;
  int *basePtr;
  int adjust;
  uint alignedSize;

  // Round up size to alignment boundary, adding overhead (0x1e = 30 bytes for headers/footer)
  alignedSize = (*(int *)(this + 0x4d8) + 0x1e + size) & ~(*(int *)(this + 0x4d8) - 1U);

  if (size <= alignedSize) {
    // Determine allocation flags: if flag at +0x498 is set, use 0x103000 (MEM_RESERVE|MEM_COMMIT|PAGE_GUARD?) else 0x3000
    allocationType = 0x3000;
    if (*(char *)(this + 0x498) != '\0') {
      allocationType = 0x103000;
    }

    basePtr = (int *)VirtualAlloc(nullptr, alignedSize, allocationType, PAGE_READWRITE);
    if (basePtr != nullptr) {
      // Update total allocated size and count
      *(int *)(this + 0x48c) += alignedSize;
      *(int *)(this + 0x488) += 1;

      alignedSize -= 0x10; // Subtract footer size (header + footer = 0x10? Actually header is 8 bytes, footer is at least 8? Let's keep as decomp: subtract 0x10)

      if (((uint)basePtr & 7) == 0) {
        // Already aligned to 8 bytes
        *basePtr = 0;            // Previous block size (0 = none)
        basePtr[1] = alignedSize | 2;  // Size with free flag (2 = free)
      } else {
        // Adjust to 8-byte boundary
        adjust = 8 - ((uint)basePtr & 7);
        basePtr = (int *)((int)basePtr + adjust);
        alignedSize -= adjust;
        *basePtr = adjust;            // Size of padding header
        basePtr[1] = adjustedSize | 2; // Size with free flag
      }

      // Set footer at the end of the block
      blockHeader = (uint *)((int)basePtr + alignedSize);
      *blockHeader = alignedSize;      // Size stored again (for coalescing)
      blockHeader[1] = 0x13;           // Footer flag (0x13 = end of free list?)

      // Insert into doubly linked free list (stored after footer)
      uint *prevHead = *(uint **)(this + 0x4a8);
      blockHeader[2] = (uint)(this + 0x49c); // Next pointer (point to head sentinel)
      blockHeader[3] = (uint)prevHead;      // Prev pointer

      *(uint **)(this + 0x4a8) = blockHeader; // Update tail
      if (prevHead != nullptr) {
        *(uint **)(prevHead + 2) = blockHeader; // Set next of previous tail
      }

      // Return pointer to usable memory (after header)
      return basePtr + 2;
    }
  }

  return nullptr;
}