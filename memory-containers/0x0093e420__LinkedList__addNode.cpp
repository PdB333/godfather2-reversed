// FUNC_NAME: LinkedList::addNode
void __thiscall LinkedList::addNode(undefined4 *this, undefined4 *node)
{
  *node = 0; // node->next = NULL
  node[1] = this[1]; // node->prev = this->tail
  if ((undefined4 *)this[1] != (undefined4 *)0x0) { // if tail exists
    *(undefined4 *)this[1] = node; // tail->next = node
    this[1] = node; // this->tail = node
    return;
  }
  *this = node; // this->head = node
  this[1] = node; // this->tail = node
  return;
}