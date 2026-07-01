// FUNC_NAME: SomeClass::clearPendingAction
void __fastcall SomeClass::clearPendingAction(int this)
{
  // Check if bit 1 (0x2) of the flags at offset 0x1a4 is set
  if ((*(byte *)(this + 0x1a4) & 2) != 0) {
    // Call the function to handle the pending action
    FUN_0081cf20(this);
    // Clear bit 1 (0x2) from the flags at offset 0x1a4
    *(uint *)(this + 0x1a4) = *(uint *)(this + 0x1a4) & 0xfffffffd;
  }
  return;
}