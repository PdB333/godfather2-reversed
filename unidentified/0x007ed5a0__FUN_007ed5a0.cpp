// FUNC_NAME: SomeClass::constructorWithParams
int __thiscall SomeClass::constructorWithParams(int thisPtr, int *someObject, int param3)
{
  undefined4 uVar1;
  int *piVar2;
  
  piVar2 = someObject;
  (**(code **)(*someObject + 8))(someObject);  // vtable call at offset 8 (likely addRef or similar)
  if (param3 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_004265d0(param3, piVar2);  // some conversion/duplication function
  }
  FUN_007ecfd0(piVar2, uVar1);  // initialization helper
  *(int **)(thisPtr + 0x10) = someObject;  // store someObject at +0x10
  (**(code **)(*someObject + 8))();  // vtable call at offset 8 again
  if (param3 != 0) {
    uVar1 = FUN_004265d0(param3, *(undefined4 *)(thisPtr + 0x10));  // convert again with stored object
    *(undefined4 *)(thisPtr + 0x14) = uVar1;  // store result at +0x14
    (**(code **)(*someObject + 4))(param3, 0);  // vtable call at offset 4 (setParam?)
    (**(code **)(*someObject + 0xc))();  // vtable call at offset 12 (finalize?)
    return thisPtr;
  }
  *(undefined4 *)(thisPtr + 0x14) = 0;  // clear +0x14
  (**(code **)(*someObject + 0xc))();  // vtable call at offset 12
  return thisPtr;
}