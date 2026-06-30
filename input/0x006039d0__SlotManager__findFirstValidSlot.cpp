// FUNC_NAME: SlotManager::findFirstValidSlot
uint __thiscall SlotManager::findFirstValidSlot(int thisPtr, undefined4 param_2, undefined4* outValue, undefined1* outTypeByte)
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint in_EAX;
  uint uVar4;
  int iVar5;
  int* local_4;

  uVar4 = in_EAX & 0xffffff00;
  iVar5 = *(int*)(thisPtr + 0x34) + -1; // entryCount - 1
  if (-1 < iVar5) {
    local_4 = (int*)(*(int*)(thisPtr + 0x30) + iVar5 * 4); // points to last entry in list
    do {
      iVar1 = *local_4;                    // entry pointer
      iVar2 = *(int*)(iVar1 + 4);           // +0x4: subTablePtr
      param_2 = 0;
      uVar4 = FUN_00605d00(&param_2);       // validate and get subIndex
      if ((char)uVar4 != '\0') {
        uVar3 = *(undefined4*)(*(int*)(iVar2 + 0x1c) + param_2 * 4); // subTable[subIndex]
        *outValue = uVar3;
        *outTypeByte = *(undefined1*)(iVar1 + 8); // entry +0x8: typeByte
        return CONCAT31((int3)((uint)uVar3 >> 8), 1); // pack success flag (low byte=1) and data
      }
      local_4 = local_4 + -1; // move backward through list
      iVar5 = iVar5 + -1;
    } while (-1 < iVar5);
  }
  return uVar4; // failure: return original mask value
}