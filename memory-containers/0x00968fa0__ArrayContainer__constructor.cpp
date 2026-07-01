// FUNC_NAME: ArrayContainer::constructor
void __thiscall ArrayContainer::constructor(int* thisPtr, uint capacity, int flags)
{
  longlong lVar1;
  int* pInternal;
  uint uVar2;
  uint idx;
  
  // Offset +12 (param_1[3]): flags
  thisPtr[3] = flags;
  // Offset +4 (param_1[1]): some counter or size
  thisPtr[1] = 0;
  // Offset +8 (param_1[2]): capacity (size of arrays)
  thisPtr[2] = capacity;
  // Offset +16 (param_1[4]): another counter
  thisPtr[4] = 0;

  // Allocate internal block (12 bytes)
  pInternal = (int*)FUN_009c8e50(0xc);  // operator new(sizeof(InternalBlock))
  if (pInternal != (int*)0x0) {
    // +8 of internal block: pointer to first array (capacity+1 elements of 4 bytes)
    pInternal[2] = (int)FUN_009c8e80((capacity + 1) * 4);  // operator new[]((capacity+1)*4)
  }
  // +0 of this: store pointer to internal block
  thisPtr[0] = (int)pInternal;

  // Zero-initialize the first array
  idx = 0;
  do {
    *(int*)(*(int*)(thisPtr[0] + 8) + idx * 4) = 0;
    idx = idx + 1;
  } while (idx <= capacity);

  // Allocate second array (same size) and store at offset +20
  lVar1 = (longlong)(capacity + 1) * 4;
  thisPtr[5] = FUN_009c8e80(-((uint)((int)((ulonglong)lVar1 >> 0x20) != 0)) | (uint)lVar1);  // operator new[]((capacity+1)*4)
  return;
}