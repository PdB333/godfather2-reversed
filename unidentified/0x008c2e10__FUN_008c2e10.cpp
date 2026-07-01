// FUNC_NAME: unknown::FUN_008c2e10
void __thiscall FUN_008c2e10(void *thisPtr, void *param2)
{
  int priority;

  priority = 2;
  if (*(char *)((int)param2 + 0xc) != '\0') { // +0x0C: isActive or some bool flag
    priority = 0;
  }
  if (*(int *)((int)thisPtr + 0x54) == 0x637b907) { // +0x54: some ID/Type constant
    priority = 0;
  }
  if (*(int *)((int)param2 + 4) == 2) { // +0x04: something with value 2
    priority = 0;
  }
  FUN_008c2d00((int)param2 + 0x10, priority, *(undefined4 *)(*(int *)((int)param2 + 8) + 0x38)); // param2+0x10 = data, param2+8+0x38 = another param
  return;
}