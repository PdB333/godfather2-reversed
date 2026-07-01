// FUNC_NAME: UnknownBaseClass::constructor

undefined4 * __thiscall UnknownBaseClass::constructor(UnknownBaseClass *this, byte allocFlag)
{
  // Set vtable pointer at start of object
  *this = &PTR_FUN_00d69654;
  // Set additional vtable or interface pointers at offsets 0x3C and 0x48 (0xF and 0x12 words)
  this[0xF] = &PTR_LAB_00d69644;  // +0x3C
  this[0x12] = &PTR_LAB_00d69640; // +0x48

  // Call base class or member initializer
  FUN_0046c640();

  // If object was heap allocated (allocFlag & 1), set up cleanup handler
  if ((allocFlag & 1) != 0) {
    FUN_0043b960(this, 0x94);  // Register for deletion with size 0x94
  }

  return this;
}