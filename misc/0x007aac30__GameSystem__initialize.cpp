// FUNC_NAME: GameSystem::initialize
void __thiscall GameSystem::initialize(GameSystem *this)
{
  // Set vtable pointers (likely for multiple inheritance or interface)
  this->vtable0 = &PTR_FUN_00d6baa0;   // +0x00: primary vtable
  this->vtable1 = &PTR_LAB_00d6ba9c;   // +0x04: secondary vtable

  // Call base class or registration function with a hash ID (0x7b80c13a)
  FUN_004639e0(0x7b80c13a);

  // Update secondary vtable pointer
  this->vtable1 = &PTR_LAB_00d6ba98;   // +0x04: updated vtable

  // Reset global singleton flag
  DAT_01129958 = 0;                     // Global flag indicating initialization state

  // Set primary vtable to final value
  this->vtable0 = &PTR_LAB_00e30fe0;   // +0x00: final vtable
}