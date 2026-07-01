// FUNC_NAME: RBTree::findOrInsert
undefined4 * __thiscall RBTree::findOrInsert(int this, uint *key)
{
  undefined4 *node;
  undefined4 *current;
  int *newNode;
  undefined4 *root;
  undefined4 keyBuffer[3];
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_14[8];
  
  root = *(undefined4 **)(this + 4);
  if (*(char *)((int)root[1] + 0x19) == '\0') {
    current = (undefined4 *)root[1];
    do {
      if ((uint)current[3] < *key) {
        node = (undefined4 *)current[2];
      }
      else {
        node = (undefined4 *)*current;
        root = current;
      }
      current = node;
    } while (*(char *)((int)node + 0x19) == '\0');
  }
  if ((root == *(undefined4 **)(this + 4)) || (*key < (uint)root[3])) {
    keyBuffer[0] = *key;
    local_1c = 0;
    local_18 = 0;
    FUN_008eb820(&local_1c);
    newNode = (int *)FUN_008eed50(local_14, this, root, keyBuffer);
    this = *newNode;
    root = (undefined4 *)newNode[1];
    FUN_008eb7a0();
    FUN_008eb7a0();
  }
  if (this == 0) {
    FUN_00b97aea();
  }
  if (root == *(undefined4 **)(this + 4)) {
    FUN_00b97aea();
  }
  return root + 4;
}