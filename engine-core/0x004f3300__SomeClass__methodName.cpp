// FUNC_NAME: SomeClass::methodName
undefined4 * SomeClass::methodName(int this, undefined4 *param_2)
{
  if (param_2 != (undefined4 *)0x0) {
    baseClassConstructor(); // FUN_00533cc0 - likely base class constructor
    *param_2 = &vtablePtr; // PTR_FUN_00e37670 - vtable setup
    if (*(char *)(this + 0xd) == '\0') {
      initializeSomething(); // FUN_004f3780 - conditional initialization based on flag at +0x0D
    }
    return param_2;
  }
  return (undefined4 *)0x0;
}