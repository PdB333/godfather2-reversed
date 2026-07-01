// FUNC_NAME: SomeListClass::removeNode
void __fastcall SomeListClass::removeNode(int this)
{
  int *nodePtr;
  int *prevNodePtr;
  int *nextNodePtr;
  int local_this;

  nodePtr = (int *)(this + 0x1dc);
  if (*(int *)(this + 0x1dc) == 0) {
    local_this = this;
    nextNodePtr = (int *)FUN_008dc310(&local_this, this + 0x1cc);
    if (*nodePtr != 0) {
      *(undefined4 *)(*nodePtr + 8) = 0;
      *nodePtr = 0;
    }
    prevNodePtr = *nextNodePtr;
    *nodePtr = prevNodePtr;
    if (prevNodePtr != 0) {
      *(int **)(prevNodePtr + 8) = nodePtr;
      *nextNodePtr = 0;
    }
    if (local_this != 0) {
      *(undefined4 *)(local_this + 8) = 0;
    }
  }
  return;
}