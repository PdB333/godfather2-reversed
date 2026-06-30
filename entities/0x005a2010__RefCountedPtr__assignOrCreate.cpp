// FUNC_NAME: RefCountedPtr::assignOrCreate
undefined4 * RefCountedPtr_assignOrCreate(undefined4 *param_1, int *param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *puVar4;
  
  piVar2 = param_2;
  puVar1 = DAT_0119a9c8; // Global head of linked list (likely free list or pool)
  FUN_005a1eb0(&param_2, param_2); // Call to resolve/adjust pointer (likely ref count increment)
  if (param_2 == (int *)0x0) {
    // Create new object if null
    piVar3 = (int *)(*DAT_0119caf0)(0x30, 0); // Allocate 0x30 bytes (size of some struct)
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      *piVar3 = 0; // Initialize reference count to 0
      FUN_005a0a00(piVar2); // Initialize object at piVar2? (or constructor)
      piVar3[8] = 1; // +0x20: some flag
      piVar3[10] = 0; // +0x28: some field
      piVar3[0xb] = 0; // +0x2c: some field
      *piVar3 = *piVar3 + 1; // Increment ref count (now 1)
    }
    puVar4 = (undefined4 *)(*DAT_0119caf0)(8, 0); // Allocate 8 bytes node for linked list
    if (puVar4 == (undefined4 *)0x0) {
      puVar4 = (undefined4 *)0x0;
    }
    else {
      *puVar4 = piVar3; // Store pointer to object
      puVar4[1] = 0; // Next pointer initially null
    }
    puVar4[1] = *puVar1; // Link new node into list (head->next)
    *puVar1 = puVar4; // Update head to new node
    *param_1 = piVar3; // Store in output parameter
    if (piVar3 == (int *)0x0) {
      return param_1;
    }
  }
  else {
    // Use existing object
    *param_1 = param_2;
    piVar3 = param_2;
  }
  // Increment ref count, then decrement check (if was 1, becomes 0 after decrement)
  *piVar3 = *piVar3 + 1;
  *piVar3 = *piVar3 + -1;
  if (*piVar3 == 0) {
    FUN_005a1b40(); // Cleanup function
    (*DAT_0119caf8)(piVar3, 0x30); // Free memory (0x30 bytes)
  }
  return param_1;
}