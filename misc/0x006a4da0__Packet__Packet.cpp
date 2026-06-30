// FUNC_NAME: Packet::Packet
undefined4 * __thiscall Packet::Packet(undefined4 *this, uint packetType)
{
  // Call base class initialization or packet type setup (likely sets some flags or header)
  Packet::baseInit(packetType);

  // Set vtable pointer (PTR_FUN_00d5d768 is the vtable for this class)
  *this = &vtable_Packet;

  // Set pointers at offset 0x3C (0xF * 4) and 0x48 (0x12 * 4) - possibly to static buffers or function tables
  // PTR_LAB_00d5d758 and PTR_LAB_00d5d754 are likely global structures
  this[0xF] = &someGlobalStructure1;   // +0x3C
  this[0x12] = &someGlobalStructure2;  // +0x48

  // Initialize magic/sentinel values at offsets 0x50, 0x54, 0x58, 0x5C (likely for debugging or packet validation)
  // Values: 0xBADBADBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911
  this[0x14] = 0xBADBADBA;   // +0x50
  this[0x15] = 0xBEEFBEEF;   // +0x54
  this[0x16] = 0xEAC15A55;   // +0x58
  this[0x17] = 0x91100911;   // +0x5C

  // Clear a byte at offset 0x60 (0x18 * 4) - possibly a flag or state
  *(byte *)(this + 0x18) = 0;   // +0x60

  return this;
}