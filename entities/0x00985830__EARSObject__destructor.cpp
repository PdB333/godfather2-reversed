// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::destructor(EARSObject *this)
{
  // Set vtable pointer to base class vtable
  this->vtable = &PTR_FUN_00d90c78;
  this[4] = &PTR_LAB_00d90c54; // +0x10: secondary vtable or interface pointer
  this[0x13] = &PTR_LAB_00d90c50; // +0x4C: another vtable/interface

  // Check if bit 2 of byte at +0x68 is set (some flag)
  if ((*(byte *)(this + 0x1a) >> 2 & 1) != 0) {
    // Clear bit 2 at global address +0x10
    *(uint *)(DAT_011298d4 + 0x10) = *(uint *)(DAT_011298d4 + 0x10) & 0xfffffffb;
    FUN_00912030(); // Likely some cleanup or unregister function
    // Clear bit 2 in the word at +0x68
    *(ushort *)(this + 0x1a) = *(ushort *)(this + 0x1a) & 0xfffb;
  }
  this[0x13] = &PTR_LAB_00d90bc8; // +0x4C: set to another vtable
  DAT_0112e228 = 0; // Global flag reset
  FUN_005c16e0(); // Likely memory deallocation or final cleanup
  return;
}