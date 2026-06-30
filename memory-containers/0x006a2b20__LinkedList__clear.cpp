// FUNC_NAME: LinkedList::clear
void __fastcall LinkedList::clear(LinkedList *this)
{
  Node *currentNode;
  Node *nextNode;
  
  currentNode = (Node *)*this; // +0x00: head pointer
  while (currentNode != this) {
    nextNode = (Node *)*currentNode; // +0x00: next pointer
    FUN_009c8f10(currentNode); // deallocate node
    currentNode = nextNode;
  }
  return;
}