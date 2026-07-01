// FUNC_NAME: DoublyLinkedList::unlinkNode
void __thiscall DoublyLinkedList::unlinkNode(int *list, int *node)
{
  int iVar1;
  undefined4 *puVar2;
  
  if ((int *)node[1] == (int *)0x0) {
    iVar1 = *node;
    *list = iVar1;
    if (iVar1 == 0) goto LAB_0093e486;
    *(undefined4 *)(iVar1 + 4) = 0;
  }
  else {
    *(int *)node[1] = *node;
  }
  if (*node != 0) {
    *(int *)(*node + 4) = node[1];
    node[1] = 0;
    *node = 0;
    return;
  }
LAB_0093e486:
  puVar2 = (undefined4 *)node[1];
  list[1] = (int)puVar2;
  if (puVar2 != (undefined4 *)0x0) {
    *puVar2 = 0;
  }
  node[1] = 0;
  *node = 0;
  return;
}