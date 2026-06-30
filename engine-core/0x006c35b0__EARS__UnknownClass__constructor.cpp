// FUNC_NAME: EARS::UnknownClass::constructor
// Address: 0x006c35b0
// Reconstructed constructor for an EARS framework class.
// Sets vtable, handles sub-object at offset 0xE8, calls global init, optionally allocates memory and calls a function via the allocation's vtable.

undefined4 * __thiscall EARS::UnknownClass::constructor(UnknownClass *this, byte allocateFlag)
{
  int *mem;

  // Set vtable pointer (virtual function table at 0x00d5ef34)
  this->vtable = (void **)&PTR_FUN_00d5ef34; // +0x00
  // Set another pointer (likely a data pointer at 0x00d5ef2c)
  this->somePointer = (void *)&PTR_LAB_00d5ef2c; // +0x08

  // If the sub-object pointer at offset 0xE8 is not null, release it
  if (this->field_0xE8 != 0) {
    FUN_004daf90(this + 0xE8); // cleanup/release function
  }

  // Global initialization call (possibly engine-level setup)
  FUN_006c9820();

  // If the low bit of allocateFlag is set, allocate a block and call a function via its vtable
  if ((allocateFlag & 1) != 0) {
    mem = (int *)FUN_009c8f80(); // allocate memory (likely operator new or memory pool)
    // Call the second virtual function (offset 4) on the newly allocated block,
    // passing 'this' and size 0x310 as arguments.
    // This may be a placement constructor/initializer or a registration call.
    (**(void (**)(void *, int))(*mem + 4))(this, 0x310);
  }

  return this;
}