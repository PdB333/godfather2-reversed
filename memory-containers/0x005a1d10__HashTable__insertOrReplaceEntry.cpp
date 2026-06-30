// FUNC_NAME: HashTable::insertOrReplaceEntry
void HashTable::insertOrReplaceEntry(HashTable *this, int *entry)
{
  int *bucket;
  int bucketIndex;
  int cmpResult;
  int *existingEntry;
  int *headBucket;
  bool charMatch;
  int i;
  
  bucket = this;
  headBucket = (int *)this[2];
  bucketIndex = *this * 0x20;
  if (headBucket != headBucket + *this * 8) {
    do {
      charMatch = *headBucket == *entry;
      i = 0;
      if (charMatch) {
        do {
          if (*headBucket <= i) {
            if (charMatch) {
              if (headBucket[7] != 1) {
                return;
              }
              headBucket[7] = 3;
              return;
            }
            break;
          }
          charMatch = *(char *)(i + headBucket[2]) == *(char *)(i + entry[2]);
          i = i + 1;
        } while (charMatch);
      }
      headBucket = headBucket + 8;
    } while (headBucket != (int *)(this[2] + bucketIndex));
  }
  this = (int *)bucketIndex;
  FUN_005a0a00(entry);
  bucketIndex = *bucket * 0x20 + bucket[2];
  // unknown: local_4 = 2
  // unknown: stack manipulation for FUN_005a3480
  this = (int *)register0x00000010;
  // FUN_005a3480 is likely a container destructor or list cleanup
  FUN_005a3480(&local_28,&stack0x00000004);
  if ((local_18 != local_14) && (local_18 != (undefined1 *)0x0)) {
    (*DAT_0119caf4)(local_18);
  }
  return;
}