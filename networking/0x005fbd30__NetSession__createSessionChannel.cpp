// FUNC_NAME: NetSession::createSessionChannel
int NetSession::createSessionChannel(int param_1, int *param_2, int param_3)
{
  undefined4 uVar1;
  int *piVar2;
  
  piVar2 = param_2;
  // AddRef on the channel object via vtable at offset +8
  (**(code **)(*param_2 + 8))(param_2);
  if (param_3 == 0) {
    uVar1 = 0;
  }
  else {
    // Clone/duplicate data using some copy function
    uVar1 = FUN_004265d0(param_3, piVar2);
  }
  // Initialize internal channel link list entry
  FUN_005fc2c0(piVar2, uVar1);
  // Store the channel pointer at +0x10
  *(int **)(param_1 + 0x10) = param_2;
  // Another AddRef
  (**(code **)(*param_2 + 8))();
  if (param_3 != 0) {
    uVar1 = FUN_004265d0(param_3, *(undefined4 *)(param_1 + 0x10));
    // Store cloned data reference at +0x14
    *(undefined4 *)(param_1 + 0x14) = uVar1;
    // Release original channel via vtable offset +4
    (**(code **)(*param_2 + 4))(param_3, 0);
    // Notify some listener via vtable offset +12
    (**(code **)(*param_2 + 0xc))();
    return param_1;
  }
  // No param_3: clear data reference
  *(undefined4 *)(param_1 + 0x14) = 0;
  (**(code **)(*param_2 + 0xc))();
  return param_1;
}