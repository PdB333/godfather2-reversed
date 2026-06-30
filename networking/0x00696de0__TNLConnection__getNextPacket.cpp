// FUNC_NAME: TNLConnection::getNextPacket
int __thiscall TNLConnection::getNextPacket(int this, undefined4 param_2)
{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined1 local_20 [8];
  int local_18 [3];
  code *local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar1 = FUN_006948e0(param_2); // likely getSequenceForPacket or similar
  if (this == 0) {
    FUN_00b97aea(); // assert or crash
  }
  if (iVar1 != *(int *)(this + 4)) { // +0x04 = mCurrentSequence
    iVar2 = FUN_004d4b20(iVar1 + 0xc); // check if packet is in window
    if (-1 < iVar2) goto LAB_00696e5d;
  }
  FUN_004d3b50(param_2); // mark packet as sent/acknowledged
  local_8 = 0;
  local_4 = 0;
  piVar3 = (int *)FUN_00696890(local_20, this, iVar1, local_18); // get packet data
  this = *piVar3;
  iVar1 = piVar3[1];
  if (local_18[0] != 0) {
    (*local_c)(local_18[0]); // cleanup callback
  }
LAB_00696e5d:
  if (this == 0) {
    FUN_00b97aea(); // assert or crash
  }
  if (iVar1 == *(int *)(this + 4)) { // +0x04 = mSequence
    FUN_00b97aea(); // assert or crash
  }
  return iVar1 + 0x1c; // return pointer to packet data (offset +0x1c from packet header)
}