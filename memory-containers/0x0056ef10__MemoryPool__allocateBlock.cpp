// FUNC_NAME: MemoryPool::allocateBlock
undefined8 * MemoryPool::allocateBlock(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined4 *puVar5;
  undefined2 uVar6;
  uint uVar7;
  undefined4 *puVar8;
  
  iVar1 = DAT_01205560; // MemoryPool instance pointer
  uVar7 = param_1 * 0x20 + 0x10; // Calculate block size: param_1 * 32 + 16
  puVar3 = *(undefined8 **)(DAT_01205560 + 8); // freeList head
  puVar4 = puVar3 + param_1 * 4 + 2; // Calculate end of block
  uVar6 = (undefined2)uVar7; // Store block size as ushort
  if (puVar4 <= (undefined8 *)
                (*(int *)(DAT_01205560 + 0x10) + (int)*(undefined8 **)(DAT_01205560 + 0xc))) {
    // Fast path: allocate from free list
    if (puVar3 == (undefined8 *)0x0) {
      puVar3 = (undefined8 *)0x0;
    }
    else {
      *puVar3 = 0;
      puVar3[1] = 0;
    }
    *(undefined4 *)puVar3 = *(undefined4 *)(iVar1 + 4); // prev pointer
    *(undefined4 *)((int)puVar3 + 4) = 0; // next pointer
    *(undefined1 *)(puVar3 + 1) = 0; // flags
    *(undefined1 *)((int)puVar3 + 9) = 1; // inUse flag
    *(undefined2 *)((int)puVar3 + 10) = uVar6; // block size
    *(int *)((int)puVar3 + 0xc) = param_1; // index
    if (*(int *)(iVar1 + 4) != 0) {
      *(undefined8 **)(*(int *)(iVar1 + 4) + 4) = puVar3;
    }
    *(undefined8 **)(iVar1 + 8) = puVar4;
    *(undefined8 **)(iVar1 + 4) = puVar3;
    return puVar3;
  }
  // Slow path: search for free space in memory pool
  puVar2 = (undefined4 *)**(undefined4 **)(DAT_01205560 + 4); // first block
  puVar8 = *(undefined4 **)(DAT_01205560 + 4); // current block
  while( true ) {
    puVar5 = puVar2;
    puVar4 = *(undefined8 **)(DAT_01205560 + 0xc); // pool start
    if (puVar5 != (undefined4 *)0x0) {
      puVar4 = (undefined8 *)((uint)*(ushort *)((int)puVar5 + 10) + (int)puVar5); // end of current block
    }
    if (uVar7 <= (uint)((int)puVar8 - (int)puVar4)) break; // found enough space
    if (puVar5 == (undefined4 *)0x0) {
      return (undefined8 *)0x0; // no space available
    }
    puVar2 = (undefined4 *)*puVar5; // next block
    puVar8 = puVar5;
  }
  // Insert new block between puVar5 and puVar8
  if (puVar4 == (undefined8 *)0x0) {
    puVar3 = (undefined8 *)0x0;
  }
  else {
    *puVar4 = 0;
    puVar4[1] = 0;
    puVar3 = puVar4;
  }
  *(undefined2 *)((int)puVar3 + 10) = uVar6; // block size
  *(undefined4 **)puVar3 = puVar5; // next pointer
  *(undefined4 **)((int)puVar3 + 4) = puVar8; // prev pointer
  *(undefined1 *)(puVar3 + 1) = 0; // flags
  *(undefined1 *)((int)puVar3 + 9) = 1; // inUse flag
  *(int *)((int)puVar3 + 0xc) = param_1; // index
  if (puVar5 != (undefined4 *)0x0) {
    puVar5[1] = puVar4; // update next block's prev
  }
  *puVar8 = puVar4; // update prev block's next
  return puVar3;
}