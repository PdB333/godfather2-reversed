// FUNC_NAME: SomeClass::clearAndRelease
void SomeClass::clearAndRelease(void)
{
  int *piVar1;
  int iVar2;
  int this; // unaff_EDI
  int local_8;
  undefined4 local_4;
  
  piVar1 = *(int **)(this + 0x28); // +0x28: pointer to some array/container
  iVar2 = *piVar1;
  if (iVar2 != 0) {
    if (*(int *)(iVar2 + 8) != 0) { // +0x08: first element pointer
      FUN_00573f70(*(int *)(iVar2 + 8)); // release first element
    }
    if (*(int *)(iVar2 + 0xc) != 0) { // +0x0C: second element pointer
      FUN_00573f70(*(int *)(iVar2 + 0xc)); // release second element
    }
    (**(code **)(*(int *)piVar1[3] + 4))(iVar2,0); // call virtual destructor or release
    piVar1[1] = piVar1[1] + -1; // decrement reference count
  }
  *piVar1 = 0; // clear pointer
  local_8 = 0;
  if (0 < *(int *)(this + 0x20)) { // +0x20: count of items
    do {
      local_4 = *(undefined4 *)(*(int *)(this + 0x24) + local_8 * 8); // +0x24: array of items (8 bytes each)
      FUN_00573df0(*(undefined4 *)(this + 0x28),&local_4,&local_8); // process each item
      local_8 = local_8 + 1;
    } while (local_8 < *(int *)(this + 0x20));
  }
  return;
}