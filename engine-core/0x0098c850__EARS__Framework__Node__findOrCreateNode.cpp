// FUNC_NAME: EARS::Framework::Node::findOrCreateNode
undefined4 * __thiscall EARS::Framework::Node::findOrCreateNode(int this, undefined4 *outNode, int *childNode, uint *key)
{
  int *parentNode;
  uint *keyCopy;
  int siblingNode;
  undefined4 *resultNode;
  undefined1 local_8[8];
  
  keyCopy = key;
  parentNode = *(int **)(this + 4); // +0x4: parent node pointer
  if ((childNode == parentNode) || (childNode == (int *)(this + 4))) {
    if ((*(int *)(this + 0x14) != 0) && ((uint)parentNode[4] < *key)) {
      // +0x14: some flag/child count
      // parentNode[4] is likely a key value at offset +0x10
      FUN_0098c0f0(outNode, parentNode, key, 0);
      return outNode;
    }
  }
  else {
    siblingNode = FUN_00ab3c50(childNode);
    if (((uint)childNode[4] < *key) && (*key < *(uint *)(siblingNode + 0x10))) {
      if (*childNode != 0) {
        FUN_0098c0f0(outNode, siblingNode, key, 1);
        return outNode;
      }
      FUN_0098c0f0(outNode, childNode, key, 0);
      return outNode;
    }
  }
  key = (uint *)((uint)key & 0xffffff00);
  resultNode = (undefined4 *)FUN_0098c400(local_8, keyCopy, key);
  *outNode = *resultNode;
  return outNode;
}