// FUNC_NAME: EARS::Framework::SomeManager::processUpdate
void __thiscall processUpdate(int this, int param_2)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  int local_64 [3];
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  // Check if the internal data pointer at +0x1c is null
  if (*(int *)(param_2 + 0x1c) == 0) {
    // Allocate memory for a new object (size 0x14, alignment 0x10)
    puVar4 = (undefined4 *)FUN_004eb390(0x14,0x10);
    if (puVar4 == (undefined4 *)0x0) {
      puVar4 = (undefined4 *)0x0;
    }
    else {
      // Initialize the allocated object
      puVar4[1] = 0;  // +0x04: reference count?
      *puVar4 = &PTR_LAB_00d73428;  // +0x00: vtable pointer
      puVar4[4] = 0;  // +0x10: some field
    }
    // Store the allocated object pointer at +0x1c
    *(undefined4 **)(param_2 + 0x1c) = puVar4;
    // Increment reference count at +0x04 of the allocated object
    piVar1 = (int *)(*(int *)(param_2 + 0x1c) + 4);
    *piVar1 = *piVar1 + 1;
  }
  
  // Copy data from param_1 + 0x4c to param_2 + 0x08 (8 bytes)
  *(undefined8 *)(param_2 + 8) = *(undefined8 *)(param_1 + 0x4c);
  // Copy data from param_1 + 0x54 to param_2 + 0x10 (8 bytes)
  *(undefined8 *)(param_2 + 0x10) = *(undefined8 *)(param_1 + 0x54);
  
  // Set fields in the allocated object
  *(undefined4 *)(*(int *)(param_2 + 0x1c) + 0xc) = _DAT_00d5780c;  // +0x0c: some global value
  *(undefined4 *)(*(int *)(param_2 + 0x1c) + 8) = 0;  // +0x08: reset to 0
  
  // Get some function result
  local_64[2] = FUN_004262f0(0);
  
  iVar3 = param_2;
  
  // Initialize local array with global values
  local_50 = _DAT_00d5780c;
  uStack_4c = 0;
  uStack_48 = 0;
  uStack_44 = 0;
  local_40 = 0;
  uStack_3c = _DAT_00d5780c;
  uStack_38 = 0;
  uStack_34 = 0;
  local_30 = 0;
  uStack_2c = 0;
  uStack_28 = _DAT_00d5780c;
  uStack_24 = 0;
  local_20 = 0;
  uStack_1c = 0;
  uStack_18 = 0;
  uStack_14 = _DAT_00d5780c;
  local_58 = 0xffffffff;
  local_54 = 0;
  local_64[1] = 5;
  
  // Call some processing function
  piVar5 = (int *)FUN_004df270(local_64, param_1 + 0x4c, &local_50, 0xffffffff, 2, local_64 + 1);
  
  // Manage linked list at param_2 + 0x18
  iVar2 = *(int *)(iVar3 + 0x18);
  piVar1 = (int *)(iVar3 + 0x18);
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 8) = 0;  // Clear next pointer
    *piVar1 = 0;  // Clear head
  }
  iVar2 = *piVar5;
  *piVar1 = iVar2;  // Set new head
  if (iVar2 != 0) {
    *(int **)(iVar2 + 8) = piVar1;  // Set previous pointer
    *piVar5 = 0;  // Clear source
  }
  
  // Cleanup
  if (local_64[0] != 0) {
    *(undefined4 *)(local_64[0] + 8) = 0;
  }
  
  // Free allocated object if list is non-empty
  if (*(int *)(param_2 + 0x18) != 0) {
    FUN_004df830(*(undefined4 *)(param_2 + 0x1c));
  }
  
  // Destructor call
  if (param_2 != 0) {
    FUN_004daf90(&param_2);
  }
  
  return;
}