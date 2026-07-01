// FUNC_NAME: AnimationBlendTree::blendAnimations
void __thiscall AnimationBlendTree::blendAnimations(int this, int *blendNodes)
{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  float fVar7;
  int iVar8;
  
  if ((*(int *)(this + 0xc0) != -1) && (*(int *)(this + 0xc4) != -1)) {
    bVar6 = true;
    if (blendNodes == (int *)0x0) {
LAB_00824d74:
      bVar6 = false;
    }
    else {
      iVar8 = 0;
      do {
        iVar2 = *blendNodes;
        if ((iVar2 == 0) || (*(int *)(iVar2 + 0xc) != *(int *)(this + 0xc))) goto LAB_00824d74;
        if ((*(int *)(iVar2 + 0xc0) != -1) && (*(int *)(iVar2 + 0xc4) != -1)) {
          iVar3 = *(int *)(*(int *)(*(int *)(iVar2 + 0xa8) + *(int *)(iVar2 + 0xc4) * 4) + 0x5c);
          *(undefined4 *)
           (*(int *)(*(int *)(*(int *)(iVar2 + 0xa8) + *(int *)(iVar2 + 0xc0) * 4) + 0x5c) + 0x20) =
               0;
          *(undefined4 *)(iVar3 + 0x20) = 0;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 == 0);
    }
    iVar8 = *(int *)(*(int *)(*(int *)(this + 0xa8) + *(int *)(this + 0xc0) * 4) + 0x5c);
    iVar2 = *(int *)(*(int *)(*(int *)(this + 0xa8) + *(int *)(this + 0xc4) * 4) + 0x5c);
    *(undefined4 *)(iVar8 + 0x20) = 0;
    *(undefined4 *)(iVar2 + 0x20) = 0;
    fVar7 = _DAT_00d5780c;
    if (!bVar6) {
      *(float *)(iVar8 + 0x20) = *(float *)(this + 200) + *(float *)(iVar8 + 0x20);
      *(float *)(iVar2 + 0x20) =
           (_DAT_00d5780c - *(float *)(this + 200)) + *(float *)(iVar2 + 0x20);
      FUN_00824260();
      FUN_00824260();
      FUN_00824190();
      return;
    }
    iVar3 = *blendNodes;
    iVar4 = *(int *)(*(int *)(iVar3 + 0xa8) + *(int *)(iVar3 + 0xc4) * 4);
    fVar1 = (float)blendNodes[1];
    iVar5 = *(int *)(*(int *)(*(int *)(iVar3 + 0xa8) + *(int *)(iVar3 + 0xc0) * 4) + 0x5c);
    *(float *)(iVar5 + 0x20) = *(float *)(iVar3 + 200) * fVar1 + *(float *)(iVar5 + 0x20);
    iVar4 = *(int *)(iVar4 + 0x5c);
    *(float *)(iVar4 + 0x20) = (fVar7 - *(float *)(iVar3 + 200)) * fVar1 + *(float *)(iVar4 + 0x20);
    *(float *)(iVar8 + 0x20) =
         (fVar7 - fVar1) * *(float *)(this + 200) + *(float *)(iVar8 + 0x20);
    *(float *)(iVar2 + 0x20) =
         (fVar7 - *(float *)(this + 200)) * (fVar7 - fVar1) + *(float *)(iVar2 + 0x20);
    FUN_00824260();
    FUN_00824260();
    FUN_00824260();
    FUN_00824260();
    FUN_00824190();
  }
  return;
}