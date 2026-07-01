// FUNC_NAME: Entity::updateTransformFromAnimation
void __thiscall Entity::updateTransformFromAnimation(int this, undefined4 param_2)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_160 [112];
  undefined1 local_f0 [112];
  undefined1 local_80 [124];
  
  if (*(int *)(this + 0x24) == 0) {
    iVar4 = FUN_0082eb80(local_80,param_2);
  }
  else if (*(int *)(this + 0x24) == 1) {
    iVar4 = FUN_0082e8e0(local_160,param_2,0);
  }
  else {
    iVar4 = FUN_0082e8e0(local_f0,param_2,0);
  }
  if (this + 0x30 != iVar4) {
    FUN_00820830(iVar4);
    // Copy transform data from animation result to entity
    // +0x7c: position x
    // +0x80: position y
    // +0x84: position z
    *(undefined4 *)(this + 0x7c) = *(undefined4 *)(iVar4 + 0x4c);
    *(undefined4 *)(this + 0x80) = *(undefined4 *)(iVar4 + 0x50);
    *(undefined4 *)(this + 0x84) = *(undefined4 *)(iVar4 + 0x54);
    uVar1 = *(undefined4 *)(iVar4 + 100);
    uVar2 = *(undefined4 *)(iVar4 + 0x68);
    uVar3 = *(undefined4 *)(iVar4 + 0x6c);
    // +0x90: rotation quaternion x
    // +0x94: rotation quaternion y
    // +0x98: rotation quaternion z
    // +0x9c: rotation quaternion w
    *(undefined4 *)(this + 0x90) = *(undefined4 *)(iVar4 + 0x60);
    *(undefined4 *)(this + 0x94) = uVar1;
    *(undefined4 *)(this + 0x98) = uVar2;
    *(undefined4 *)(this + 0x9c) = uVar3;
  }
  return;
}