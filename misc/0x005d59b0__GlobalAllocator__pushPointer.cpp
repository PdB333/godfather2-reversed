// FUNC_NAME: GlobalAllocator::pushPointer
void FUN_005d59b0(void* param_1)
{
  int* piVar1;
  
  piVar1 = (int *)(DAT_01206880 + 0x14); // +0x14: current allocation offset in global allocator
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126c80; // set vtable pointer
  *piVar1 = *piVar1 + 4; // advance offset by 4
  *(undefined4 *)*piVar1 = param_1; // store the pointer
  *piVar1 = *piVar1 + 4; // advance offset by 4 again
  return;
}