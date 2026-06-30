// FUNC_NAME: NetSession::processIncomingPacket
void NetSession::processIncomingPacket(void)
{
  undefined4 *packetData;
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *local_14;
  undefined1 auStack_10 [4];
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (*(char *)(packetData + 10) == '\0') {
    FUN_0060c430();
    return;
  }
  if (packetData[0xb] == 0) {
    local_c = 2;
    local_8 = 0x10;
    local_4 = 0;
    puVar1 = (undefined4 *)(**(code **)*DAT_01205868)(0x40,&local_c);
    puVar4 = puVar1;
    for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *packetData;
      packetData = packetData + 1;
      puVar4 = puVar4 + 1;
    }
    puVar1[0xb] = puVar1;
    packetData = puVar1;
  }
  local_14 = packetData;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_012224f8);
  if (DAT_012224e0 != (int *)0x0) {
    piVar2 = DAT_012224e0;
    do {
      if ((uint)packetData[8] < *(uint *)(*piVar2 + 0x20)) {
        FUN_0060d480(auStack_10,&local_14);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_012224f8);
        return;
      }
      piVar2 = (int *)piVar2[1];
    } while (piVar2 != (int *)0x0);
  }
  FUN_0060d370(&local_14);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_012224f8);
  return;
}