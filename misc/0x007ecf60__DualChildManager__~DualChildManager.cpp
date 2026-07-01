// FUNC_NAME: DualChildManager::~DualChildManager
void __thiscall DualChildManager::destroy(void* thisPtr)
{
  // thisPtr is a pointer to DualChildManager structure
  // Interpret as int array for offset access
  int* thisPtrInt = (int*)thisPtr;

  // Field at +12 (param_1[3]): second owned child pointer
  if (thisPtrInt[3] != 0) {
    // Call Release() (vtable+4) on the owner at +8 (param_1[2]) with the child pointer
    (**(void (__thiscall**)(void*, int))(*(int*)thisPtrInt[2] + 4))(thisPtrInt[3], 0);
    thisPtrInt[3] = 0;
  }
  // Call finalize function (vtable+12) on the owner at +8
  (**(void (__thiscall**)(void*))(*(int*)thisPtrInt[2] + 12))();

  // Field at +4 (param_1[1]): first owned child pointer
  if (thisPtrInt[1] != 0) {
    // Call Release() (vtable+4) on the owner at +0 (param_1[0]) with the child pointer
    (**(void (__thiscall**)(void*, int))(*(int*)thisPtrInt[0] + 4))(thisPtrInt[1], 0);
    thisPtrInt[1] = 0;
  }
  // Call finalize function (vtable+12) on the owner at +0
  (**(void (__thiscall**)(void*))(*(int*)thisPtrInt[0] + 12))();
}