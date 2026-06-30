// FUNC_NAME: MemoryManagedObject::freeTwoArraysAndSetVtableToDeleted
void __fastcall MemoryManagedObject::freeTwoArraysAndSetVtableToDeleted(uint *this)
{
  uint countA;
  uint countB;

  // Free first array (element size 0xC)
  countA = this[7];                              // +0x1C: countA
  if ((int)countA >= 0)
  {
    TlsGetValue(g_TlsIndex);                     // Retrieve thread-local heap context
    HeapFree((void *)this[5],                    // +0x14: pointer to arrayA
             (countA & 0x3FFFFFFF) * 0xC,        // Total size
             0x17);                              // Deallocation tag
  }

  // Free second array (element size 0x30)
  countB = this[4];                              // +0x10: countB
  if ((int)countB >= 0)
  {
    TlsGetValue(g_TlsIndex);
    HeapFree((void *)this[2],                    // +0x08: pointer to arrayB
             (countB & 0x3FFFFFFF) * 0x30,
             0x17);
  }

  // Mark object as destroyed by setting vtable to sentinel
  *this = PTR_g_VtableDeleted;                   // +0x00: vtable pointer
}