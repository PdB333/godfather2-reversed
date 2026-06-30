// FUNC_NAME: SomeEARSObject::processEvent
uint SomeEARSObject::processEvent(int eventData)
{
  // +0x08: pointer to something (passed to FUN_004d3bc0)
  FUN_004d3bc0(eventData + 8);
  
  // Call some function with this and a local buffer
  int result;
  int output[3];
  // unaff_EDI is actually 'this' (passed in EDI register)
  int iVar1 = FUN_005653d0(this, output);
  
  if (output[0] != 0) {
    // Call a function pointer (possibly from a register or global)
    // local_4 appears uninitialized in decompiled output; might be a register
    // that holds a callback, but we don't have it. For now, we note it.
    // (*someCallback)(output[0]);
  }
  
  char* stringPtr = *(char**)(iVar1 + 0x24);  // +0x24: string field
  if (stringPtr == NULL) {
    stringPtr = &DAT_0120546e;  // Default string "None" or similar
  }
  
  uint uVar3 = FUN_005655c0(stringPtr, 1);  // Some comparison/lookup
  if ((char)uVar3 == '\0') {
    // Virtual call: vtable at +0x20, function at offset 0x28
    // 'this' is passed as eventData? Actually param_1 is passed.
    uVar3 = (*(code**)(*(int**)(this + 0x20) + 0x28))(eventData);
  }
  
  return uVar3 & 0xffffff00;
}