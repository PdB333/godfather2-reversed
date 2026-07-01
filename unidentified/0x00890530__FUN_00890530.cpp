// FUNC_NAME: SomeClass::constructor
int __thiscall SomeClass::constructor(int thisPtr, byte flags)
{
  // Call sub-constructor with fields at +0x04 and +0x08
  FUN_0088faf0(*(undefined4 *)(thisPtr + 4), *(undefined4 *)(thisPtr + 8));
  
  // Initialize field at +0x0C to 0
  *(undefined4 *)(thisPtr + 0xc) = 0;
  
  // If size/count at +0x08 is greater than 1, call cleanup function
  if (1 < *(uint *)(thisPtr + 8)) {
    FUN_009c8f10(*(undefined4 *)(thisPtr + 4));
  }
  
  // If flag bit 0 is set, call destructor
  if ((flags & 1) != 0) {
    FUN_009c8eb0(thisPtr);
  }
  
  return thisPtr;
}