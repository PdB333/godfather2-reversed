// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x0046c590
  FUN_0046c590(param_2);
  
  // Set vtable pointer (likely for this class)
  *this = &PTR_FUN_00d734d4;
  
  // Set additional vtable pointers for interfaces or virtual bases
  this[0xf] = &PTR_LAB_00d734c4;  // +0x3C - secondary vtable
  this[0x12] = &PTR_LAB_00d734c0; // +0x48 - tertiary vtable
  
  // Initialize various fields to zero
  *(undefined2 *)(this + 0x17) = 0;  // +0x5C - short field
  *(undefined2 *)((int)this + 0x5e) = 0;  // +0x5E - short field
  *(undefined2 *)(this + 0x19) = 0;  // +0x64 - short field
  *(undefined2 *)((int)this + 0x66) = 0;  // +0x66 - short field
  *(undefined2 *)(this + 0x1b) = 0;  // +0x6C - short field
  *(undefined2 *)((int)this + 0x6e) = 0;  // +0x6E - short field
  
  // Initialize pointer fields to null
  this[0x14] = 0;  // +0x50
  this[0x15] = 0;  // +0x54
  this[0x16] = 0;  // +0x58
  this[0x18] = 0;  // +0x60
  this[0x1a] = 0;  // +0x68
  
  return this;
}