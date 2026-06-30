// FUNC_NAME: EARSObject::processInput
undefined4 __thiscall EARSObject::processInput(int *thisPtr, undefined4 param2, undefined4 param3)
{
  char cVar1;
  undefined4 uStack_48;
  undefined4 *puStack_44;
  undefined4 uStack_40;
  undefined1 *puStack_3c;
  undefined4 uStack_38;
  undefined4 *puStack_34;
  undefined4 uStack_30;
  undefined4 *puStack_2c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined4 local_c;
  
  puStack_2c = &local_10;
  local_c = 0;
  uStack_30 = param2;
  local_10 = 0;
  puStack_34 = (undefined4 *)0x543193;
  // Call virtual function at vtable+0x1f8 (likely isInputEnabled or similar)
  cVar1 = (**(code **)(*thisPtr + 0x1f8))();
  if (cVar1 != '\0') {
    puStack_34 = &uStack_18;
    uStack_18 = 0;
    uStack_14 = 0;
    uStack_38 = param3;
    puStack_3c = (undefined1 *)0x5431be;
    // Second call to the same vtable function (check input state)
    cVar1 = (**(code **)(*thisPtr + 0x1f8))();
    if (cVar1 != '\0') {
      puStack_3c = &stack0xffffffe0;
      uStack_40 = param2;
      puStack_44 = (undefined4 *)0x5431f6;
      // Third call to vtable+0x1f8 (process input)
      (**(code **)(*thisPtr + 0x1f8))();
      puStack_44 = &uStack_30;
      uStack_48 = param3;
      // Fourth call to vtable+0x1f8 (process input)
      (**(code **)(*thisPtr + 0x1f8))();
      // Call vtable+0x210 with param 0 and address of uStack_30 (likely releaseInput or similar)
      (**(code **)(*thisPtr + 0x210))(0,&uStack_30);
      // Call vtable+0x210 with param 0 and address of uStack_40
      (**(code **)(*thisPtr + 0x210))(0,&uStack_40);
      // Call vtable+0x210 with param2 and address of uStack_48
      (**(code **)(*thisPtr + 0x210))(param2,&uStack_48);
      // Call vtable+0x210 with param3 and address of uStack_48
      (**(code **)(*thisPtr + 0x210))(param3,&uStack_48);
      return 1;
    }
  }
  return 0;
}