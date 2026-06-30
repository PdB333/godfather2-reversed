//FUNC_NAME: GhostConnection::activateGhost
undefined4 __thiscall GhostConnection::activateGhost(int this, int connection, uint ghostId)
{
  int *bucketArray;
  uint *entry;
  char isValid;
  uint ghostIndex;
  undefined4 result;
  
  if (ghostId == 0xffffffff) {
    *(undefined4 *)(this + 0x14) = 0xffffffff;
    *(undefined4 *)(this + 0x18) = 0xffffffff;
    *(undefined4 *)(this + 0x60) = 0;
    return 0;
  }
  
  // Hash table lookup: connection+0x70 points to a GhostHashTable object
  // The hash table has at +0x30 a pointer to the bucket array
  bucketArray = *(int **)(*(int *)(connection + 0x70) + 0x30);
  // bucketArray[0] is the array of bucket heads, bucketArray[1] is the number of buckets
  entry = *(uint **)(*bucketArray + (ghostId % (uint)bucketArray[1]) * 4);
  
  do {
    if (entry == (uint *)0x0) {
LAB_00581b7b:
      ghostIndex = 0;
LAB_00581b7d:
      if ((ghostIndex != 0) && (isValid = FUN_005818d0(), isValid != '\0')) {
        result = 0;
        *(uint *)(this + 0x60) = ghostIndex;
        *(uint *)(this + 0x10) = *(uint *)(this + 0x10) & 0xfffffffc | 0x20020;
        *(uint *)(this + 0x14) = ghostId;
        *(uint *)(this + 0x18) = ghostId;
        *(undefined4 *)(this + 0x1c) = 0;
        *(undefined4 *)(this + 0x20) = 0;
        *(int *)(connection + 0x7c) = this;
        FUN_005918f0(connection, *(undefined4 *)(this + 0x60), *(undefined4 *)(this + 100), 1);
        FUN_00591880(connection, *(undefined4 *)(this + 0x60), *(undefined4 *)(this + 100));
        *(undefined4 *)(this + 0x28) = *(undefined4 *)(this + 0x24);
        *(int *)(connection + 0x7c) = this;
        FUN_00591160();
        *(undefined4 *)(this + 0x24) = result;
        return 1;
      }
      return 0;
    }
    if (*entry == ghostId) {
      if ((entry != (uint *)0x0) && (entry + 1 != (uint *)0x0)) {
        ghostIndex = entry[2];
        goto LAB_00581b7d;
      }
      goto LAB_00581b7b;
    }
    entry = (uint *)entry[3];
  } while( true );
}