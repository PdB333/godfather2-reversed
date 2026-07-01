// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(int thisPtr, undefined4 param_2)
{
  undefined4 *newObj;
  
  if ((thisPtr != 0) && (newObj = (undefined4 *)FUN_009c8e50(0x84), newObj != (undefined4 *)0x0)) {
    FUN_008d3980();
    newObj[7] = param_2;          // +0x1C: store param_2
    newObj[0x12] = thisPtr;       // +0x48: store this pointer
    *newObj = &PTR_FUN_00d7d504;  // +0x00: vtable pointer
    newObj[0x13] = &PTR_LAB_00d7d4f4; // +0x4C: some other pointer
    return newObj;
  }
  return (undefined4 *)0x0;
}