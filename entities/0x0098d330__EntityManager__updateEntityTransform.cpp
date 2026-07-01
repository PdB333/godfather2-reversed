// FUNC_NAME: EntityManager::updateEntityTransform
void __thiscall EntityManager::updateEntityTransform(int thisPtr, int entityId, undefined4 *transform)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  bool bVar5;
  int iVar6;
  undefined1 *puVar7;
  int *piVar8;
  
  iVar6 = FUN_005bec00(); // likely getCurrentTime() or getFrameNumber()
  piVar8 = *(int **)(thisPtr + 0x230); // +0x230: entity list begin iterator
  if (piVar8 != *(int **)(thisPtr + 0x234)) { // +0x234: entity list end iterator
    while (*(int *)(*piVar8 + 0x34) != entityId) { // +0x34: entity ID field
      piVar8 = piVar8 + 1;
      if (piVar8 == *(int **)(thisPtr + 0x234)) {
        return;
      }
    }
    iVar1 = *piVar8; // pointer to entity
    bVar5 = false;
    // Check if entity is active (time matches) and no pending update, and transform change is significant
    if (((*(int *)(iVar1 + 0x40) == iVar6) && (*(int *)(thisPtr + 0x120) == 0)) &&
       (*(float *)(iVar1 + 0x20) * *(float *)(iVar1 + 0x20) + // position.x^2
        *(float *)(iVar1 + 0x24) * *(float *)(iVar1 + 0x24) + // position.y^2
        *(float *)(iVar1 + 0x28) * *(float *)(iVar1 + 0x28) + // position.z^2
        *(float *)(iVar1 + 0x2c) * *(float *)(iVar1 + 0x2c) < DAT_00e44598)) { // threshold
      bVar5 = true;
    }
    uVar2 = transform[1];
    uVar3 = transform[2];
    uVar4 = transform[3];
    *(undefined4 *)(iVar1 + 0x20) = *transform; // update position.x
    *(undefined4 *)(iVar1 + 0x24) = uVar2; // update position.y
    *(undefined4 *)(iVar1 + 0x28) = uVar3; // update position.z
    *(undefined4 *)(iVar1 + 0x2c) = uVar4; // update rotation/scale
    if (*(int *)(thisPtr + 0x270) == entityId) { // +0x270: current tracked entity ID
      puVar7 = *(undefined1 **)(thisPtr + 0x260); // +0x260: callback function pointer
      if (puVar7 == (undefined1 *)0x0) {
        puVar7 = &DAT_0120546e; // default callback
      }
      FUN_0098cf00(puVar7); // invoke callback
      *(undefined4 *)(thisPtr + 0x270) = 0; // clear tracked entity
      if (*(int *)(thisPtr + 0x260) != 0) {
        (**(code **)(thisPtr + 0x26c))(*(int *)(thisPtr + 0x260)); // call destructor?
      }
      *(undefined4 *)(thisPtr + 0x260) = 0; // clear callback
      *(undefined4 *)(thisPtr + 0x268) = 0;
      *(undefined4 *)(thisPtr + 0x264) = 0;
      return;
    }
    if (bVar5) {
      FUN_0098d250(); // trigger update notification
    }
  }
  return;
}