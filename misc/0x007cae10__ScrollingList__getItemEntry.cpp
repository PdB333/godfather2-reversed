// FUNC_NAME: ScrollingList::getItemEntry
int __thiscall ScrollingList::getItemEntry(int this, int index, undefined4 param_3)
{
  int entryIndex;
  
  if ((*(int *)(this + 0x30) != 0) && (-1 < index)) {
    if ((*(int *)(this + 0x18) == 0) || (*(int *)(this + 0x14) <= index)) {
      entryIndex = 0;
    }
    else {
      entryIndex = FUN_006eca80(param_3);  // likely some hash/key lookup
    }
    if (*(int *)(this + 0x1c) != 0) {     // +0x1c: itemEntryArray pointer
      return *(int *)(this + 0x1c) + entryIndex * 0xc;  // each entry is 12 bytes
    }
  }
  return 0;
}