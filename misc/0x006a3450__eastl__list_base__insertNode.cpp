// FUNC_NAME: eastl::list_base::insertNode
void __thiscall eastl::list_base::insertNode(int thisPtr, int* data) 
{
  int *newNode;
  int i;
  int *dest;
  
  // Allocate a new node (0x45c = 1116 bytes) using EASTL allocator
  newNode = (int *)FUN_0068ab90(0x45c,"EASTL",0,0,
                               "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h",0xe9
                              );
  // Check allocation succeeded (null check via pointer arithmetic)
  if (newNode + 2 != (int *)0x0) {
    // Copy 0x115 (277) integer elements from source to node data area (offset +8)
    dest = newNode + 2;
    for (i = 0x115; i != 0; i = i + -1) {
      *dest = *data;
      data = data + 1;
      dest = dest + 1;
    }
  }
  // Node structure: +0 = prev, +4 = next, +8.. = data[0x115]
  // Insert at front of list (after sentinel head)
  *newNode = thisPtr;                         // newNode->prev = head
  newNode[1] = *(int *)(thisPtr + 4);         // newNode->next = head->next
  **(int **)(thisPtr + 4) = (int)newNode;     // head->next->prev = newNode
  *(int **)(thisPtr + 4) = newNode;           // head->next = newNode
  return;
}