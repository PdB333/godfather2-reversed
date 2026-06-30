// FUNC_NAME: RefCountedPtrArray::removeRef
void __thiscall RefCountedPtrArray::removeRef(int this, int *ptr)
{
  undefined4 **slot;
  int *arrayBase;
  undefined1 *local_14;
  undefined4 *local_10;
  int local_c;
  
  slot = *(undefined4 ***)(this + 0xc);
  arrayBase = (int *)(this + 4);
  if (slot != (undefined4 *)(*(int *)(this + 0xc) + *(int *)(this + 4) * 4)) {
    do {
      if ((int *)*slot == ptr) {
        if (ptr == (int *)0x0) {
          return;
        }
        *ptr = *ptr + -1;
        goto LAB_005a2838;
      }
      slot = slot + 1;
    } while (slot != (undefined4 *)(*(int *)(this + 0xc) + *arrayBase * 4));
  }
  local_c = *(int *)(this + 0xc) + *arrayBase * 4;
  local_14 = &stack0x00000008;
  local_10 = &ptr;
  FUN_005a3320(arrayBase,&local_10,&local_14);  // array insertion helper
  if (ptr != (int *)0x0) {
    *ptr = *ptr + -1;
LAB_005a2838:
    arrayBase = ptr;
    if ((*ptr == 0) && (ptr != (int *)0x0)) {
      FUN_005a1b40();  // free memory
      (*DAT_0119caf8)(arrayBase,0x30);  // operator delete
    }
  }
  return;
}