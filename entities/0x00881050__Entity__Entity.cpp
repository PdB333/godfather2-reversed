// FUNC_NAME: Entity::Entity
void __fastcall Entity::Entity(uint *this)
{
  uint flags;
  uint someGlobalArg;
  uint zero1;
  uint zero2;
  
  flags = this[0x1e];                                          // +0x78: flags field (bits: 0=?,5=?,6=?)
  this[0] = &Entity_vtable;                                    // +0x00: set vtable pointer
  this[0x14] = &Entity_funcPtr1;                               // +0x50: function pointer (likely event/update)
  this[0x17] = &Entity_labelPtr1;                              // +0x5C: another function pointer or vtable
  if (((flags >> 6 & 1) != 0) &&                              // Bit 6 set (e.g., isGhost)
      ((flags & 1) != 0 || ((flags >> 5 & 1) != 0)))         // Bit0 (isLocal?) OR Bit5 (isServer?)
  {
    zero1 = 0;
    zero2 = 0;
    someGlobalArg = DAT_0112add8;                               // Global singleton resource reference
    FUN_00408a00(&someGlobalArg, 0);                            // Register/initialize global resource
  }
  FUN_008825e0();                                               // Second-stage initialization (e.g., physics setup)
  return;
}