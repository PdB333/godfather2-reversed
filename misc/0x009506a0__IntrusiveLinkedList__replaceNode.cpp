// FUNC_NAME: IntrusiveLinkedList::replaceNode
void __thiscall IntrusiveLinkedList_ReplaceNode(int this, int newNode)
{
  int *linkField = (int *)(this + 0x170); // +0x170: pointer to node in linked list (head or next)
  
  int adjustedNewNode;
  if (newNode == 0) {
    adjustedNewNode = 0;
  }
  else {
    adjustedNewNode = newNode + 0x48; // +0x48: offset of 'next' pointer within node
  }
  
  if (*linkField != adjustedNewNode) {
    if (*linkField != 0) {
      FUN_004daf90(linkField); // likely removeFromList(linkField) or unlinkNode
    }
    *linkField = adjustedNewNode;
    if (adjustedNewNode != 0) {
      *(undefined4 *)(this + 0x174) = *(undefined4 *)(adjustedNewNode + 4); // copy back pointer (prev?) to +0x174
      *(int **)(adjustedNewNode + 4) = linkField; // link node's prev pointer back to linkField
    }
  }
}