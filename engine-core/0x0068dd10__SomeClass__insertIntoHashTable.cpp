// FUNC_NAME: SomeClass::insertIntoHashTable
uint __thiscall SomeClass::insertIntoHashTable(int this, undefined8 *key, uint hash1, uint hash2)
{
  uint uVar1;
  undefined8 local_24;
  undefined8 local_1c;
  undefined8 local_14;
  uint local_c;
  uint local_8;
  undefined1 local_4;
  
  local_24 = *key;
  local_1c = key[1];
  local_14 = key[2];
  local_c = hash1;
  uVar1 = hash1 & 0xffffff00;
  local_8 = hash2;
  local_4 = 1;
  if (hash2 < 6) {
    key = (undefined8 *)0x6;
    uVar1 = FUN_0068dbd0(this + 0x14, &key, &local_24);
    return uVar1;
  }
  if (hash2 < 0x10) {
    key = (undefined8 *)0x10;
    uVar1 = FUN_0068dbd0(this + 0x29c, &key, &local_24);
    return uVar1;
  }
  if (hash2 < 0x1f) {
    key = (undefined8 *)0x1f;
    uVar1 = FUN_0068dbd0(this + 0x95c, &key, &local_24);
  }
  return uVar1;
}