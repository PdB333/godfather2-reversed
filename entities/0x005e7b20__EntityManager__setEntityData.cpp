// FUNC_NAME: EntityManager::setEntityData
undefined1 __thiscall EntityManager::setEntityData(uint entityId, undefined4 data)
{
  int iVar1;
  undefined1 uVar2;
  
  uVar2 = 0;
  // XOR the entity ID with a magic constant (0xad103100) to get a hash/index
  // Check if the hash is within the valid range (stored at DAT_01223504 + 0x1c)
  if (((entityId ^ 0xad103100) < (uint)*(byte *)(DAT_01223504 + 0x1c)) &&
     // Look up the entity pointer from the hash table (DAT_01223504 + 4 + (hash & 0xff) * 4)
     (iVar1 = *(int *)(DAT_01223504 + 4 + ((entityId ^ 0xad103100) & 0xff) * 4), iVar1 != 0)) {
    // Set the data at offset +0x6c (likely a data pointer or value)
    *(undefined4 *)(iVar1 + 0x6c) = data;
    uVar2 = 1;
  }
  return uVar2;
}