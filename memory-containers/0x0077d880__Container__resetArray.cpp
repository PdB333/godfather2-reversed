// FUNC_NAME: Container::resetArray
void __thiscall Container::resetArray(uint32_t *thisPtr)
{
  // Global sentinel value (likely an invalid handle or null pointer)
  uint32_t defaultHandle = DAT_00d5ccf8;
  
  // Get the current count stored at offset +0x30 (48 bytes)
  uint32_t count = thisPtr[0x30 / 4];
  
  if (count != 0) {
    if (count == 1) {
      // If only one element, just set count to 0 and return
      thisPtr[0x30 / 4] = 0;
      return;
    }
    
    uint32_t idx = 0;
    uint32_t *elementPtr = thisPtr; // Array starts at offset 0
    
    do {
      if (elementPtr != (uint32_t *)0x0) {
        // Each element is 12 bytes (3 uint32_t fields)
        elementPtr[0] = 0;                 // +0x00: Field1
        elementPtr[1] = 0;                 // +0x04: Field2
        elementPtr[2] = defaultHandle;     // +0x08: Field3 (set to global sentinel)
      }
      idx++;
      elementPtr += 3; // Advance to next element (3 * 4 bytes)
    } while (idx < count - 1);
  }
  
  // Reset count to 0
  thisPtr[0x30 / 4] = 0;
}