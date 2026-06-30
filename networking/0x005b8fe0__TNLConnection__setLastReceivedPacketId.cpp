// FUNC_NAME: TNLConnection::setLastReceivedPacketId
void __thiscall TNLConnection::setLastReceivedPacketId(undefined4 param_1, int param_2)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  undefined2 *puStack_1c;
  undefined4 uStack_18;
  
  iVar4 = FUN_005a19c0(); // getConnectionState() - returns pointer to connection state struct
  if (((-1 < param_2) && (piVar5 = (int *)(*(int *)(iVar4 + 8) + 8), param_2 < *piVar5)) &&
     (param_2 != *(int *)(iVar4 + 0x10))) {
    if (param_2 == *(int *)(iVar4 + 0x10) + 1) {
      // Normal sequential packet - just advance lastReceivedPacketId
      *(int *)(iVar4 + 0x10) = param_2;
      FUN_005ba140(piVar5,iVar4 + 0x1c,param_1,param_2); // processPacket()
    }
    else {
      // Out-of-order packet - need to handle gap
      uVar2 = *(undefined4 *)(iVar4 + 0x1c); // save current packet buffer
      puVar1 = (undefined4 *)(iVar4 + 0x1c);
      iVar6 = (*DAT_0119caf0)(4,0); // allocate 4 bytes
      if (iVar6 == 0) {
        uStack_18 = 0;
      }
      else {
        uStack_18 = FUN_005b1df0(); // createPacketBuffer()
      }
      puStack_1c = (undefined2 *)(*DAT_0119caf0)(0x48,0); // allocate 0x48 bytes for gap buffer
      if (puStack_1c == (undefined2 *)0x0) {
        puStack_1c = (undefined2 *)0x0;
      }
      else {
        *puStack_1c = 4; // gap buffer type
        puStack_1c[1] = 0; // gap count
        *(undefined2 **)(puStack_1c + 2) = puStack_1c + 4; // pointer to gap data
        _memset(puStack_1c + 4,0,0x40); // clear gap data
      }
      uVar3 = *(undefined4 *)(iVar4 + 0xc); // save current gap buffer
      *puVar1 = uStack_18; // set new packet buffer
      *(undefined2 **)(iVar4 + 0xc) = puStack_1c; // set new gap buffer
      FUN_005b3890(); // resetPacketProcessing()
      *(undefined4 *)(iVar4 + 0x10) = 0; // reset lastReceivedPacketId
      if (-1 < param_2) {
        do {
          piVar5 = (int *)(*(int *)(iVar4 + 8) + 8);
          if (*piVar5 <= *(int *)(iVar4 + 0x10)) break;
          FUN_005ba140(piVar5,puVar1,param_1,*(int *)(iVar4 + 0x10)); // processPacket()
          *(int *)(iVar4 + 0x10) = *(int *)(iVar4 + 0x10) + 1;
        } while (*(int *)(iVar4 + 0x10) <= param_2);
      }
      *(undefined4 *)(iVar4 + 0xc) = uVar3; // restore old gap buffer
      *(int *)(iVar4 + 0x10) = param_2; // set lastReceivedPacketId
      *puVar1 = uVar2; // restore old packet buffer
      FUN_005b3950(uStack_18,puStack_1c,uVar3); // freeGapBuffer()
    }
    FUN_005ba460(*(int *)(iVar4 + 8) + 8,param_1); // updateAckState()
  }
  return;
}