// FUNC_NAME: BaseGameObject::BaseGameObject
undefined4 * __thiscall BaseGameObject::BaseGameObject(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor
  FUN_0046c590(param_2);
  
  // Set vtable pointer (base class vtable)
  *this = &PTR_FUN_00d7251c;  // +0x00: vtable pointer
  
  // Additional vtable pointers (likely for multiple inheritance or interface pointers)
  this[0xf] = &PTR_LAB_00d7250c;  // +0x3C: maybe secondary vtable
  this[0x12] = &PTR_LAB_00d72508; // +0x48: another interface vtable
  
  // Initialize fields
  this[0x14] = 0;                 // +0x50: some pointer or int
  *(short *)(this + 0x15) = 0;    // +0x54: short field
  *(short *)((int)this + 0x56) = 0; // +0x56: another short field
  
  // Debug sentinel values for uninitialized fields
  this[0x16] = 0xbadbadba;        // +0x58: sentinel
  this[0x17] = 0xbeefbeef;        // +0x5C: sentinel
  this[0x18] = 0xeac15a55;        // +0x60: sentinel (EA? maybe)
  this[0x19] = 0x91100911;        // +0x64: sentinel
  
  // Zero a byte at offset 0x68
  *(byte *)(this + 0x1a) = 0;     // +0x68: byte field
  
  return this;
}