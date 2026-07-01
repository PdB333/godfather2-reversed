// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor (likely SimObject or EARSObject)
  FUN_0046c590(param_2);

  // Set vtable pointer (main class vtable)
  *this = &PTR_FUN_00d80f10;

  // Set additional vtable pointers for interfaces (offsets +0x3C and +0x48)
  this[0xf] = &PTR_LAB_00d80f00;  // +0x3C: interface vtable 1
  this[0x12] = &PTR_LAB_00d80efc; // +0x48: interface vtable 2

  // Set byte flag at +0x50 to 1 (e.g., m_bActive)
  *(undefined1 *)(this + 0x14) = 1;  // +0x50: byte flag

  // Zero out a block of fields from +0xA0 to +0xAE
  this[0x28] = 0;                    // +0xA0: dword
  *(undefined2 *)(this + 0x29) = 0;  // +0xA4: word
  *(undefined2 *)((int)this + 0xa6) = 0; // +0xA6: word
  this[0x2a] = 0;                    // +0xA8: dword
  *(undefined2 *)(this + 0x2b) = 0;  // +0xAC: word
  *(undefined2 *)((int)this + 0xae) = 0; // +0xAE: word

  // Call some initialization routine
  FUN_007dcae0();

  // Copy global value into four fields (e.g., m_pParent, m_pOwner, etc.)
  undefined4 uVar1 = _DAT_00d5780c;  // Global sentinel or handle
  this[0x27] = _DAT_00d5780c;        // +0x9C
  this[0x22] = uVar1;                // +0x88
  this[0x1d] = uVar1;                // +0x74
  this[0x18] = uVar1;                // +0x60

  // Zero out remaining fields from +0x64 to +0x98
  this[0x1b] = 0;  // +0x6C
  this[0x1c] = 0;  // +0x70
  this[0x1a] = 0;  // +0x68
  this[0x19] = 0;  // +0x64
  this[0x1f] = 0;  // +0x7C
  this[0x21] = 0;  // +0x84
  this[0x20] = 0;  // +0x80
  this[0x1e] = 0;  // +0x78
  this[0x23] = 0;  // +0x8C
  this[0x26] = 0;  // +0x98
  this[0x25] = 0;  // +0x94
  this[0x24] = 0;  // +0x90

  return this;
}