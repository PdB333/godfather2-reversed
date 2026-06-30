// FUNC_NAME: NetSession::processTimedOutConnections
void NetSession::processTimedOutConnections(void)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  
  iVar1 = DAT_0119a9cc; // gNetSession singleton
  iVar4 = 0;
  iVar5 = 0;
  puVar6 = (undefined4 *)(DAT_0119a9cc + 0x251c); // +0x251c: connection array start
  do {
    if (iVar4 == *(int *)(iVar1 + 0x3018)) { // +0x3018: connectionCount
      return;
    }
    if (puVar6[-1] != 0) { // puVar6[-1] = connection active flag
      iVar4 = iVar4 + 1;
      iVar2 = FUN_005a3ae0(); // getCurrentTime()
      iVar3 = FUN_005a3f20(); // getTimeoutDuration()
      if (*(int *)(iVar2 + 0x54) == *(int *)(iVar3 + 8)) { // compare time values
        (**(code **)(&DAT_0103aee0 + (*(uint *)*puVar6 & 0x7fff) * 4))((uint *)*puVar6); // call timeout handler
        iVar2 = puVar6[3]; // puVar6[3] = retryCount
        if (0 < iVar2) {
          do {
            FUN_005a6ff0(); // retryConnection()
            iVar2 = iVar2 + -1;
          } while (iVar2 != 0);
        }
        puVar6[-1] = 0; // mark connection inactive
      }
    }
    iVar5 = iVar5 + 1;
    puVar6 = puVar6 + 0xb; // each connection slot is 0x2C bytes (11 * 4)
  } while (iVar5 < 0x40); // max 64 connections
  return;
}