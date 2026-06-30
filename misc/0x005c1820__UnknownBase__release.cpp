// FUNC_NAME: UnknownBase::release
void __thiscall UnknownBase::release(int *thisPtr)
{
  // Check if the object is flagged as active (bit 1 at offset +0x4a)
  if ((*(byte *)((int)thisPtr + 0x4a) & 2) != 0) {
    // Perform pre-cleanup (e.g., decrement reference, notify observers)
    FUN_005c0b40();

    // Save child object pointer at +0x28 (thisPtr[10])
    int childObj = thisPtr[10];

    // Reset counters/state at +0x30 and +0x2C
    thisPtr[0xc] = 0;   // +0x30
    thisPtr[0xb] = 0;   // +0x2C

    // Release the child object if it exists
    if (childObj != 0) {
      // Call vtable[1] on the child object (likely a release/destructor)
      // DAT_012234ec is a global vtable pointer; retrieve function from +4 offset
      (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(childObj, 0);
    }
    thisPtr[10] = 0;    // +0x28 clear child pointer

    // Call virtual function at vtable+4 (e.g., onStop, onCleanup)
    (**(code **)(*thisPtr + 4))();

    // Zero out two more fields: +0x20 and +0x24
    thisPtr[8] = 0;     // +0x20
    thisPtr[9] = 0;     // +0x24

    // Perform post-cleanup (e.g., decrement global counter, destroy)
    FUN_005c08f0();

    // Clear the active flag (bit 1 at +0x4a)
    *(ushort *)((int)thisPtr + 0x4a) = *(ushort *)((int)thisPtr + 0x4a) & 0xfffd;
  }
}