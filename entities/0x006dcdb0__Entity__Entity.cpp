// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(undefined4 *this, undefined4 initData)
{
  // Call base initialization with initData (likely a resource or parent pointer)
  FUN_00473840(initData);

  // Set primary vtable pointer
  *this = &PTR_FUN_00d5f678;

  // Set secondary vtable pointers for multiple interfaces (offsets: 0x3C, 0x48, 0x50)
  this[0xf] = &PTR_LAB_00d5f668;  // offset +0x3C
  this[0x12] = &PTR_LAB_00d5f664; // offset +0x48
  this[0x14] = &PTR_LAB_00d5f660; // offset +0x50

  // Zero out four fields at offsets +0x58, +0x5C, +0x60, +0x64
  this[0x16] = 0;
  this[0x17] = 0;
  this[0x18] = 0;
  this[0x19] = 0;

  // Call base class constructor or common initialization
  FUN_006dc940();

  return this;
}