// FUNC_NAME: Player::Player
undefined4 * __thiscall Player::Player(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor (likely EARSObject or Entity)
  FUN_00473f10(param_2);
  
  // Set vtable pointers for the Player class and its base interfaces
  *this = &Player_vtable;                     // +0x00: main vtable
  this[0xf] = &IUpdatable_vtable;            // +0x3C: IUpdatable interface vtable
  this[0x12] = &IRenderable_vtable;          // +0x48: IRenderable interface vtable
  this[0x14] = &IControllable_vtable;        // +0x50: IControllable interface vtable
  
  // Initialize player-specific fields to zero
  this[0x50] = 0;   // +0x140: playerState flags (e.g., bitfield for movement states)
  this[0x51] = 0;   // +0x144: some pointer/ID (e.g., crew ID)
  this[0x52] = 0;   // +0x148: another flag or reference count

  // Note: The second assignment to this[0x52] is likely a decompilation artifact
  // Actual code only assigns once.
  return this;
}