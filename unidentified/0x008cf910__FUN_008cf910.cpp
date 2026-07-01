// FUNC_NAME: SomeClass::releaseRefOrDestructor
void __fastcall SomeClass::releaseRefOrDestructor(void *thisPtr)
{
  int *piVar1;
  
  *(int **)thisPtr = &PTR_FUN_00d7cd90; // vtable pointer assignment (likely destructor or release)
  if (*(int *)((int)thisPtr + 0x24) != 0) { // param_1[9] -> offset 0x24 (some ref-counted object)
    piVar1 = (int *)(*(int *)((int)thisPtr + 0x24) + 4); // get refCount field at +4 of the inner object
    *piVar1 = *piVar1 + -1; // decrement ref count
    if (((int *)*(int *)((int)thisPtr + 0x24))[1] == 0) { // check if ref count reached 0
      (**(code (**)(void))(*(int *)*(int *)((int)thisPtr + 0x24) + 4))(); // call destructor via vtable
    }
    *(int *)((int)thisPtr + 0x24) = 0; // clear pointer
  }
  if (*(int *)((int)thisPtr + 0x20) != 0) { // param_1[8] -> offset 0x20 (another pointer)
    *(int *)(*(int *)((int)thisPtr + 0x20) + 8) = 0; // clear some field at +8 of that object
    *(int *)((int)thisPtr + 0x20) = 0; // clear pointer
  }
  FUN_004a7810(); // possibly global cleanup or deallocation
  return;
}