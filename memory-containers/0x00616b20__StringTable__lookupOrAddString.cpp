// FUNC_NAME: StringTable::lookupOrAddString
undefined4 StringTable::lookupOrAddString(void)
{
  char cVar1;
  char *pcVar2;
  undefined4 *in_EAX;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  ushort uVar6;
  
  FUN_0061c350(); // likely a mutex lock or critical section enter
  pcVar2 = (char *)*in_EAX; // this->string pointer (offset +0x00)
  pcVar3 = pcVar2;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  uVar4 = FUN_00ab8560(0,pcVar2,(int)pcVar3 - (int)(pcVar2 + 1)); // hash function (seed=0, string, length)
  for (iVar5 = *(int *)(DAT_01205968 + (uVar4 & 0x1ff) * 4); // hash table bucket array (512 entries)
      (iVar5 != 0 && (*(uint *)(iVar5 + 4) != uVar4)); iVar5 = *(int *)(iVar5 + 8)) {
  }
  if (iVar5 == 0) {
    iVar5 = FUN_00616590(uVar4); // allocate new string entry node
  }
  uVar6 = 0;
  if (*(short *)((int)in_EAX + 6) != 0) { // this->refCount (offset +0x06)
    do {
      FUN_00616a60(iVar5,in_EAX[3] + (uint)uVar6 * 0x18,1); // add reference (node, refData + index*0x18, 1)
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(ushort *)((int)in_EAX + 6));
  }
  return *(undefined4 *)(iVar5 + 4); // return the string pointer from the node
}