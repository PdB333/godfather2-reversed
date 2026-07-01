// FUNC_NAME: Player::Player
undefined4 * __thiscall Player::Player(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d81db0;  // Player vtable
  
  // Initialize member pointers
  this[0xf] = &PTR_LAB_00d81da0;   // +0x3C - some vtable/interface
  this[0x12] = &PTR_LAB_00d81d9c;  // +0x48 - another vtable
  this[0x14] = &PTR_LAB_00d81d98;  // +0x50 - vtable
  this[0x15] = &PTR_LAB_00d81d38;  // +0x54 - vtable
  this[0x16] = &PTR_LAB_00d81cd0;  // +0x58 - vtable
  
  // Call base class constructor
  FUN_009018b0();  // Sentient::Sentient() or similar base
  
  // If flag bit 0 is set, call placement delete (constructor failed)
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x230);  // operator delete(this, size)
  }
  
  return this;
}