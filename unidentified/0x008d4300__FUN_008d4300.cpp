// FUNC_NAME: SomeClass::Constructor
undefined4 * SomeClass::Constructor(int param_1, undefined4 param_2)

{
  undefined4 *puVar1;
  
  if ((param_1 != 0) && (puVar1 = (undefined4 *)operator_new(0x88), puVar1 != (undefined4 *)0x0)) {
    FUN_008d3ec0(); // Likely base class constructor or initialization
    puVar1[7] = param_2; // +0x1C: store some parameter
    puVar1[0x12] = param_1; // +0x48: store the input parameter
    *puVar1 = &PTR_FUN_00d7d5e0; // +0x00: set vtable pointer
    puVar1[0x13] = &PTR_LAB_00d7d5d0; // +0x4C: set some function pointer or data pointer
    return puVar1;
  }
  return (undefined4 *)0x0;
}