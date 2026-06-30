// FUNC_NAME: TNLConnection::writePacketHeader
undefined4 __thiscall TNLConnection::writePacketHeader(int this, undefined4 param_2, int param_3)
{
  int iVar1;
  int iVar2;
  undefined4 uStack_1c;
  int iStack_18;
  undefined4 *puStack_14;
  undefined4 uStack_10;
  undefined4 local_8;
  uint local_4;
  
  local_4 = param_3 * 0x10 + 0xcU & 0xffff;
  uStack_10 = 2;
  puStack_14 = &local_8;
  local_8 = 0x201;
  uStack_1c = 0x597764;
  iStack_18 = this;
  (**(code **)(*DAT_01205590 + 0x10))();
  uStack_1c = 2;
  iVar2 = this + 2;
  (**(code **)(*DAT_01205590 + 0x10))(iVar2,&uStack_10);
  iVar1 = 4;
  (**(code **)(*DAT_01205590 + 0x10))(this + 4,&puStack_14,4);
  (**(code **)(*DAT_01205590 + 0x10))(this + 8,&uStack_1c);
  (**(code **)(*DAT_01205590 + 0x10))(this + 0xc,iVar2,iVar1 << 4);
  return 0x4c;
}