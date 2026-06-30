// FUNC_NAME: SomeClass::allocateSlot
int __thiscall SomeClass::allocateSlot(int thisPtr, ushort slotIndex)
{
  int result;
  uint eaxShifted;
  uint tempVar;
  undefined4 someValue;

  eaxShifted = in_EAX >> 8;
  if (slotIndex < 0x80) {
    // Calculate offset into slot array: slotIndex * 0xf8 + 0x5a0
    result = (uint)slotIndex * 0xf8 + 0x5a0 + thisPtr;
    tempVar = FUN_005e9d10(); // likely checks if slot is available or validates state
    if ((tempVar != 0) && (*(int *)(thisPtr + 0x580) != 0)) {
      // Slot is available, initialize it
      FUN_00c9eac0(); // some initialization routine
      FUN_00c9cd40(1, 0); // set some flag or parameter
      someValue = FUN_00c9eb20(); // get some resource handle
      *(undefined4 *)(result + 0xe0) = someValue; // store handle at slot+0xe0
      FUN_00c9eae0(); // cleanup or finalize initialization
      FUN_005efb60(); // another setup function
      *(undefined4 *)(result + 0xdc) = 0; // clear slot+0xdc
      *(undefined4 *)(result + 0xe0) = 0; // clear slot+0xe0
      *(undefined4 *)(result + 0xe4) = 0; // clear slot+0xe4
      return 1; // success
    }
    eaxShifted = tempVar >> 8;
  }
  return eaxShifted << 8; // return failure code
}