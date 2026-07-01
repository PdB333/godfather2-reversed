// FUNC_NAME: BaseGameObject::constructor
undefined4 * __thiscall BaseGameObject::constructor(undefined4 *this, int allocateFlag)
{
  undefined4 uVar1;

  if (allocateFlag == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00481610();  // allocator / memory allocation
  }

  FUN_0064d390(1, 1);      // base initialization, e.g., reference count, flags
  *this = &PTR_LAB_00e317dc;             // vtable for base class (temporary)
  this[6] = 0;                           // offset +0x18: some flag/pointer
  FUN_00454a10(uVar1);                   // attach allocated resource if any
  this[9] = 1;                           // offset +0x24: count/state
  *this = &PTR_LAB_00d79ea4;             // vtable for derived class / actual vtable
  this[10] = &PTR_LAB_00d79bd8;          // offset +0x28: secondary vtable / interface
  this[0xc] = &LAB_008a89d0;             // offset +0x30: virtual function pointer (e.g., destructor)
  this[0xd] = 0;                         // offset +0x34: null terminator / sentinel
  this[5] = this + 10;                   // offset +0x14: points to itself at +0x28 (self-referential link)
  return this;
}