// FUNC_NAME: TNLHandleContainer::reserve (or similar EA EARS container growth function, address 0x00750050)
// Reconstructed: This function ensures the internal array of 12-byte nodes can hold at least 'capacity' elements.
// Nodes are intrusive: each object pointed to by a node stores a back-pointer to its node at offset +4.
// When reallocating, the old nodes are copied, back-pointers are updated, and old nodes are destructed via FUN_004daf90.

void __thiscall TNLHandleContainer::reserve(int *this, uint capacity)
{
  int *newNodes;
  int *oldNode;
  int *newNode;
  int nodeCount;
  uint idx;

  if ((uint)this[2] < capacity) {
    // Allocate new node array: capacity * 12 bytes per node
    newNodes = (int *)operator new[](capacity * 0xc);

    if (*this != 0) {
      idx = 0;
      if (this[1] != 0) {
        nodeCount = 0;
        newNode = newNodes;
        do {
          oldNode = (int *)(*this + idx);
          // Copy node data
          *newNode = *oldNode;                           // object pointer
          newNode[1] = 0;                                // clear back-pointer (temp)
          if (*oldNode != 0) {
            // Update back-pointer from object to new node
            newNode[1] = *(int *)(*oldNode + 4);         // object->prevNode (saved)
            *(int **)(*oldNode + 4) = newNode;           // object->prevNode = newNode
          }
          newNode[2] = oldNode[2];                       // copy extra data (e.g., flags/refcount)
          // Destroy old node (decrease refcount, etc.)
          if (*oldNode != 0) {
            FUN_004daf90(oldNode);
          }
          idx += 0xc;
          nodeCount += 1;
          newNode += 3;                                  // advance by 3 ints (12 bytes)
        } while (nodeCount < this[1]);
      }
      // Free old array
      operator delete[](*this);
    }
    *this = (int)newNodes;
    this[2] = capacity;
  }
}