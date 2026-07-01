// FUNC_NAME: Entity::updateStateFlags
void __thiscall Entity::updateStateFlags(int *this)
{
  // Check if byte at offset +0xE0 is zero (e.g., m_isActive or m_initialized)
  if (*(char *)(this + 0xE0) == '\0') {
    // Call virtual function at vtable+0x98 (likely an initialization/update hook)
    (**(code **)(*this + 0x98))();
    
    // Set global game state or debug flag to 0x1B (27)
    g_gameState = 0x1B;
    
    // Clear bit 3 (0x8) in flags at offset +0xDF (e.g., m_flags)
    this[0xDF] = this[0xDF] & 0xFFFFfff7;
    
    // Call static helper function (e.g., debug logging or state change notification)
    FUN_008a4ae0(1);
    
    // Clear bit 1 (0x2) in flags
    this[0xDF] = this[0xDF] & 0xFFFFfffd;
  }
  
  // Always set byte at +0xE0 to 0 (mark as inactive/uninitialized)
  *(char *)(this + 0xE0) = 0;
  return;
}