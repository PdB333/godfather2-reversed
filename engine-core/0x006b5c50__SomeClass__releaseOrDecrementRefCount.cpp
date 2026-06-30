// FUNC_NAME: SomeClass::releaseOrDecrementRefCount
void __thiscall FUN_006b5c50(int this, int param_2)
{
  uint uVar1;
  int iVar2;
  undefined **local_14;
  int local_10;
  undefined4 local_c;
  undefined ***local_8;
  undefined1 local_4;
  
  // Check if reference count is zero
  if (*(int *)(this + 0x68) == 0) {
    return;
  }
  
  // Decrement reference count
  uVar1 = *(int *)(this + 0x68) - 1;
  *(uint *)(this + 0x68) = uVar1;
  
  // If reference count is less than or equal to some threshold, call a function
  if (*(uint *)(this + 0x6c) <= uVar1) {
    FUN_008c78b0(*(undefined4 *)(this + 0x40), 1);
  }
  
  // Check if some flag is set
  if (*(int *)(this + 0x78) != 0) {
    if (param_2 == 0) {
      // If param_2 is zero, check another field
      if (*(int *)(this + 0xac) == 0) goto LAB_006b5ce9;
      DAT_012054b4 = DAT_012054b4 + 1;
      iVar2 = FUN_00b9a1c0();
    }
    else {
      // Otherwise, call a function with param_2
      iVar2 = FUN_006b1b10(&param_2);
    }
    
    // If result is valid, call another function
    if (-1 < iVar2) {
      FUN_006b56a0(iVar2);
    }
  }
  
LAB_006b5ce9:
  // Setup some structure for cleanup or notification
  local_8 = &local_14;
  local_14 = &PTR_LAB_00d5dbb0;
  local_c = DAT_0112a5a4;
  local_4 = 0;
  local_10 = this;
  FUN_00408a00(&local_c, 0);
  return;
}