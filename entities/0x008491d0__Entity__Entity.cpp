// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(undefined4 *this, undefined4 entityArg)
{
  // +0x00: vtable pointer (set to vtable for Entity)
  // +0x3C: secondary vtable (likely for network interface)
  // +0x48: tertiary vtable (likely for animation or scripting interface)
  // +0x50..0x7C: various zeroed fields (likely transform, flags, etc.)
  // +0x80: halfword field (e.g., entity type or state)
  // +0x82: another halfword (e.g., sub-state)
  // +0x84..0x9C: more zeroed fields (position/rotation components)
  // +0xA0, +0xA8: a default floating-point value (maybe 1.0 or similar)
  // +0xA4, +0xAC: another default value (maybe 0.0 or similar)
  // +0xB0, +0xB4: other zeroed fields (e.g., padding or counters)

  undefined4 uVar1;
  undefined4 uVar2;

  FUN_0046c590(entityArg);  // base class constructor (e.g., EARSObject)
  
  // Load global default constants
  uVar2 = DAT_00d74cd0;  // likely a float constant (e.g., 1.0f)
  uVar1 = DAT_00d60d0c;  // likely another float constant (e.g., 0.0f)

  // Initialize vtable pointers
  this[0] = &PTR_FUN_00d74cb4;      // main vtable
  this[0xf] = &PTR_LAB_00d74ca4;    // secondary vtable
  this[0x12] = &PTR_LAB_00d74ca0;   // tertiary vtable

  // Zero out a large block of members (offset +0x50 to +0x7C)
  this[0x14] = 0;
  this[0x15] = 0;
  this[0x16] = 0;
  this[0x17] = 0;
  this[0x18] = 0;
  this[0x19] = 0;
  this[0x1a] = 0;
  this[0x1b] = 0;
  this[0x1c] = 0;
  this[0x1d] = 0;
  this[0x1e] = 0;
  this[0x1f] = 0;

  // Halfword fields at +0x80 and +0x82
  *(undefined2 *)(this + 0x20) = 0;   // halfword at +0x80
  *(undefined2 *)((int)this + 0x82) = 0; // halfword at +0x82

  // More zeroed fields at +0x84..+0x9C
  this[0x21] = 0;
  this[0x22] = 0;
  this[0x23] = 0;
  this[0x24] = 0;
  this[0x25] = 0;
  this[0x26] = 0;
  this[0x27] = 0;

  // Set default constants (e.g., near/far plane, scale factors)
  this[0x28] = uVar2;   // +0xA0
  this[0x2a] = uVar2;   // +0xA8
  this[0x29] = uVar1;   // +0xA4
  this[0x2b] = uVar1;   // +0xAC

  // Final zeroed fields
  this[0x2c] = 0;   // +0xB0
  this[0x2d] = 0;   // +0xB4

  return this;
}