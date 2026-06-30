// FUNC_NAME: RBTreeIterator::increment
void __thiscall RBTreeIterator::increment(void)
{
  // this[0] = root (Node*)
  // this[4] = current (Node*)
  // Node offsets: left (0x00), parent (0x04), right (0x08), color (0x15)
  // color: 0 = red, non-zero = black

  Node* root = *(Node**)this;
  Node* current = *(Node**)((int)this + 4);

  if (root == nullptr) {
    // assertion or debug break
    FUN_00b97aea();
  }

  Node* node = current;
  if (*(char*)((int)node + 0x15) == '\0') {
    // current node is red
    Node* leftChild = (Node*)node->left; // +0x00
    if (*(char*)((int)leftChild + 0x15) == '\0') {
      // left child is also red: descend the right chain of the left subtree
      Node* cur = leftChild;
      Node* next = (Node*)cur->right; // +0x08
      while (*(char*)((int)next + 0x15) == '\0') {
        cur = next;
        next = (Node*)cur->right; // +0x08
      }
      *(Node**)((int)this + 4) = cur;
      return;
    }
    // left child is black: ascend the parent chain
    node = (Node*)node->parent; // +0x04
    while (*(char*)((int)node + 0x15) == '\0' && *(Node**)((int)this + 4) == (Node*)node->left) {
      *(Node**)((int)this + 4) = node;
      node = (Node*)node->parent; // +0x04
    }
    if (*(char*)(*(int*)((int)this + 4) + 0x15) != '\0') {
      // inconsistency, abort
      FUN_00b97aea();
      return;
    }
    *(Node**)((int)this + 4) = node;
  }
  else {
    // current node is black: go to right child
    Node* rightChild = (Node*)node->right; // +0x08
    *(Node**)((int)this + 4) = rightChild;
    if (rightChild != nullptr && *(char*)((int)rightChild + 0x15) != '\0') {
      // right child exists and is black – unexpected
      FUN_00b97aea();
      return;
    }
  }
}