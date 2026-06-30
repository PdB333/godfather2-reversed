// FUNC_NAME: List::addToFront
void __thiscall List::addToFront(List *this, Entity *entity) // 'entity' is the object containing the list node at +0x48
{
  int **headNextPtr = (int **)((int)this + 0x140); // address of head->next (pointer to first node)
  int *newNode = entity == 0 ? 0 : (int *)((int)entity + 0x48); // node inside entity at +0x48

  if (*headNextPtr != newNode) {
    if (*headNextPtr != 0) {
      // Remove old first node from list (probably unlinking it)
      FUN_004daf90(headNextPtr);
    }
    *headNextPtr = newNode; // head->next = newNode
    if (newNode != 0) {
      // head->prev = newNode->prev
      *(int *)((int)this + 0x144) = *(int *)((int)newNode + 4); 
      // newNode->prev = &head->next (i.e., address of head's next pointer)
      *(int **)((int)newNode + 4) = headNextPtr;
    }
  }
}