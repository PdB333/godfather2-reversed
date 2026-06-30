// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(undefined4 *this, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
  // Set entity type to 2 (e.g., static object, building, etc.)
  *this = 2;

  // Call base class constructor (likely Entity base initialization)
  FUN_006da9d0();

  // Clear flags at offsets +0x40 and +0x48 (since each offset is 4 bytes)
  this[0x10] = 0;  // +0x40: some state/flag
  this[0x12] = 0;  // +0x48: another state/flag

  // Store parameters into specific fields
  this[0x13] = param_3;  // +0x4C: e.g., subtype or data pointer
  this[0x14] = param_4;  // +0x50: e.g., x-coordinate or uint
  this[0x11] = param_2;  // +0x44: e.g., model handle or enum
  this[0x15] = param_5;  // +0x54: e.g., y-coordinate or identifier

  // Copy global singleton/renderer references into the entity
  this[5] = DAT_00e50dfc;  // +0x14: pointer to resource manager
  this[6] = DAT_00e50e00;  // +0x18: pointer to renderer/manager

  // Clear byte at offset +0x04 (e.g., a flag or small state)
  *(undefined1 *)(this + 4) = 0;

  return this;
}