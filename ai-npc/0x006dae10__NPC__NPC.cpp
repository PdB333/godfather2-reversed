// FUNC_NAME: NPC::NPC
undefined4 * __thiscall NPC::NPC(undefined4 *this, byte allocFlag)
{
  // Set vtable pointers for multiple base classes
  this[0x0] = &PTR_FUN_00e32b30;                     // primary vtable (offset 0)
  this[0xf] = &PTR_LAB_00e32b50;                     // vtable for base class at offset 0x3C
  this[0x12] = &PTR_LAB_00e32b60;                    // vtable for base class at offset 0x48
  this[0x14] = &PTR_LAB_00e32854;                    // vtable for base class at offset 0x50 (overwrites earlier assignment)
  // Call base class constructor (e.g., Sentient constructor)
  Sentient::Sentient();
  // If the allocator flag indicates heap allocation, call operator delete on failure?
  // This pattern is used in EA's custom allocator to free memory if construction fails.
  if ((allocFlag & 1) != 0) {
    operatorDelete(this, 0xb8);                      // size of NPC object = 184 bytes
  }
  return this;
}