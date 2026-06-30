// FUNC_NAME: NodeListManager::destructor
void __fastcall NodeListManager::destructor(NodeListManager *this)
{
  Node *currentNode;
  Node *nextNode;

  this->vtable = &BASE_VTABLE_A;
  if (this->someResource != 0) {
    someFreeFunction(&this->someResource);
  }
  this->vtable = &BASE_VTABLE_B;
  currentNode = this->listHead;
  while (currentNode != 0) {
    nextNode = currentNode->next;
    currentNode->next = 0;
    currentNode->data = 0;
    currentNode = nextNode;
  }
}