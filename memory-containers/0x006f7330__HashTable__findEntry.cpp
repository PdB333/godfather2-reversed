// FUNC_NAME: HashTable::findEntry
undefined4 __thiscall HashTable::findEntry(HashTable *this, undefined4 key)
{
  int iVar1;
  
  // Check for magic markers indicating uninitialized or dead state.
  // If the block is valid (not all magic and not all zero), proceed.
  if (((((this->magic1 != 0xBABDB8BA) || (this->magic2 != 0xBEEFBEEF) ||
        (this->magic3 != 0xEAC15A55) || (this->magic4 != 0x91100911)) &&
       (((this->magic1 != 0) || (this->magic2 != 0)) &&
        ((this->magic3 != 0) || (this->magic4 != 0)))) &&
      (iVar1 = HashTable::isValid(this + 4), iVar1 != 0)) {
    // If the hash table is valid, attempt to find the given key.
    iVar1 = HashTable::lookup(key);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}