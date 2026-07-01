// FUNC_NAME: SomeClass::moveNodeToList
void __fastcall SomeClass::moveNodeToList(int thisPtr)
{
  int *nodePtr;
  int *listHeadPtr;
  int *resultNode;
  int localTemp;

  nodePtr = (int *)(thisPtr + 0x204);
  if (*(int *)(thisPtr + 0x204) == 0) {
    localTemp = thisPtr;
    resultNode = (int *)FUN_008dc310(&localTemp, thisPtr + 500);
    if (*nodePtr != 0) {
      *(undefined4 *)(*nodePtr + 8) = 0;
      *nodePtr = 0;
    }
    listHeadPtr = *resultNode;
    *nodePtr = listHeadPtr;
    if (listHeadPtr != 0) {
      *(int **)(listHeadPtr + 8) = nodePtr;
      *resultNode = 0;
    }
    if (localTemp != 0) {
      *(undefined4 *)(localTemp + 8) = 0;
    }
  }
  return;
}