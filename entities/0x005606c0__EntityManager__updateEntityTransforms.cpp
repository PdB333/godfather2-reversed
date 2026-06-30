// FUNC_NAME: EntityManager::updateEntityTransforms
void EntityManager::updateEntityTransforms(int param_1)
{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int unaff_ESI;
  int iVar6;
  int iVar7;
  
  // Lock transform data mutex (offset +0x18 -> +0xe0)
  FUN_00bf0850(*(int *)(unaff_ESI + 0x18) + 0xe0);
  
  // Call virtual function at vtable+0xc on object at param_1+8 (likely a transform update callback)
  (**(code **)(**(int **)(unaff_ESI + 0x3c) + 0xc))(*(undefined4 *)(param_1 + 8));
  
  iVar5 = 0;
  iVar7 = 0;
  if (0 < *(int *)(unaff_ESI + 0x4c)) { // entity count at +0x4c
    puVar4 = (undefined4 *)(unaff_ESI + 0x150); // pointer to array of transform data pairs
    iVar6 = 0;
    do {
      // Copy transform data from source array (+0x118) to destination array (+0x48)
      // Each source entry is 0x40 bytes, each destination entry is 0xc0 bytes
      *(undefined4 *)(iVar6 + 0x50 + *(int *)(unaff_ESI + 0x48)) =
           *(undefined4 *)(iVar5 + 0x2c + *(int *)(unaff_ESI + 0x118));
      iVar1 = *(int *)(unaff_ESI + 0x118);
      iVar3 = *(int *)(unaff_ESI + 0x48);
      *(undefined4 *)(iVar3 + iVar6) = *(undefined4 *)(iVar1 + iVar5);
      iVar1 = iVar1 + iVar5;
      iVar3 = iVar3 + iVar6;
      *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(iVar1 + 4);
      *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(iVar1 + 8);
      *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(iVar1 + 0xc);
      *(undefined4 *)(iVar3 + 0x10) = *(undefined4 *)(iVar1 + 0x10);
      *(undefined4 *)(iVar3 + 0x14) = *(undefined4 *)(iVar1 + 0x14);
      *(undefined4 *)(iVar3 + 0x18) = *(undefined4 *)(iVar1 + 0x18);
      *(undefined4 *)(iVar3 + 0x1c) = *(undefined4 *)(iVar1 + 0x1c);
      *(undefined4 *)(iVar6 + 0x20 + *(int *)(unaff_ESI + 0x48)) =
           *(undefined4 *)(iVar5 + 0x20 + *(int *)(unaff_ESI + 0x118));
      *(undefined4 *)(iVar6 + 0x24 + *(int *)(unaff_ESI + 0x48)) =
           *(undefined4 *)(iVar5 + 0x24 + *(int *)(unaff_ESI + 0x118));
      *(undefined4 *)(iVar6 + 0x28 + *(int *)(unaff_ESI + 0x48)) =
           *(undefined4 *)(iVar5 + 0x28 + *(int *)(unaff_ESI + 0x118));
      *puVar4 = 0;
      puVar4[1] = 0;
      if (*(int *)(iVar6 + 0x24 + *(int *)(unaff_ESI + 0x48)) != 0) {
        iVar1 = iVar6 + *(int *)(unaff_ESI + 0x48);
        puVar2 = (undefined4 *)
                 FUN_005566a0(*(int *)(iVar1 + 0x24) + 0x10,*(undefined4 *)(iVar1 + 0x28));
        if (puVar2 != (undefined4 *)0x0) {
          *puVar4 = puVar2[1];
          puVar4[1] = *puVar2;
        }
      }
      iVar7 = iVar7 + 1;
      puVar4 = puVar4 + 2;
      iVar5 = iVar5 + 0x40;
      iVar6 = iVar6 + 0xc0;
    } while (iVar7 < *(int *)(unaff_ESI + 0x4c));
  }
  return;
}