// FUNC_NAME: resourceArrayCleanup

void __fastcall ResourceArrayContainer::clear(int this)
{
  uint count;
  int arrayPtr;
  int *entryPtr;
  char tempBuf;
  uint i;

  count = *(int *)(this + 0xc4); // number of entries
  if (count != 0) {
    i = 0;
    do {
      entryPtr = (int *)(*(int *)(this + 0xc0) + i * 0x10); // base of entry (0x10 bytes each)
      if (entryPtr[2] != 0) { // third pointer at offset +8 in entry
        releaseExternalResource(&tempBuf, entryPtr[2]); // FUN_009e71f0
        onResourceReleased(); // FUN_009f01a0
        entryPtr[2] = 0;
      }
      if ((void *)entryPtr[1] != (void *)0x0) { // second pointer at offset +4
        (*(void (__thiscall **)(void *, int))entryPtr[1])((void *)entryPtr[1], 1); // virtual destructor with delete flag
        entryPtr[1] = 0;
      }
      if ((void *)entryPtr[0] != (void *)0x0) { // first pointer at offset +0
        (*(void (__thiscall **)(void *, int))entryPtr[0])((void *)entryPtr[0], 1); // virtual destructor with delete flag
        entryPtr[0] = 0;
      }
      i++;
    } while (i < count);
  }
  *(int *)(this + 0xc4) = 0; // clear count
  if (*(int *)(this + 0xc0) != 0) {
    deallocateArray(*(int *)(this + 0xc0)); // FUN_009c8f10
  }
  *(int *)(this + 0xc0) = 0; // clear array pointer
  *(int *)(this + 0xc8) = 0; // clear field at +0xC8 (200)
}