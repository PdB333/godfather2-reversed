// FUNC_NAME: NetConnection::findLocalObject
undefined4 __thiscall NetConnection::findLocalObject(int this, int *outGhostIndex, undefined4 *outObject)
{
  undefined4 uVar1;
  char cVar2;
  int in_EAX;
  int iVar3;
  
  if ((in_EAX != 0) && (this != 0)) {
    iVar3 = FUN_005f0330(*(undefined4 *)(in_EAX + 8),*(undefined4 *)(in_EAX + 0x14),0);
    *(int *)(iVar3 + 0xc) = this;
    if (*(int *)(iVar3 + 0x10) != 0) {
      cVar2 = FUN_005f0490();
      if (cVar2 != '\0') {
        uVar1 = **(undefined4 **)(iVar3 + 0x10);
        *outGhostIndex = iVar3;
        *outObject = uVar1;
        return 1;
      }
    }
    return 0;
  }
  return 0;
}