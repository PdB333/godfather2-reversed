// FUNC_NAME: Entity::setAnimation
void __thiscall Entity::setAnimation(int this, undefined4 animName, uint slotIndex)
{
  int iVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  int *piVar4;
  undefined4 uVar5;
  
  if (((slotIndex < *(uint *)(this + 400)) &&
      (*(int *)(*(int *)(this + 0x18c) + slotIndex * 4) != 0)) &&
     (iVar1 = FUN_004baf60(animName), iVar1 != 0)) {
    puVar2 = (undefined4 *)FUN_004bb600(iVar1);
    puVar3 = (undefined1 *)*puVar2;
    if (puVar3 == (undefined1 *)0x0) {
      puVar3 = &DAT_0120546e;
    }
    piVar4 = (int *)FUN_00568320(puVar3);
    if (piVar4 != (int *)0x0) {
      iVar1 = **(int **)(*(int *)(this + 0x18c) + slotIndex * 4);
      uVar5 = (**(code **)(*piVar4 + 0xc))();
      (**(code **)(iVar1 + 0xc))(uVar5);
    }
  }
  return;
}