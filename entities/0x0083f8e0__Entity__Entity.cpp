// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(undefined4 *this, undefined4 initData)
{
  // Call base class constructor (likely SimObject or similar)
  FUN_0083fb90(initData);

  // Initialize fields at offsets 0x50, 0x54, 0x58 to zero
  this[0x14] = 0; // +0x50: m_flags or m_state
  this[0x15] = 0; // +0x54: m_counter or m_timer
  this[0x16] = 0; // +0x58: m_unknown

  // Set vtable pointer for this class
  *this = &PTR_FUN_00d74490; // +0x00: vtable for Entity

  // Set additional vtable pointers for base classes/interfaces
  this[0xf] = &PTR_LAB_00d74480; // +0x3C: vtable for first base (e.g., NetReflectable)
  this[0x12] = &PTR_LAB_00d7447c; // +0x48: vtable for second base (e.g., SimObject)

  return this;
}