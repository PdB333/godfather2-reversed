// FUNC_NAME: Entity::Entity
undefined4 * __fastcall Entity::Entity(undefined4 *this)
{
  // Call base class constructor or common initialization
  FUN_004737b0();
  
  // Set vtable pointer
  *this = &PTR_FUN_00d5ef08;
  
  // Initialize function pointers or callback tables
  this[0xf] = &PTR_LAB_00d5eef8;   // +0x3C
  this[0x12] = &PTR_LAB_00d5eef4;  // +0x48
  this[0x14] = &PTR_LAB_00d5eef0;  // +0x50
  
  // Zero out remaining fields
  this[0x16] = 0;  // +0x58
  this[0x17] = 0;  // +0x5C
  this[0x18] = 0;  // +0x60
  this[0x19] = 0;  // +0x64
  
  // Additional initialization
  FUN_006c1360();
  
  return this;
}