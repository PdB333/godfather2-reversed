// Xbox PDB: EARS_Apt_UIHudEventQueue_UIHudEventQueue
// FUNC_NAME: UIHudEventQueue::constructor
undefined4 * __fastcall UIHudEventQueue::constructor(undefined4 *this)
{
  // Initialize vtable pointer
  this[1] = 1; // +0x04: some flag or count
  this[2] = 0; // +0x08: some pointer or value
  this[3] = &PTR_LAB_00d8afbc; // +0x0C: vtable or function pointer
  DAT_0112a67c = this; // Store singleton pointer
  *this = &PTR_FUN_00d8afc4; // +0x00: vtable pointer
  this[3] = &PTR_LAB_00d8afc0; // +0x0C: update vtable entry

  // Allocate pool for queue entries (0x2c bytes each, 10 entries)
  FUN_004de0b0(0x2c, 10, "UIHudEventQueue::QueueEntryPool", 0, 4);

  this[4] = &PTR_FUN_00d8afb4; // +0x10: another vtable/function pointer

  // Initialize queue data (offsets from +0x48 to +0x7C)
  this[0x12] = 0; // +0x48: head index
  this[0x13] = 0; // +0x4C: tail index
  this[0x14] = 0; // +0x50: count
  this[0x15] = 0; // +0x54: some flag
  this[0x16] = 0; // +0x58: some value
  *(undefined2 *)(this + 0x17) = 0; // +0x5C: short
  *(undefined2 *)(this + 0x18) = 0; // +0x60: short
  *(undefined2 *)((int)this + 0x62) = 0; // +0x62: short
  this[0x1d] = 0; // +0x74: some pointer
  this[0x1c] = 0; // +0x70: some pointer
  this[0x1b] = 0; // +0x6C: some pointer
  this[0x1a] = 0; // +0x68: some pointer
  this[0x19] = 0; // +0x64: some pointer
  this[0x1e] = 0; // +0x78: some pointer
  this[0x1f] = 0; // +0x7C: some pointer

  return this;
}