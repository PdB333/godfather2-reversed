// FUNC_NAME: Player::Player
undefined4 * __thiscall Player::Player(Player *this, byte isHeapAllocated)
{
  // Set vtable pointers for multiple inheritance
  // Main vtable at offset 0
  *(void **)this = &PTR_FUN_00d81a60;
  // Secondary vtable at offset 0x3C (0xF * 4)
  *(void **)((char *)this + 0x3C) = &PTR_LAB_00d81a50;
  // Tertiary vtable at offset 0x48 (0x12 * 4)
  *(void **)((char *)this + 0x48) = &PTR_LAB_00d81a4c;
  // Fourth vtable at offset 0x50 (0x14 * 4)
  *(void **)((char *)this + 0x50) = &PTR_LAB_00d81a48;
  // Fifth vtable at offset 0x54 (0x15 * 4)
  *(void **)((char *)this + 0x54) = &PTR_LAB_00d819e8;
  // Sixth vtable at offset 0x58 (0x16 * 4)
  *(void **)((char *)this + 0x58) = &PTR_LAB_00d81980;

  // Call base class constructors / initialization functions
  // Likely Sentient::Sentient(this) and PlayerActionableInfo::PlayerActionableInfo(this)
  FUN_00903a40(this);
  FUN_004c0f60(this);

  // If heap-allocated, call cleanup function (possibly to free memory on failure)
  // Note: This is called unconditionally after construction, which is unusual.
  // Possibly a custom allocator pattern.
  if ((isHeapAllocated & 1) != 0) {
    FUN_0043b960(this, 0x230); // size = 0x230 bytes
  }

  return this;
}