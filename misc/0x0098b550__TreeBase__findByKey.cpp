// FUNC_NAME: TreeBase::findByKey
void TreeBase::findByKey(Node *this, Node **outResult, const uint *key)
{
  Node *sentinel = (Node *)((char *)this + 4);
  Node *lastRightNode = sentinel;
  Node *currentNode;

  if (*(Node **)((char *)this + 0xc) != (Node *)0x0) {
    currentNode = *(Node **)((char *)this + 0xc);
    do {
      if (currentNode->key < *key) {
        // If current node key is less than search key, go to left child (larger keys)
        currentNode = (Node *)currentNode->left;
      }
      else {
        // If current node key is >= search key, go to right child (smaller keys)
        currentNode = (Node *)currentNode->right;
        lastRightNode = currentNode;
      }
    } while (currentNode != (Node *)0x0);
  }

  if ((lastRightNode != sentinel) && (lastRightNode->key <= *key)) {
    *outResult = lastRightNode;
    return;
  }

  *outResult = sentinel;
  return;
}