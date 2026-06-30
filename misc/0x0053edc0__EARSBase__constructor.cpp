// FUNC_NAME: EARSBase::constructor
undefined4 * __thiscall EARSBase::constructor(undefined4 *this, byte allocFlag)
{
  // Set vtable pointer at offset 0
  *this = &PTR_FUN_00e3918c; // VTable for base class
  // Set additional function tables at offsets 8 and 12 (0x8 and 0xC)
  this[2] = &PTR_LAB_00e391a0; // Derived class metatable or interface
  this[3] = &PTR_LAB_00e391a8; // Another function table
  // Call base initialization routine
  FUN_00a0ea60(); // Likely initializes static data or registers class
  // If the allocFlag parameter has bit 0 set, allocate additional storage from TLS heap
  if ((allocFlag & 1) != 0) {
    // Get thread-local storage base pointer (TLS index stored at 0x01139810)
    void *tlsBase = TlsGetValue(DAT_01139810);
    // Call a constructor or initializer on this, using some field at offset 4 (this[1])
    // and size 0xd (13 bytes)
    FUN_00aa26e0(this, *(undefined2 *)(this + 1), 0xd); // Possibly allocates and attaches a sub-object
  }
  return this;
}