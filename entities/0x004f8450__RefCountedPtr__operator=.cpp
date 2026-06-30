// FUNC_NAME: RefCountedPtr::operator=
void __thiscall RefCountedPtr::operator=(int *thisPtr, int *rhsPtr)
{
  int *piVar1;
  int iVar2;

  // Release current reference if non-null
  if (*thisPtr != 0) {
    piVar1 = (int *)(*thisPtr + 4);          // +0x04: reference count
    *piVar1 = *piVar1 + -1;                  // decrement ref count
    if (((int *)*thisPtr)[1] == 0) {         // ref count now zero
      (**(code **)(*(int *)*thisPtr + 4))(); // call vtable[1] (destructor/deleter)
    }
    *thisPtr = 0;                            // clear old pointer
  }

  // Acquire new reference
  iVar2 = *rhsPtr;
  *thisPtr = iVar2;
  if (iVar2 != 0) {
    *(int *)(iVar2 + 4) = *(int *)(iVar2 + 4) + 1; // increment ref count at +0x04
  }
  return;
}