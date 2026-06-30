// FUNC_NAME: EARS::Object::constructor
void __fastcall EARS_Object_constructor(void *unused, int **ppObject)
{
  int *pObject;
  void *alignedDst;
  int iVar2;
  unsigned int *srcPtr;
  unsigned int *dstPtr;
  unsigned int stackData[534]; // 0x858 bytes, but copy only 0x854

  pObject = (int *)*ppObject;
  // Set vtable pointer at offset +0x14 (object+0x14)
  *(void **)(pObject + 5) = &PTR_LAB_01124514; // offset +0x14 (int*+5 = 20 bytes)
  // Bump the vtable pointer? Actually advances by 4 (vtable adjustment)
  pObject[5] = pObject[5] + 4;

  // Copy initial data from stack (starting after parameters and return address)
  srcPtr = (unsigned int *)&unused; // actually stack0x00000004 in the original
  dstPtr = stackData;
  for (iVar2 = 533; iVar2 != 0; iVar2--) { // 533*4 = 2132 bytes = 0x854
    *dstPtr = *srcPtr;
    srcPtr++;
    dstPtr++;
  }

  pObject = (int *)*ppObject; // reload pObject? Possibly due to alignment
  // Align destination to 4-byte boundary after adding 3 then masking
  alignedDst = (void *)((pObject[5] + 3) & 0xFFFFFFFC);
  pObject[5] = (int)alignedDst;

  // Copy the inlined data (0x854 bytes) to the object
  _memcpy(alignedDst, stackData, 0x854);

  // Update the allocation pointer past the copied data
  pObject[5] = pObject[5] + 0x854;
}