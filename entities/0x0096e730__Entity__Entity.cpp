// FUNC_NAME: Entity::Entity
undefined4 * __fastcall Entity::Entity(undefined4 *this)
{
  // Call base class constructor
  FUN_005bf9b0(); // Likely base class constructor or initialization
  
  // Set vtable pointer at offset 0x00
  *this = &PTR_FUN_00d8ec78; // Primary virtual table
  
  // Set secondary vtable or interface pointer at offset 0x10 (param_1[4])
  this[4] = &PTR_LAB_00d8ec54; // Secondary vtable / interface table
  
  return this;
}