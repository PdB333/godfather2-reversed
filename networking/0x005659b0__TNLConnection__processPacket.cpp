// FUNC_NAME: TNLConnection::processPacket
undefined4 __thiscall TNLConnection::processPacket(undefined4 param_1, undefined4 param_2)
{
  int iVar1;
  byte packetBuffer[128];
  
  iVar1 = FUN_00569bf0(*(undefined4 *)(this + 0x20), param_1, packetBuffer);
  if (iVar1 == 0) {
    return 0;
  }
  if (iVar1 == 2) {
    FUN_005655c0(packetBuffer, param_2);
    if ((char)param_2 == '\0') {
      return 0;
    }
  }
  else if (iVar1 == 3) {
    return 0;
  }
  return 1;
}