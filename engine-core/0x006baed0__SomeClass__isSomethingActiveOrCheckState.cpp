// FUNC_NAME: SomeClass::isSomethingActiveOrCheckState
uint __fastcall SomeClass::isSomethingActiveOrCheckState(int thisPtr)
{
  char cVar1;
  undefined1 local_c [12];

  if ((*(int *)(thisPtr + 0x9c) != 0) && ((*(uint *)(thisPtr + 0x84) >> 0x1e & 1) == 0)) {
    cVar1 = FUN_008824c0(*(int *)(thisPtr + 0x9c) + 0x28, local_c);
    if (cVar1 == '\0') {
      *(uint *)(thisPtr + 0x84) = *(uint *)(thisPtr + 0x84) & 0x7fffffff;
    }
    else {
      *(uint *)(thisPtr + 0x84) = *(uint *)(thisPtr + 0x84) | 0x80000000;
    }
    *(uint *)(thisPtr + 0x84) = *(uint *)(thisPtr + 0x84) | 0x40000000;
  }
  return *(uint *)(thisPtr + 0x84) >> 0x1f;
}