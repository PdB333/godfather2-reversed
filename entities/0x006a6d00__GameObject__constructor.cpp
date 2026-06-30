// FUNC_NAME: GameObject::constructor
undefined4 * __thiscall GameObject::constructor(GameObject *this, undefined4 param_2)
{
  // Call base class constructor
  BaseClass::BaseClass(param_2);

  // Set vtable pointer
  this->vtable = &g_vtable_GameObject;

  // Set interface pointers (likely for multiple inheritance)
  this->iface1 = &g_interface1_GameObject; // +0x3C (offset 0x3C)
  this->iface2 = &g_interface2_GameObject; // +0x48 (offset 0x48)

  // Initialize two 16-bit fields to zero
  *(unsigned short *)(&this->field_0x54) = 0; // +0x54
  *(unsigned short *)((int)this + 0x56) = 0; // +0x56
  *(unsigned short *)(&this->field_0x5C) = 0; // +0x5C
  *(unsigned short *)((int)this + 0x5E) = 0; // +0x5E

  // Write debug magic numbers
  this->magic0 = 0xBADBADBA; // +0x60
  this->magic1 = 0xBEEFBEEF; // +0x64
  this->magic2 = 0xEAC15A55; // +0x68
  this->magic3 = 0x91100911; // +0x6C

  // Write a byte zero after magic region
  *(unsigned char *)(&this->field_0x70) = 0; // +0x70 (byte)

  // Clear the magic numbers
  this->magic3 = 0; // +0x6C
  this->magic2 = 0; // +0x68
  this->magic1 = 0; // +0x64
  this->magic0 = 0; // +0x60

  // Zero out additional fields
  this->field_0x50 = 0; // +0x50
  this->field_0x58 = 0; // +0x58

  return (undefined4 *)this;
}