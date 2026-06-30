// FUNC_NAME: StringTable::setEntryActive
void __fastcall StringTable::setEntryActive(int *this)
{
  int index = *reinterpret_cast<int*>(in_EAX + 4);  // offset from some base, likely an index into the array
  uint *entryPtr = reinterpret_cast<uint*>(*(int*)(*this + 0xc) + index * 4); // base + offset*4

  // If there is a previous entry and the character classification table indicates it's an alphabetic character,
  // move to the previous entry (likely to merge with a multi-character token)
  if (index > 0 && (("$a $ a4A"[entryPtr[-1] & 0x3f] & 0x80) != 0)) {
    entryPtr--;
  }

  // Set the high byte of this entry to 0x01 if it was 0x00 (mark as active/used)
  uint old = *entryPtr;
  *entryPtr = (old & 0xffffff) | ((uint)((old & 0xff000000) == 0) * 0x1000000);
}