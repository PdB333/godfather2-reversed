// FUNC_NAME: SomeListManager::processAndRemoveItem
void __fastcall SomeListManager::processAndRemoveItem(int this)
{
  int *listNode;
  int itemPtr;
  int *currentNode;
  
  currentNode = *(int **)(this + 0x34); // +0x34: linked list head (sentinel)
  if (currentNode != (int *)(this + 0x34)) {
    while (((itemPtr = currentNode[2], itemPtr == 0 || ((undefined4 *)(itemPtr + -0x1c) == (undefined4 *)0x0))
           || (*(char *)(itemPtr + 0x2c) == '\0'))) {
      currentNode = (int *)*currentNode; // move to next node
      if (currentNode == (int *)(this + 0x34)) {
        return;
      }
    }
    listNode = (int *)(this + 0xb4); // +0xB4: pointer to some tracked item
    if ((*listNode == currentNode[2]) && (*listNode != 0)) {
      FUN_004daf90(listNode); // likely release/delete
      *listNode = 0;
    }
    FUN_0089f970(currentNode + 2); // process the item at currentNode+2
    (*(code *)**(undefined4 **)(itemPtr + -0x1c))(1); // virtual call with arg 1
  }
  return;
}