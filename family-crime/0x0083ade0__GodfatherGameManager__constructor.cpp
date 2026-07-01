// FUNC_NAME: GodfatherGameManager::constructor
void __thiscall GodfatherGameManager::constructor(uint32_t *this)
{
  // Set vtable pointer (vtable at 0x00d741f0)
  this[0] = (uint32_t)&PTR_FUN_00d741f0;
  
  // Initialize function pointers at various offsets
  // Offset +0x3C (0xF * 4) - likely an array or function table
  this[0xF] = (uint32_t)&PTR_LAB_00d741dc;
  // Offset +0x48 (0x12 * 4) - another function pointer
  this[0x12] = (uint32_t)&PTR_LAB_00d741d8;
  // Offset +0x158 (0x56 * 4) - first assignment, then overwritten
  this[0x56] = (uint32_t)&PTR_LAB_00d741d4;
  // Overwrite the same offset with a different pointer (perhaps a correction)
  this[0x56] = (uint32_t)&PTR_LAB_00d741d0;
  
  // Clear global initialization flag
  DAT_0112aff0 = 0;
  
  // Call secondary initialization function
  FUN_0083f2f0();
  
  return;
}