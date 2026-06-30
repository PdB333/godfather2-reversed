// FUNC_NAME: SomeClass::incrementAndProcess
void __fastcall incrementAndProcess(int thisPtr)
{
  int count;
  
  *(int *)(thisPtr + 0x78) = *(int *)(thisPtr + 0x78) + 1;  // +0x78: some counter
  if ((*(int *)(thisPtr + 0x78) == 1) &&
     (count = *(int *)(thisPtr + 0x68) - *(int *)(thisPtr + 0xac), 0 < count)) {  // +0x68: some limit, +0xac: some offset
    do {
      FUN_006b4b50();  // process function
      count = count + -1;
    } while (count != 0);
  }
  return;
}