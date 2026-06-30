// FUNC_NAME: HashTable::insertOrUpdate
void HashTable::insertOrUpdate(int param_1, uint key, char *value)
{
  int *piVar1;
  uint hash;
  uint *bucket;
  uint bucketIndex;
  
  hash = FUN_004dafd0(key);
  bucket = *(uint **)(**(int **)(param_1 + 0x30) +
                     (hash % (uint)(*(int **)(param_1 + 0x30))[1]) * 4);
  do {
    if (bucket == (uint *)0x0) {
LAB_00573275:
      piVar1 = *(int **)(param_1 + 0x30);
      bucketIndex = hash % (uint)piVar1[1];
      if (((char)piVar1[5] != '\0') && ((uint)(piVar1[1] * 2) <= (uint)piVar1[3])) {
        FUN_00573bb0(piVar1);
        bucketIndex = hash % (uint)piVar1[1];
      }
      bucket = (uint *)FUN_00573b40();
      bucket[1] = key;
      bucket[2] = (uint)value;
      *bucket = hash;
      bucket[3] = *(uint *)(*piVar1 + bucketIndex * 4);
      *(uint **)(*piVar1 + bucketIndex * 4) = bucket;
      return;
    }
    if (*bucket == hash) {
      if ((bucket != (uint *)0x0) && (bucket != (uint *)0xfffffffc)) {
        if (*value != '\x02') {
          return;
        }
        if (*(int **)(value + 4) == (int *)0x0) {
          return;
        }
        if (((*(char *)bucket[2] == '\x02') &&
            (piVar1 = *(int **)((char *)bucket[2] + 4), piVar1 != (int *)0x0)) &&
           (**(int **)(value + 4) <= *piVar1)) {
          return;
        }
        FUN_005737c0();
      }
      goto LAB_00573275;
    }
    bucket = (uint *)bucket[3];
  } while( true );
}