// FUNC_NAME: RefCountedPointer::release
void __fastcall RefCountedPointer::release(int param_1)
{
  int *piVar1;
  
  if (*(int *)(param_1 + 0x10) != 0) {
    piVar1 = (int *)(*(int *)(param_1 + 0x10) + 4);
    *piVar1 = *piVar1 + -1;
    if ((*(int **)(param_1 + 0x10))[1] == 0) {
      (**(code **)(**(int **)(param_1 + 0x10) + 4))();
    }
    *(undefined4 *)(param_1 + 0x10) = 0;
  }
  return;
}