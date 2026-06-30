// FUNC_NAME: Animation::updateAnimationState
int __thiscall Animation::updateAnimationState(int this, int animData, undefined4 param_3)
{
  byte bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  int local_18;
  
  if (*(int *)(this + 0x60) == 0) {
    return 0;
  }
  *(undefined1 *)(this + 0x30) = 0;
  *(int *)(animData + 0x7c) = this;
  bVar1 = **(byte **)(this + 0x60);
  uVar5 = *(undefined4 *)(this + 0x20);
  if ((bVar1 & 0x3f) < 0x23) {
    local_18 = (**(code **)(&DAT_0103afc0 + (bVar1 & 0x3f) * 4))
                         (animData,*(byte **)(this + 0x60),*(undefined4 *)(this + 100),
                          *(undefined4 *)(this + 0x1c),uVar5,param_3,0x3f800000);
    if (local_18 != 0) {
      FUN_0056cba0(local_18 + 0x10,this + 0x40,local_18 + 0x10);
      fVar2 = *(float *)(this + 0x54);
      fVar3 = *(float *)(this + 0x58);
      fVar4 = *(float *)(this + 0x5c);
      *(float *)(local_18 + 0x20) = *(float *)(this + 0x50) + *(float *)(local_18 + 0x20);
      *(float *)(local_18 + 0x24) = fVar2 + *(float *)(local_18 + 0x24);
      *(float *)(local_18 + 0x28) = fVar3 + *(float *)(local_18 + 0x28);
      *(float *)(local_18 + 0x2c) = fVar4 + *(float *)(local_18 + 0x2c);
      uVar5 = DAT_00e2b1a4;
      *(undefined4 *)(local_18 + 0x2c) = DAT_00e2b1a4;
    }
  }
  else {
    local_18 = 0;
  }
  *(int *)(animData + 0x7c) = this;
  FUN_00591160();
  *(undefined4 *)(this + 0x24) = uVar5;
  if (*(int *)(this + 0x68) != 0) {
    FUN_00591ab0(animData,*(undefined4 *)(this + 0x60),*(undefined4 *)(this + 100));
    *(undefined4 *)(this + 0x68) = 0;
  }
  *(uint *)(this + 0x10) = *(uint *)(this + 0x10) & 0xffffffdf;
  return local_18;
}