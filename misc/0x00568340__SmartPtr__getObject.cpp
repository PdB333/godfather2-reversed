// FUNC_NAME: SmartPtr::getObject
undefined4 __fastcall SmartPtr_getObject(int this)
{
  undefined4 uVar1;
  
  if (*(int *)(this + 0xc) != 0) {
    // Dereference wrapper object at +0x0C to get actual pointer,
    // then call vtable function at offset 0x24 (likely addRef or some getter)
    uVar1 = (**(code **)(**(int **)(this + 0xc) + 0x24))();
    return uVar1;
  }
  return 0;
}