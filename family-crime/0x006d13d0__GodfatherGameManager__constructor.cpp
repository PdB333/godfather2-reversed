// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __thiscall GodfatherGameManager::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  FUN_00473840(param_2);
  
  // Set vtable pointer at +0x58 (0x16 * 4)
  this[0x16] = &PTR_LAB_00d5f2f0;
  
  // Store singleton instance pointer at global DAT_0112a874
  DAT_0112a874 = this;
  
  // Set vtable pointer at +0x0
  *this = &PTR_FUN_00d5f32c;
  
  // Set additional vtable-like pointers at various offsets
  this[0xf] = &PTR_LAB_00d5f31c;  // +0x3C
  this[0x12] = &PTR_LAB_00d5f318; // +0x48
  this[0x14] = &PTR_LAB_00d5f314; // +0x50
  this[0x16] = &PTR_LAB_00d5f310; // +0x58 (overwrites previous assignment)
  
  // Initialize member at +0x5C to null
  this[0x17] = 0;
  
  return this;
}