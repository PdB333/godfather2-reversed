// FUNC_NAME: HashTable::removeByKey
void HashTable::removeByKey(uint key)
{
  uint *puVar1;
  
  puVar1 = *(uint **)(*DAT_0112bb2c + (key % (uint)DAT_0112bb2c[1]) * 4);
  while( true ) {
    if (puVar1 == (uint *)0x0) {
      return;
    }
    if (*puVar1 == key) break;
    puVar1 = (uint *)puVar1[2];
  }
  if (puVar1 == (uint *)0x0) {
    return;
  }
  // Remove the node from the hash table (likely unlinks and frees)
  FUN_007e7df0();
  return;
}