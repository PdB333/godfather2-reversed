// FUNC_NAME: GameObject::GameObject
// EARS base game object constructor (size 0x180)
// Sets multiple vtable pointers for multiple inheritance.
undefined4* __thiscall GameObject::GameObject(undefined4* this, byte allocateFlag)
{
  // Set main vtable at offset 0
  *this = &PTR_FUN_00d80008;
  // +0x3C: vtable for first additional base
  this[0xf] = &PTR_LAB_00d7fff8;
  // +0x48: vtable for second additional base
  this[0x12] = &PTR_LAB_00d7fff4;
  // +0x50: vtable for third additional base
  this[0x14] = &PTR_LAB_00d7fff0;
  // +0x54: vtable for fourth additional base
  this[0x15] = &PTR_LAB_00d7ff90;
  // +0x58: vtable for fifth additional base
  this[0x16] = &PTR_LAB_00d7ff28;

  // Call base class constructor (likely initializes core base)
  FUN_0046ea20();

  // If allocation flag bit0 set, call deallocation function (for new/delete handling)
  if ((allocateFlag & 1) != 0) {
    FUN_0043b960(this, 0x180);
  }
  return this;
}