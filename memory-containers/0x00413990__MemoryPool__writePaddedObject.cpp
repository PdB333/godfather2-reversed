// FUNC_NAME: MemoryPool::writePaddedObject
void __thiscall MemoryPool::writePaddedObject(int *this, uint64_t *data)
{
  // Dereference this to get the pool header pointer (offset 0 of this)
  int *poolHeader = (int *)*this;
  // Write first vtable pointer (4 bytes) at current allocation pointer (+0x14 from pool header)
  *(int **)(poolHeader[5]) = &PTR_LAB_0110b10c; // poolHeader+0x14 is the current write pointer
  // Advance write pointer by 4
  poolHeader[5] = (int)((char *)poolHeader[5] + 4);
  // Re-read pool header (redundant, but decompiler shows it)
  poolHeader = (int *)*this;
  // Align current write pointer to 16-byte boundary
  poolHeader[5] = (int)((poolHeader[5] + 0xf) & 0xfffffff0);
  // Copy 16 bytes from data into aligned location
  uint64_t *dest = (uint64_t *)poolHeader[5];
  dest[0] = data[0];
  dest[1] = data[1];
  // Advance write pointer by 16
  poolHeader[5] = (int)((char *)poolHeader[5] + 0x10);
  // Write second vtable pointer (4 bytes) at new location
  *(int *)poolHeader[5] = DAT_012052e8;
  // Advance write pointer by 4
  poolHeader[5] = (int)((char *)poolHeader[5] + 4);
}