// FUNC_NAME: TNLConnection::processPacket
undefined4 * TNLConnection::processPacket(int thisPtr, undefined4 *outPacket, uint *inSeq, int param4, int param5)

{
  char cVar1;
  undefined4 *puVar2;
  bool bVar3;
  int local_c;
  int local_8;
  
  if (*(int *)(thisPtr + 0x20) == 0) {
    FUN_005e0510(thisPtr,outPacket,1,inSeq);
    return outPacket;
  }
  local_8 = **(int **)(thisPtr + 0x1c);
  if ((param4 == 0) || (param4 != thisPtr)) {
    FUN_00b97aea();
  }
  if (param5 == local_8) {
    if (*inSeq < *(uint *)(param5 + 0xc)) {
      FUN_005e0510(thisPtr,outPacket,1,inSeq);
      return outPacket;
    }
  }
  else {
    local_8 = *(int *)(thisPtr + 0x1c);
    if ((param4 == 0) || (param4 != thisPtr)) {
      FUN_00b97aea();
    }
    if (param5 == local_8) {
      if (*(uint *)(*(int *)(*(int *)(thisPtr + 0x1c) + 8) + 0xc) < *inSeq) {
        FUN_005e0510(thisPtr,outPacket,0,inSeq);
        return outPacket;
      }
    }
    else {
      bVar3 = *(uint *)(param5 + 0xc) < *inSeq;
      if (*inSeq < *(uint *)(param5 + 0xc)) {
        FUN_005e1540();
        if (*(uint *)(param5 + 0xc) < *inSeq) {
          if (*(char *)(*(int *)(param5 + 8) + 0x15) == '\0') {
            FUN_005e0510(thisPtr,outPacket,1,inSeq);
            return outPacket;
          }
          FUN_005e0510(thisPtr,outPacket,0,inSeq);
          return outPacket;
        }
        bVar3 = *(uint *)(param5 + 0xc) < *inSeq;
      }
      if (bVar3) {
        local_8 = *(int *)(thisPtr + 0x1c);
        local_c = thisPtr;
        FUN_005e15c0();
        cVar1 = FUN_005dff60();
        if ((cVar1 != '\0') || (*inSeq < *(uint *)(param5 + 0xc))) {
          if (*(char *)(*(int *)(param5 + 8) + 0x15) == '\0') {
            FUN_005e0510(thisPtr,outPacket,1,inSeq);
            return outPacket;
          }
          FUN_005e0510(thisPtr,outPacket,0,inSeq);
          return outPacket;
        }
      }
    }
  }
  puVar2 = (undefined4 *)FUN_005e0330(thisPtr,&local_c,inSeq);
  *outPacket = *puVar2;
  outPacket[1] = puVar2[1];
  return outPacket;
}