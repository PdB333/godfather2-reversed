// FUNC_NAME: TNLConnection::processPacketWindow
void __thiscall TNLConnection::processPacketWindow(int thisPtr, int *outPacket, int param3, int param4, int param5, int param6)
{
  int iVar1;
  undefined1 local_8 [8];
  
  iVar1 = **(int **)(thisPtr + 4);
  if ((param3 == 0) || (param3 != thisPtr)) {
    FUN_00b97aea(); // likely assertion failure
  }
  if (param4 == iVar1) {
    iVar1 = *(int *)(thisPtr + 4);
    if ((param5 == 0) || (param5 != thisPtr)) {
      FUN_00b97aea(); // assertion failure
    }
    if (param6 == iVar1) {
      FUN_006956b0(*(undefined4 *)(*(int *)(thisPtr + 4) + 4)); // freePacket
      *(int *)(*(int *)(thisPtr + 4) + 4) = *(int *)(thisPtr + 4); // reset next pointer
      *(undefined4 *)(thisPtr + 8) = 0; // clear some field
      *(undefined4 *)*(undefined4 *)(thisPtr + 4) = *(undefined4 *)(thisPtr + 4); // self-loop prev
      *(int *)(*(int *)(thisPtr + 4) + 8) = *(int *)(thisPtr + 4); // self-loop next
      iVar1 = **(int **)(thisPtr + 4);
      *outPacket = thisPtr;
      outPacket[1] = iVar1;
      return;
    }
  }
  while( true ) {
    if ((param3 == 0) || (param3 != param5)) {
      FUN_00b97aea(); // assertion failure
    }
    if (param4 == param6) break;
    FUN_006940f0(); // advancePacketWindow
    FUN_00695750(local_8,param3,param4); // copyPacket
  }
  *outPacket = param3;
  outPacket[1] = param4;
  return;
}