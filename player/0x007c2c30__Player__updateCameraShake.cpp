// FUNC_NAME: Player::updateCameraShake
void __thiscall Player::updateCameraShake(int *this, undefined4 *param_2)
{
  int iVar1;
  int iVar2;
  undefined1 local_44 [12];
  undefined8 local_38;
  float local_30;
  undefined1 local_2c[4];
  undefined4 local_28;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  
  iVar1 = (**(code **)*param_2)();
  if (((iVar1 == 0x27a0f69c) && (this[0x22] != 0)) && (this[0x22] != 0x48)) {
    iVar1 = FUN_00471610();
    iVar2 = FUN_00471610();
    local_38 = *(undefined8 *)(iVar2 + 0x20);
    local_30 = *(float *)(iVar2 + 0x28);
    FUN_008d8ce0(local_2c);
    local_28 = *(undefined4 *)(iVar1 + 0x34);
    local_20 = (float)local_38;
    local_1c = local_38._4_4_;
    local_18 = local_30;
    local_14 = 0;
    FUN_0056afa0(&local_20,&local_20);
    local_30 = DAT_00e44564 - local_18;
    local_38 = CONCAT44(DAT_00e44564 - local_1c,DAT_00e44564 - local_20);
    (**(code **)(*this + 0x2c))(0x2242e90e,1,1,0,0x3f800000,0x3f800000);
    FUN_00754d30(local_44,&stack0xffffffb0,1,_DAT_00d64c8c,0,1);
  }
  return;
}