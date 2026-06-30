// FUNC_NAME: HashTable::findByKey
void __thiscall HashTable::findByKey(undefined4 *this, int *key)
{
  int *bucketList;
  int *currentNode;
  int *prevNode;
  int hashIndex;
  int *node;
  
  bucketList = (int *)*this;
  for (hashIndex = this[1]; hashIndex >= 0; hashIndex = hashIndex + -1) {
    currentNode = *(int **)(bucketList[2] + hashIndex * 4);
    if (currentNode != (int *)0x0) {
      do {
        prevNode = currentNode;
        if (*key <= *currentNode) break;
        currentNode = *(int **)(currentNode[2] + hashIndex * 4);
        bucketList = prevNode;
      } while (currentNode != (int *)0x0);
    }
    node = *(int **)bucketList[2];
    if (node == (int *)0x0) break;
    if (*node == *key) {
      *in_EAX = (int)node;
      return;
    }
  }
  *in_EAX = 0;
  return;
}