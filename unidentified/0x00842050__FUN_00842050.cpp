// FUNC_NAME: UnknownClass::DestructorOrCleanup
undefined4 * __thiscall UnknownClass::DestructorOrCleanup(undefined4 *thisPtr, byte flags)
{
  // vtable setup: Point to whatever vtable is at PTR_FUN_00d74820
  *thisPtr = &PTR_FUN_00d74820;
  // Set a data pointer to PTR_LAB_00d747f8
  thisPtr[1] = &PTR_LAB_00d747f8;

  // Cleanup: if any of slots 0xf,0x10,0x11 (likely pointers to sub-objects) are non-null, free/release them
  if (thisPtr[0xf] != (undefined4 *)0x0) {
    FUN_00848cc0();
  }
  if (thisPtr[0x10] != (undefined4 *)0x0) {
    FUN_00848cc0();
  }
  if (thisPtr[0x11] != (undefined4 *)0x0) {
    FUN_00848cc0();
  }

  // Call a global cleanup routine (likely operator delete or similar)
  FUN_00596640();

  // Update vtable to PTR_LAB_00d74620 (base class pointer?)
  *thisPtr = &PTR_LAB_00d74620;

  // If flags bit 0 is set, delete this object (calling operator delete via FUN_00840230)
  if ((flags & 1) != 0) {
    FUN_00840230(thisPtr);
  }

  return thisPtr;
}