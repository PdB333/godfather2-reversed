// FUNC_NAME: UIWaveManager::constructor (or similar UI/game manager)
undefined4 * __thiscall UIWaveManagerConstructor(undefined4 *thisPtr, int param_2)
{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = CallSomething(); // FUN_00481610
  }
  CallTwoParamFunc(2, 1); // FUN_0064d390
  *thisPtr = &PTR_LAB_00e317dc; // Set vtable pointer
  thisPtr[6] = 0; // Some member at +0x18 initialized to 0
  CallOneParamFunc(uVar1); // FUN_00454a10
  thisPtr[9] = 1; // +0x24 set to 1
  *thisPtr = &PTR_LAB_00d6a930; // Change vtable to another one
  thisPtr[10] = &PTR_LAB_00d6a6c4; // +0x28 points to some static data
  thisPtr[0xc] = &LAB_0079b170; // +0x30 points to another function/label
  thisPtr[0xd] = 0; // +0x34 initialized to 0
  thisPtr[5] = thisPtr + 10; // +0x14 points to +0x28 (self-referential pointer)
  return thisPtr;
}