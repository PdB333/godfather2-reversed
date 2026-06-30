// FUNC_NAME: Entity::getSomeIndexOrId
int __thiscall Entity::getSomeIndexOrId(int this, undefined4 param_2)
{
  int iVar1;
  int iVar2;
  
  if ((this != 0) && (*(int *)(this + 0x70) != 0)) {
    // +0x70: pointer to some data structure
    // +0x1c: offset within that structure to an array
    // +0x74: short index into that array (each element 0x18 bytes)
    // +0x14: offset within each element to a pointer
    iVar2 = *(int *)(*(int *)(*(int *)(this + 0x70) + 0x1c) + *(short *)(this + 0x74) * 0x18 + 0x14);
    iVar1 = FUN_005828a0(param_2, iVar2); // likely a lookup function (e.g., findIndexInArray)
    if ((iVar1 == -1) || (iVar2 = *(int *)(iVar2 + 0x10 + iVar1 * 0x14), iVar2 == -1)) {
      iVar2 = -1;
    }
    return iVar2;
  }
  return -1;
}