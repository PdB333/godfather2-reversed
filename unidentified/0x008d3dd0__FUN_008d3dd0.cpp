// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(int param_1, undefined4 param_2)
{
  undefined4 *puVar1;
  
  if ((param_1 != 0) && (puVar1 = (undefined4 *)operatorNew(0x84), puVar1 != (undefined4 *)0x0)) {
    SomeBaseClass::constructor();
    puVar1[7] = param_2;  // +0x1C: store param_2
    puVar1[0x12] = param_1;  // +0x48: store param_1
    *puVar1 = &vtable_SomeClass;  // +0x00: set vtable pointer
    puVar1[0x13] = &someDataPtr;  // +0x4C: set some data pointer
    return puVar1;
  }
  return (undefined4 *)0x0;
}