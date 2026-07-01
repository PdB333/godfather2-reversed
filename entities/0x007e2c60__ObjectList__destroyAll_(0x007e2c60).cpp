// FUNC_NAME: ObjectList::destroyAll (0x007e2c60)
void __fastcall ObjectList::destroyAll(ObjectList *this)
{
  // this points to a structure with:
  // +0x00: head pointer (linked list of nodes)
  // +0x0C: tail pointer or secondary list
  // +0x10: allocator object with vtable
  int *currentNode;
  int *nextNode;

  currentNode = *reinterpret_cast<int **>(this); // head of list

  while (currentNode != nullptr)
  {
    nextNode = reinterpret_cast<int *>(currentNode[3]); // +0x0C: next pointer

    if (*currentNode != 0) // check if node is valid (e.g., has resource)
    {
      freeNode(currentNode); // FUN_004daf90 - likely custom free or release
    }

    // Call virtual function at vtable+4 on allocator (release/destroy for node)
    // Allocator vtable: +0x00: ?, +0x04: release(void*, int), +0x0C: flush()
    void *allocator = reinterpret_cast<void *>(this[4]); // +0x10
    void **vtable = *reinterpret_cast<void ***>(allocator);
    typedef void (*ReleaseFunc)(void *, void *, int); // thiscall? Actually fastcall? But we call via code pointer.
    ReleaseFunc release = reinterpret_cast<ReleaseFunc>(vtable[1]); // index 1 corresponds to offset 4
    release(allocator, currentNode, 0); // second parameter is 0 (maybe flags)

    currentNode = nextNode;
  }

  // Handle secondary pointer (tail or extra list)
  void *secondary = reinterpret_cast<void *>(this[3]); // +0x0C
  if (secondary != nullptr)
  {
    void *allocator = reinterpret_cast<void *>(this[4]);
    void **vtable = *reinterpret_cast<void ***>(allocator);
    typedef void (*ReleaseFunc)(void *, void *, int);
    ReleaseFunc release = reinterpret_cast<ReleaseFunc>(vtable[1]);
    release(allocator, secondary, 0);
  }

  // Flush allocator (virtual function at vtable+0x0C)
  void *allocator = reinterpret_cast<void *>(this[4]);
  void **vtable = *reinterpret_cast<void ***>(allocator);
  typedef void (*FlushFunc)(void *);
  FlushFunc flush = reinterpret_cast<FlushFunc>(vtable[3]); // index 3 = offset 0x0C
  flush(allocator);
}