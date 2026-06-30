// FUNC_NAME: MemoryPoolManager::initialize
void MemoryPoolManager::initialize(void)
{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint *puVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  uint *puVar8;
  
  // Allocate pool header (8 bytes: pointer to block list + block size)
  piVar1 = (int *)FUN_009c8e50(8);
  if (piVar1 == (int *)0x0) {
    DAT_01205a4c = (int *)0x0; // gPoolHeader
  }
  else {
    piVar1[1] = 0x3ff8; // Block size: 16376 bytes (+0x4)
    puVar2 = (undefined4 *)FUN_009c8e50(0xc); // Allocate block list node (12 bytes)
    if (puVar2 == (undefined4 *)0x0) {
      *piVar1 = 0; // No block list
      uRam00000000 = 0;
      *(undefined4 *)(*piVar1 + 8) = 0;
      DAT_01205a4c = piVar1;
    }
    else {
      uVar3 = FUN_009c8e80(0x3ff8); // Allocate actual memory block
      puVar2[1] = uVar3; // +0x4: pointer to block memory
      *piVar1 = (int)puVar2; // Link block list node
      *puVar2 = 0; // +0x0: next node pointer
      *(undefined4 *)(*piVar1 + 8) = 0; // +0x8: free count
      DAT_01205a4c = piVar1;
    }
  }
  
  // Allocate global buffer for something (0x1354 bytes = 4948)
  DAT_01205a38 = (undefined4 *)(*(code *)PTR__malloc_00f0cd88)(0x1354);
  puVar2 = DAT_01205a38;
  for (iVar6 = 0x4d5; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_01205a3c = 0x4d5; // Element count
  DAT_01205a48 = 1; // Some flag
  
  // Allocate free list array (0x2000 bytes = 8192)
  puVar4 = (uint *)(*(code *)PTR__malloc_00f0cd88)(0x2000);
  uVar7 = 4;
  puVar8 = puVar4;
  DAT_01205a34 = puVar4; // gFreeList
  do {
    puVar8 = puVar8 + 1;
    *puVar8 = uVar7 | 1; // Mark as free with size
    piVar1 = DAT_01205a4c;
    uVar7 = uVar7 + 2;
  } while (uVar7 < 0x1002);
  puVar4[0x7ff] = 0; // Terminate list
  
  // Check if we need to allocate another block
  if ((*piVar1 == 0) || (piVar1[1] < *(int *)(*piVar1 + 8) + 0x14)) {
    piVar5 = (int *)FUN_009c8e50(0xc);
    if (piVar5 == (int *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      iVar6 = FUN_009c8e80(piVar1[1]);
      piVar5[1] = iVar6;
    }
    *piVar5 = *piVar1;
    piVar5[2] = 0;
    *piVar1 = (int)piVar5;
    puVar4 = DAT_01205a34;
  }
  
  // Allocate a new block (0x14 = 20 bytes)
  iVar6 = *piVar1;
  uVar7 = *(int *)(iVar6 + 4) + *(int *)(iVar6 + 8);
  *(int *)(iVar6 + 8) = *(int *)(iVar6 + 8) + 0x14;
  *puVar4 = uVar7;
  *(undefined1 *)(uVar7 + 0x10) = 0;
  *(undefined2 *)(*puVar4 + 0xc) = 0;
  *(undefined2 *)(*puVar4 + 0xe) = 1;
  *(undefined4 *)(*puVar4 + 4) = 0;
  *(undefined4 *)*puVar4 = 0;
  
  // Initialize global state
  DAT_01205a50 = 0; // Some counter
  DAT_01205a40 = 0x800; // Buffer size (2048)
  DAT_01205a44 = 3; // Some mode
  return;
}