// FUNC_NAME: SomeList::removeNode
void __fastcall SomeList::removeNode(int this, int node)
{
  int currentIndex = *(int *)(this + 0x200) - 1; // current count - 1
  *(int *)(this + 0x200) = currentIndex;
  
  if (*(int *)(node + 0x2c) != currentIndex) {
    // Swap the node to remove with the last node in the list
    int lastNode = *(int *)(*(int *)(this + 0x1fc) + currentIndex * 4);
    *(int *)(lastNode + 0x2c) = *(int *)(node + 0x2c);
    
    *(int *)(*(int *)(this + 0x1fc) + *(int *)(node + 0x2c) * 4) = 
         *(int *)(*(int *)(this + 0x1fc) + currentIndex * 4);
    
    *(int *)(*(int *)(this + 0x1fc) + currentIndex * 4) = node;
    *(int *)(node + 0x2c) = currentIndex;
  }
}