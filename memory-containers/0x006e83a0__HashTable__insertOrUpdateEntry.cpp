// FUNC_NAME: HashTable::insertOrUpdateEntry
undefined4 __thiscall HashTable::insertOrUpdateEntry(int this, int entryData)
{
  uint hash;
  undefined4 keyBytes[4];
  
  keyBytes[0] = *(undefined4 *)(entryData + 0x10);
  keyBytes[1] = *(undefined4 *)(entryData + 0x14);
  keyBytes[2] = *(undefined4 *)(entryData + 0x18);
  keyBytes[3] = *(undefined4 *)(entryData + 0x1c);
  
  // Hash function call (likely a CRC or custom hash)
  FUN_004d9af0();
  
  // Compute hash of the 16-byte key
  hash = FUN_004db320(keyBytes, 0x10);
  
  // Insert/update entry at computed bucket index (modulo table size)
  // param_1 + 4 = table size (number of buckets)
  FUN_006e7830(entryData + 0x10, entryData, hash % *(uint *)(this + 4));
  
  return 0;
}