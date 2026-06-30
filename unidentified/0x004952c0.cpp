// FUN_004952c0: ResourceManager::shutdownOrCleanup

void __fastcall ResourceManager::shutdownOrCleanup(int thisPtr)
{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;

  // Set destroyed/cleaned flag at +0x20c
  *(byte *)(thisPtr + 0x20c) = 1;

  // Free or process the first resource list (count at +0x204)
  FUN_00ab51e0(*(undefined4 *)(thisPtr + 0x204));
  iVar3 = 0;
  if (0 < *(int *)(thisPtr + 0x204)) {
    do {
      FUN_00ab54e0(&DAT_00e2e238,0);
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(thisPtr + 0x204));
  }

  // Second list: pointer at +0x208, with count stored at offset -4 (like a standard container)
  iVar3 = *(int *)(thisPtr + 0x208);
  if (iVar3 != 0) {
    iVar1 = *(int *)(iVar3 + -4);
    while (iVar1 = iVar1 + -1, -1 < iVar1) {
      FUN_00ab72a0(); // destruct each element
    }
    FUN_009c8eb0(iVar3 + -4); // delete the container itself
  }

  // Third list: count at +0x210, array of pointers starting at +0x224
  uVar2 = 0;
  if (*(int *)(thisPtr + 0x210) != 0) {
    puVar4 = (undefined4 *)(thisPtr + 0x224);
    do {
      // Call vtable function at offset 0xc on each pointed-to object
      (**(code **)(**(int **)(*(int *)*puVar4) + 0xc))(*puVar4,0);
      *puVar4 = 0;
      uVar2 = uVar2 + 1;
      puVar4 = puVar4 + 1;
    } while (uVar2 < *(uint *)(thisPtr + 0x210));
    *(undefined4 *)(thisPtr + 0x200) = 0;
    return;
  }
  *(undefined4 *)(thisPtr + 0x200) = 0;
  return;
}