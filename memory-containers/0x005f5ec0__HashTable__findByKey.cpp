// FUNC_NAME: HashTable::findByKey
int __thiscall HashTable::findByKey(int this, int table, int key)
{
  int iVar1;
  int iVar2;
  
  key = key - *(int *)(this + 0x20);  // +0x20: base offset for key adjustment
  iVar2 = 0;
  if (*(byte *)(table + 0x14) == 0) { // +0x14: count of entries
    return 0;
  }
  do {
    // +0x10: hash seed, +0x24: entry array base
    iVar1 = ((uint)*(ushort *)(table + 0x10) + iVar2 & 0xffff) * 0x10 + *(int *)(this + 0x24);
    // +4: stored key field in entry (16 bytes per entry)
    if (*(short *)(iVar1 + 4) ==
        (short)(((short)(key / 0x24) + (short)(key >> 0x1f)) -
               (short)((longlong)key * 0x38e38e39 >> 0x3f))) {
      return iVar1;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < (int)(uint)*(byte *)(table + 0x14));
  return 0;
}