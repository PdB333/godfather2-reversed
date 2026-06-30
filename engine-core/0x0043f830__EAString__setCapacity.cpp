// FUNC_NAME: EAString::setCapacity
void __thiscall EAString::setCapacity(void *thisPtr, uint newCapacity, rsize_t dataSize)
{
  uint alignedCap;
  void *dst;
  void *src;
  uint curCap;
  uint halfCap;

  // Round new capacity up to at least 15 (fits in inline buffer?)
  alignedCap = newCapacity | 0xf;
  if (alignedCap != 0xffffffff) {
    curCap = *(uint *)((int)thisPtr + 0x18); // +0x18: capacity
    halfCap = curCap >> 1;
    newCapacity = alignedCap;
    // Growth heuristic: if new capacity < half of old capacity AND old capacity <= -(halfCap) -2,
    // use sum of halfCap + curCap (likely shrink logic)
    if ((alignedCap / 3 < halfCap) && (curCap <= -halfCap - 2)) {
      newCapacity = halfCap + curCap;
    }
  }

  dst = (void *)allocateMemory(newCapacity + 1, 0);  // +1 for null terminator?

  if (dataSize != 0) {
    if (*(uint *)((int)thisPtr + 0x18) < 0x10) {
      src = (void *)((int)thisPtr + 4);   // +0x04: inline buffer (size 16)
    } else {
      src = *(void **)((int)thisPtr + 4); // +0x04: pointer to heap buffer
    }
    memcpy_s(dst, newCapacity + 1, src, dataSize);
  }

  // Free old buffer if it was heap-allocated (capacity > 15)
  if (0xf < *(uint *)((int)thisPtr + 0x18)) {
    deallocateMemory(*(undefined4 *)((int)thisPtr + 4));
  }

  // Replace buffer pointer and metadata
  *(undefined1 *)((int)thisPtr + 4) = 0;          // Clear inline buffer first byte (or set pointer low byte?)
  *(void **)((int)thisPtr + 4) = dst;             // +0x04: store new pointer
  *(uint *)((int)thisPtr + 0x18) = newCapacity;   // +0x18: updated capacity
  *(rsize_t *)((int)thisPtr + 0x14) = dataSize;   // +0x14: new length

  // Null-terminate at dataSize offset
  if (newCapacity < 0x10) {
    *(undefined1 *)((int)thisPtr + 4 + dataSize) = 0; // Inline buffer
  } else {
    *(undefined1 *)((int)dst + dataSize) = 0;          // Heap buffer
  }
  return;
}

// External helpers
extern void * allocateMemory(uint size, uint align);
extern void deallocateMemory(void *ptr);