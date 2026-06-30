// FUNC_NAME: RedBlackTree::fixupAfterDelete (internal helper)
void __fastcall RedBlackTree::fixupAfterDelete(int *context)
{
  // context[0] is likely the root pointer or a sentinel. If null, assert.
  // context[1] is the current node being processed (like a "fixup node").
  // Nodes have a color flag at offset +0x25 (0=black, non-zero=red).
  // Node structure presumably:
  //   +0x00: left child pointer (or something else?)
  //   +0x04: right child pointer?
  //   +0x08: parent pointer? or maybe another child?
  //   +0x0C-0x24: other data
  //   +0x25: color (byte)
  // This code is a standard red-black tree deletion fixup loop,
  // adjusting pointers and maintaining color invariants.

  int *currentNode;

  if (*context == 0) {
    assertFailed(); // debug assertion (FUN_00b97aea)
  }

  currentNode = (int *)context[1];

  if (*(char *)((int)currentNode + 0x25) == '\0') {
    // Current node is black. Need to find a red node in the left subtree.
    int *leftChild = (int *)*currentNode;

    if (leftChild != 0 && *(char *)((int)leftChild + 0x25) == '\0') {
      // Left child is also black. Go to its right child.
      int *tempNode = (int *)*(int *)((int)leftChild + 8);
      while (tempNode != 0 && *(char *)((int)tempNode + 0x25) == '\0') {
        leftChild = tempNode;
        tempNode = (int *)*(int *)((int)tempNode + 8);
      }
      context[1] = (int)leftChild;
      return;
    }

    // Left child does not exist or is red; move up in the tree.
    int *parent = (int *)currentNode[1];
    while (*(char *)((int)parent + 0x25) == '\0' && context[1] == *currentNode) {
      context[1] = (int)currentNode;
      currentNode = parent;
      parent = (int *)currentNode[1];
      if (parent == 0) break;
    }

    // After climbing, if the new current node is red (non-zero), we are done.
    if (*(char *)(context[1] + 0x25) != '\0') {
      assertFailed(); // Should not happen if tree is correct? (debug)
      return;
    }
    context[1] = (int)parent;
  }
  else {
    // Current node is red. Move to its parent (which should be black).
    int *parent = (int *)currentNode[2];
    context[1] = (int)parent;
    // Parent must not be red (property violation if so)
    if (parent != 0 && *(char *)((int)parent + 0x25) != '\0') {
      assertFailed();
      return;
    }
  }
}