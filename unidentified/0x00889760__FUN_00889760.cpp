// FUNC_NAME: SomeClass::constructor
int __thiscall SomeClass::constructor(int thisPtr, byte flags)
{
  // Call base class constructor or initialization function with members at +0x4 and +0x8
  FUN_00887870(*(undefined4 *)(thisPtr + 4), *(undefined4 *)(thisPtr + 8));
  
  // Initialize member at +0xC to 0
  *(undefined4 *)(thisPtr + 0xc) = 0;
  
  // If the count/size at +0x8 is greater than 1, call a cleanup or deallocation function
  if (1 < *(uint *)(thisPtr + 8)) {
    FUN_009c8f10(*(undefined4 *)(thisPtr + 4));
  }
  
  // If the low bit of flags is set, call a destructor or cleanup function on this object
  if ((flags & 1) != 0) {
    FUN_009c8eb0(thisPtr);
  }
  
  return thisPtr;
}