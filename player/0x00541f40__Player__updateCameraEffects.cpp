// FUNC_NAME: Player::updateCameraEffects
void __thiscall Player::updateCameraEffects(int this, int param_2)
{
  int iVar1;
  float fVar2;
  undefined1 auStack_b8 [8];
  undefined1 local_b0 [40];
  undefined1 auStack_88 [8];
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined1 local_60 [16];
  undefined1 local_50 [76];
  
  FUN_00470e30(param_2);
  if (*(int *)(this + 0x260) != 0) {
    FUN_004b59d0(param_2,local_50);
    FUN_00aa3930(local_50);
    FUN_00aa5450(local_60);
    local_80 = *(undefined4 *)(param_2 + 0x30);
    local_7c = *(undefined4 *)(param_2 + 0x34);
    local_78 = *(undefined4 *)(param_2 + 0x38);
    iVar1 = *(int *)(this + 0x260);
    local_74 = DAT_00e2b1a4;
    if (*(char *)(iVar1 + 0xd8) == '\\a') {
      if (((*(uint *)(iVar1 + 0x2c) & 0xc0000000) == 0xc0000000) &&
         (iVar1 = *(uint *)(iVar1 + 0x2c) * 4, iVar1 != 0)) {
        FUN_00aa1cf0(local_b0,iVar1);
        FUN_005420c0(local_50);
      }
      FUN_009f4cd0(local_b0);
      return;
    }
    if ((*(char *)(iVar1 + 0xd8) == '\\x06') && (DAT_00e44598 < DAT_012067e8)) {
      FUN_009f2000();
      (**(code **)(*(int *)(iVar1 + 0xd0) + 0x40))(&DAT_01139820);
      iVar1 = *(int *)(this + 0x260);
      FUN_009f2000();
      (**(code **)(*(int *)(iVar1 + 0xd0) + 0x44))(&DAT_01139820);
      fVar2 = 1.0 / DAT_012067e8;
      FUN_00aa3930(auStack_b8);
      FUN_009de610(auStack_88,&local_78,fVar2,*(undefined4 *)(this + 0x260));
    }
  }
  return;
}