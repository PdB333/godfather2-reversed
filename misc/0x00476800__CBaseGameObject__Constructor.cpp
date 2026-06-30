// FUNC_NAME: CBaseGameObject::Constructor
undefined4 * __thiscall CBaseGameObject::Constructor(undefined4 *this, undefined4 *pConfig)
{
  // Call base constructor with config
  BaseClass::Constructor(pConfig);
  
  // Set vtable pointer
  *this = &PTR_FUN_00e32ecc;
  
  // Initialize internal pointers (likely secondary vtable or interface pointers)
  this[0xf] = &PTR_LAB_00e32ee8; // +0x3C
  this[0x12] = &PTR_LAB_00e32ef8; // +0x48
  
  // Clear various fields
  this[0x14] = 0;               // +0x50 (int)
  *(undefined2 *)(this + 0x15) = 0; // +0x54 (short)
  *(undefined2 *)((int)this + 0x56) = 0; // +0x56 (short)
  this[0x16] = 0;               // +0x58 (int)
  *(undefined2 *)(this + 0x17) = 0; // +0x5C (short)
  *(undefined2 *)((int)this + 0x5E) = 0; // +0x5E (short)
  this[0x19] = 0;               // +0x64 (int)
  
  // Set default invalid index and active flag
  this[0x18] = 0xFFFFFFFF;      // +0x60 (int, invalid ID)
  this[0x1A] = 1;               // +0x68 (int, flag)
  
  return this;
}