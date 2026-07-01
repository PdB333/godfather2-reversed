// FUNC_NAME: AsyncReadTask::processRead
void __fastcall AsyncReadTask::processRead(int this) {
  byte bVar1;
  int iVar2;
  int local_54;
  undefined1 local_50[76];
  
  bVar1 = *(byte *)(this + 0x31);
  if ((bVar1 & 1) != 0) {
    if ((bVar1 & 2) != 0) {
      if ((bVar1 & 4) != 0) {
        return;
      }
      *(byte *)(this + 0x31) = bVar1 | 4;
    }
    if ((((*(int *)(this + 0x10) != 0) || (*(int *)(this + 0x14) != 0)) ||
        (*(int *)(this + 0x18) != 0)) || (*(int *)(this + 0x1c) != 0)) {
      FUN_008cf3d0(local_50);
      if (*(int *)(this + 0x20) == 0) {
        if (*(char *)(this + 0x30) == '\x01') {
          iVar2 = (**(code **)(**(int **)(*(int *)(this + 8) + 8) + 0x24))(0,0);
          iVar2 = FUN_00475550(&local_54,this + 0x10,iVar2);
        }
        else {
          iVar2 = FUN_008cf410();
          iVar2 = FUN_00414ef0(&local_54,this + 0x10,local_50,iVar2);
        }
        FUN_00414db0(iVar2);
        if (local_54 != 0) {
          *(undefined4 *)(local_54 + 8) = 0;
        }
        if (*(int *)(this + 0x20) == 0) {
          return;
        }
      }
      if (*(int *)(this + 0x24) != 0) {
        FUN_004df7f0((int *)(this + 0x24));
      }
    }
  }
  return;
}