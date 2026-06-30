// FUNC_NAME: EARSStreamManager::createStreamInstance
undefined4 * EARSStreamManager::createStreamInstance(int this, undefined4 *outInstance)

{
  undefined4 uVar1;
  
  if (outInstance != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(*(int *)(this + 4) + 0xc);
    FUN_00533cc0();
    outInstance[9] = uVar1;  // +0x24 - stream ID / handle
    *outInstance = &PTR_FUN_00e374d0;  // vtable pointer
    return outInstance;
  }
  return (undefined4 *)0x0;
}