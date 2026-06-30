// FUNC_NAME: AvatarLinkedNodeList::freeNodeList
void __thiscall freeNodeList(int this)
{
  int nodePool;
  int newNode;
  
  nodePool = *(int *)(this + 0x18);
  newNode = FUN_005f9cc0(nodePool, *(undefined4 *)(nodePool + 4), in_EAX); // alloc node from pool
  FUN_005f9d10(); // probably node destructor or end-of-list marker
  *(int *)(nodePool + 4) = newNode; // update pool tail pointer
  **(int **)(newNode + 4) = newNode; // make the sentinel point to itself (empty list)
}