// FUNC_NAME: EARSBaseObject::EARSBaseObject

// Constructor for a base EA EARS engine object.
// Initializes vtable, debug sentinel fields, a bool flag, and calls sub-initializers.
// Offsets are from object start (size unknown, likely > 0xB8 bytes).
undefined4* __fastcall EARSBaseObject::EARSBaseObject(undefined4* this)
{
  // Call base class constructor (likely EARSObject or similar)
  FUN_008334a0();

  // Set vtable pointer
  this[0] = &PTR_FUN_00d73398;                    // +0x00: vtable

  // Debug sentinel fields to detect memory corruption
  this[0x28] = 0xBADBADBA;                        // +0xA0: sentinel1
  this[0x29] = 0xBEEFBEEF;                        // +0xA4: sentinel2
  this[0x2A] = 0xEAC15A55;                        // +0xA8: sentinel3
  this[0x2B] = 0x91100911;                        // +0xAC: sentinel4
  this[0x2C] = 0;                                  // +0xB0: unknown (zeroed)
  this[0x2D] = 0;                                  // +0xB4: unknown (zeroed)
  *(byte*)((int)this + 0x48) = 0;                  // +0x48: bool flag (e.g., initialized)

  // Call post-initialization (e.g., member setup)
  FUN_008202d0();

  return this;
}