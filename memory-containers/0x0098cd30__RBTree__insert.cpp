// FUNC_NAME: RBTree::insert
undefined4 * __thiscall RBTree::insert(int this, uint *key)
{
  undefined4 *currentNode;
  undefined4 *parentNode;
  undefined4 *childNode;
  undefined4 *newNode;
  uint localKey;
  int localCallback;
  code *localCallbackFunc;
  
  currentNode = (undefined4 *)(this + 4);
  parentNode = currentNode;
  if (*(undefined4 **)(this + 0xc) != (undefined4 *)0x0) {
    childNode = *(undefined4 **)(this + 0xc);
    do {
      if ((uint)childNode[4] < *key) {
        newNode = (undefined4 *)*childNode;
      }
      else {
        newNode = (undefined4 *)childNode[1];
        parentNode = childNode;
      }
      childNode = newNode;
    } while (newNode != (undefined4 *)0x0);
  }
  if ((parentNode == currentNode) || (*key < (uint)parentNode[4])) {
    localKey = *key;
    FUN_004dba00(0,0);
    key = (uint *)((uint)key & 0xffffff00);
    FUN_0098c850(&key,parentNode,&localKey,key);
    parentNode = key;
    if (localCallback != 0) {
      (*localCallbackFunc)(localCallback);
    }
  }
  return parentNode + 5;
}