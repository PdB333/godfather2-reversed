// FUNC_NAME: unknown::packetConstructionMethod
undefined4 __thiscall FUN_005977e0(int this, undefined4 param2, int param3)
{
  int iVar1;
  int iVar2;
  undefined4 uStack_1c;
  int iStack_18;
  undefined4 *puStack_14;
  undefined4 uStack_10;
  undefined4 local_8;
  uint local_4;
  
  // Packet sequence number derived from param3, masked to 16-bit
  local_4 = param3 * 0x10 + 0xcU & 0xffff;
  uStack_10 = 2;
  puStack_14 = &local_8;
  local_8 = 0x210; // Possibly packet type or size constant
  uStack_1c = 0x597814; // String or data address
  iStack_18 = this;
  
  // Write to field at offset 0 (maybe stream or buffer object)
  (**(code **)(*DAT_01205590 + 0x10))(); // Virtual call through global vtable
  
  uStack_1c = 2;
  iVar2 = this + 2; // Offset 0x2 - likely buffer index or field
  (**(code **)(*DAT_01205590 + 0x10))(iVar2, &uStack_10);
  
  iVar1 = 4;
  (**(code **)(*DAT_01205590 + 0x10))(this + 4, &puStack_14, 4); // Write pointer at +0x4
  (**(code **)(*DAT_01205590 + 0x10))(this + 8, &uStack_1c); // Write value at +0x8
  (**(code **)(*DAT_01205590 + 0x10))(this + 0xc, iVar2, iVar1 << 4); // Write at +0xC with size 64?
  
  return 0x4c; // Return size or status
}