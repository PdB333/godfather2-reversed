// FUNC_NAME: addElementWithBoundsCheck
void __fastcall addElementWithBoundsCheck(int *arrayDesc, int handle, void *source)
{
  // arrayDesc points to an array descriptor:
  //   +0x00: base offset (subtracted from handle to compute index)
  //   +0x04: capacity (maximum number of elements)
  // handle is passed in EAX, source pointer in ESI
  // Element size is 12 bytes (8 + 4).
  // FUN_00498b60 = allocateElement (returns new 12-byte block)
  // FUN_00498b10 = triggerAssert (error / out-of-bounds handler)

  if (handle == 0) {
    void *newElement = allocateElement();
    // Copy 12 bytes from source to newElement
    *(uint64_t *)newElement = *(uint64_t *)source;
    *(uint32_t *)((char *)newElement + 8) = *(uint32_t *)((char *)source + 8);
    return;
  }

  uint computedIndex = (uint)((handle - arrayDesc[0]) / 12);
  if (computedIndex < (uint)arrayDesc[1]) {
    void *newElement = allocateElement();
    *(uint64_t *)newElement = *(uint64_t *)source;
    *(uint32_t *)((char *)newElement + 8) = *(uint32_t *)((char *)source + 8);
    return;
  }

  triggerAssert();
}