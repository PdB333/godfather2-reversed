// FUNC_NAME: MemoryManager::reallocateOrCopyBuffer
undefined8 * __thiscall MemoryManager::reallocateOrCopyBuffer(int param_1, int param_2, int *param_3)
{
  int *piVar1;
  undefined4 *puVar2;
  char cVar3;
  int *in_EAX;
  undefined8 *puVar4;
  undefined8 *puVar5;
  int iVar6;
  undefined4 unaff_EBP;
  undefined4 *puVar7;
  undefined4 *unaff_retaddr;
  int local_4;
  
  // Determine new size: if source buffer exists, add 5 bytes to its size
  if (*param_3 == 0) {
    local_4 = 0;
  }
  else {
    local_4 = *param_3 + 5;
  }
  
  // Ensure new size is at least param_1 (minimum allocation)
  if (local_4 < param_1) {
    local_4 = param_1;
  }
  
  // Allocate new buffer via internal allocator
  puVar4 = (undefined8 *)FUN_005d1b60();
  
  // If no source data to copy, just update size and return
  if (param_2 == 0) {
    *param_3 = local_4;
    return puVar4;
  }
  
  // Copy data from source buffer to new buffer (16-byte chunks)
  iVar6 = 0;
  if (0 < *in_EAX) {
    puVar5 = puVar4;
    do {
      *puVar5 = *(undefined8 *)((param_2 - (int)puVar4) + (int)puVar5);
      puVar5[1] = *(undefined8 *)((param_2 - (int)puVar4) + 8 + (int)puVar5);
      iVar6 = iVar6 + 1;
      puVar5 = puVar5 + 2;
    } while (iVar6 < *in_EAX);
  }
  
  // Get reference count from source buffer header (at offset -4)
  piVar1 = (int *)(param_2 + -4);
  iVar6 = *piVar1 + -1;
  
  // Decrement reference count and free if reaching zero
  if (-1 < iVar6) {
    puVar7 = (undefined4 *)(*piVar1 * 0x10 + param_2 + 4);
    do {
      puVar2 = puVar7 + -4;
      puVar7 = puVar7 + -4;
      (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(*puVar2,0);
      iVar6 = iVar6 + -1;
      *puVar7 = 0;
    } while (-1 < iVar6);
  }
  
  // Check if reference count reached zero and free source buffer
  cVar3 = FUN_005c43d0(piVar1);
  if (cVar3 == '\0') {
    (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(piVar1,0);
    *unaff_retaddr = unaff_EBP;
    return puVar4;
  }
  
  // Update size and return new buffer
  *param_3 = local_4;
  return puVar4;
}