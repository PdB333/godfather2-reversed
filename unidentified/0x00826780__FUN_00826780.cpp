// FUNC_NAME: UnknownClass::vtableSwitchAndInit
void __fastcall func_00826780(undefined4 *thisPtr)
{
  // Set vtable pointers - this appears to be a constructor or initialization function
  // that switches from one vtable entry to another
  *thisPtr = &PTR_FUN_00d73510;        // +0x00: initial vtable pointer
  thisPtr[1] = &PTR_LAB_00d73500;      // +0x04: secondary vtable/data pointer

  // Call initialization function with some identifier/magic value
  FUN_004639e0(0xa8896ed8);

  // Update vtable pointers after initialization
  thisPtr[1] = &PTR_LAB_00e30fe0;      // +0x04: updated after init
  *thisPtr = &PTR_LAB_00d734f8;        // +0x00: final vtable pointer

  // Clear global variable (likely a singleton or manager flag)
  _DAT_0112db5c = 0;

  return;
}