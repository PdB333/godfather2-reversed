// FUNC_NAME: SomeContainer::countAllElements
int __fastcall SomeContainer::countAllElements(int this) // 0x008ebfc0
{
  int currentNode;
  int *headNode;
  int count;
  undefined4 *listItem;
  int nodeSize;
  
  currentNode = **(int **)(this + 0x10);
  count = 0;
  while( true ) {
    headNode = *(int **)(this + 0x10);
    if (this == -0xc) {
      FUN_00b97aea(); // likely debug assertion
    }
    if (currentNode == headNode) break;
    if (this == -0xc) {
      FUN_00b97aea(); // debug assertion
    }
    if (currentNode == *(int *)(this + 0x10)) {
      FUN_00b97aea(); // debug assertion (null check maybe)
    }
    nodeSize = 0;
    for (listItem = *(undefined4 **)(currentNode + 0x10); listItem != (undefined4 *)0x0;
        listItem = (undefined4 *)*listItem) {
      nodeSize = nodeSize + 1;
    }
    count = count + nodeSize;
    FUN_008ea1d0(); // likely iterator advance function
  }
  return count;
}