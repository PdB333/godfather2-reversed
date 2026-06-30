// FUNC_NAME: SomeClass::compareAndNotify
void __fastcall SomeClass::compareAndNotify(int *param_1)
{
  int iVar1;
  int in_EAX;
  int iVar2;
  undefined1 local_1c [20];
  undefined1 local_8;
  
  // Get value from this+0x18
  iVar1 = *(int *)(in_EAX + 0x18);
  
  // Check if param_1+0x2C has bit 5 set and param_1[0] < 2
  if (((*(byte *)(param_1 + 0xb) & 0x20) == 0) || (*param_1 < 2)) {
    // Use param_1[5] (offset 0x14)
    iVar2 = param_1[5];
  }
  else {
    // Use param_1[7] (offset 0x1C)
    iVar2 = param_1[7];
  }
  
  // Call some function (likely a notification or update)
  FUN_00579870();
  
  // Store comparison result
  local_8 = iVar1 == iVar2;
  
  // Call another function with this and local buffer
  FUN_00579450(in_EAX, local_1c);
  
  return;
}