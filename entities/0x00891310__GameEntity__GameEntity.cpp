// FUNC_NAME: GameEntity::GameEntity
undefined4 * __thiscall GameEntity::GameEntity(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor (likely Entity or similar)
  Entity::constructor(param_2);  // FUN_0046c590

  // Set vtable pointers (multiple inheritance / interface)
  // +0x00: Primary vtable pointer
  *this = &vtable_GameEntity_Primary;  // PTR_FUN_00d77790

  // +0x3C: Secondary vtable pointer
  this[0xF] = &vtable_GameEntity_Secondary;  // PTR_LAB_00d77780

  // +0x48: Third vtable pointer
  this[0x12] = &vtable_GameEntity_Tertiary;  // PTR_LAB_00d7777c

  // +0x50: Fourth vtable pointer (overwrites earlier assignment)
  this[0x14] = &vtable_GameEntity_Quaternary;  // PTR_LAB_00d77778

  // --- Field initialization (zeroing out large block) ---

  // +0x50: Initial vtable (overwritten above)
  this[0x14] = &vtable_GameEntity_Fifth;  // PTR_LAB_00e32854  // Note: overwritten later

  // +0x54: Pointer/flag (zero)
  this[0x15] = 0;

  // +0x58: Word (zero)
  *(undefined2 *)(this + 0x16) = 0;

  // +0x5A: Word (zero)
  *(undefined2 *)((int)this + 0x5A) = 0;

  // +0x5C: Pointer (zero)
  this[0x17] = 0;

  // +0x60: Word (zero)
  *(undefined2 *)(this + 0x18) = 0;

  // +0x62: Word (zero)
  *(undefined2 *)((int)this + 0x62) = 0;

  // +0x64: Pointer (zero)
  this[0x19] = 0;

  // +0x68: Word (zero)
  *(undefined2 *)(this + 0x1A) = 0;

  // +0x6A: Word (zero)
  *(undefined2 *)((int)this + 0x6A) = 0;

  // +0x6C: Pointer (zero)
  this[0x1B] = 0;

  // +0x70: Word (zero)
  *(undefined2 *)(this + 0x1C) = 0;

  // +0x72: Word (zero)
  *(undefined2 *)((int)this + 0x72) = 0;

  // +0x74: Pointer (zero)
  this[0x1D] = 0;

  // +0x78: Word (zero)
  *(undefined2 *)(this + 0x1E) = 0;

  // +0x7A: Word (zero)
  *(undefined2 *)((int)this + 0x7A) = 0;

  // +0x80: Pointer (zero)
  this[0x20] = 0;

  // +0x84: Pointer (zero)
  this[0x21] = 0;

  // +0x88: Pointer (zero)
  this[0x22] = 0;

  // +0x8C: Pointer (zero)
  this[0x23] = 0;

  // +0x90: Pointer (zero)
  this[0x24] = 0;

  // +0x94: Pointer (zero)
  this[0x25] = 0;

  // +0x118: Pointer (zero)
  this[0x46] = 0;

  // +0x160: Pointer (zero)
  this[0x58] = 0;

  // +0x170: Pointer (zero)
  this[0x5C] = 0;

  // +0x174: Pointer (zero)
  this[0x5D] = 0;

  // +0x178: Sentinel value (debug marker)
  this[0x5E] = 0xBADBADBA;

  // +0x17C: Sentinel value (debug marker)
  this[0x5F] = 0xBEEFBEEF;

  // +0x180: Sentinel value (debug marker)
  this[0x60] = 0xEAC15A55;

  // +0x184: Sentinel value (debug marker)
  this[0x61] = 0x91100911;

  // +0x16C: Pointer (zero)
  this[0x5B] = 0;

  // +0x168: Pointer (zero)
  this[0x5A] = 0;

  // +0x164: Pointer (zero)
  this[0x59] = 0;

  // +0x98: Byte (zero)
  *(undefined1 *)(this + 0x26) = 0;

  // +0xD8: Byte (zero)
  *(undefined1 *)(this + 0x36) = 0;

  // +0x11C: Byte (zero)
  *(undefined1 *)(this + 0x47) = 0;

  // +0x7C: Pointer (zero)
  this[0x1F] = 0;

  return this;
}