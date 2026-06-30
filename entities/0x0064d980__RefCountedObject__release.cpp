// FUNC_NAME: RefCountedObject::release
void RefCountedObject::release(void)
{
  int *piVar1;
  int iVar2;
  int this;
  int *refCountPtr;
  
  if (refCountPtr != (int *)0x0) {
    refCountPtr[2] = refCountPtr[2] + 1;  // +0x08: increment ref count
  }
  if ((*(uint *)(this + 0x30) >> 1 & 1) == 0) {  // +0x30: flags, check bit 1
    if (DAT_01205a24 == 0) {
      for (iVar2 = *(int *)(this + 0x1c); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0xc)) {  // +0x1c: linked list head, +0x0c: next
        if ((*(byte *)(iVar2 + 0x20) & 0x3c) == 0) {  // +0x20: flags, check bits 2-5
          FUN_0064ef60(refCountPtr);
        }
      }
    }
    else {
      FUN_0064ef60(refCountPtr);
    }
  }
  else {
    FUN_0064ef60(refCountPtr);
  }
  if (refCountPtr != (int *)0x0) {
    piVar1 = refCountPtr + 2;  // +0x08: ref count
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      (**(code **)(*refCountPtr + 8))();  // vtable[2] = destructor
      return;
    }
  }
  return;
}