// FUNC_NAME: HashTable::findByKey
void __fastcall HashTable::findByKey(undefined4 this, int key, undefined4 **result)
{
  int *node;
  undefined4 *in_EAX;
  
  node = (int *)*result; // +0x00: head of linked list bucket
  while( true ) {
    if (node == (int *)0x0) {
      *in_EAX = 0; // not found
      return;
    }
    if (*(int *)(*node + 8) == key) break; // +0x08: key field in node
    node = (int *)node[1]; // +0x04: next pointer in linked list
  }
  *in_EAX = node; // found, return pointer to node
  return;
}