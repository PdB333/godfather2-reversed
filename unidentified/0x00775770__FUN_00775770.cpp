// FUNC_NAME: SomeClass::getSomeFlagOrState
uint __fastcall SomeClass::getSomeFlagOrState(int thisPtr)
{
  uint result = in_EAX & 0xffffff00; // Preserve upper bits from EAX (likely a default/fallback value)
  
  // Check if the pointer at +0x5C is non-null and not equal to 0x48 (likely a sentinel/invalid value)
  if ((*(int *)(thisPtr + 0x5C) != 0) && (*(int *)(thisPtr + 0x5C) != 0x48)) {
    // If the pointer is valid (non-zero), read a value from the pointed-to object at offset +0xD4
    // Shift right by 2 and mask to get bits [1..7] (clearing bit 0 and upper bits)
    return *(uint *)(*(int *)(thisPtr + 0x5C) + 0xD4) >> 2 & 0xFFFFFF01;
  }
  
  // Fallback: use a global/static value at address 0x0000011C (likely a global state or default)
  // Shift right by 2 and mask similarly
  result = uRam0000011c >> 2 & 0xFFFFFF01;
  
  return result;
}