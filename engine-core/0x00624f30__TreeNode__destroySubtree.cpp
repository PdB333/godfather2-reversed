// FUNC_NAME: TreeNode::destroySubtree
void __thiscall TreeNode::destroySubtree(TreeNode *this, TreeNode *node)
{
  TreeNode *nextChild;
  TreeNode *child;
  
  if (node != (TreeNode *)0x0) {
    child = *(TreeNode **)(node + 0x20); // +0x20: first child pointer
    while (child != (TreeNode *)0x0) {
      nextChild = *(TreeNode **)(child + 0x28); // +0x28: sibling pointer
      TreeNode::destroySubtree(this, child);
      child = nextChild;
    }
    if (node == *(TreeNode **)(this + 4)) { // +0x04: root node pointer
      *(undefined4 *)(this + 4) = 0;
    }
    else if (*(TreeNode **)(node + 0x1c) != (TreeNode *)0x0) { // +0x1c: parent pointer
      (**(code **)(*(int *)node->parent + 0x1c))(node); // vtable call to detach child
    }
    if ((*(byte *)(node + 0x14) & 1) != 0) { // +0x14: flags byte
      node->flags = node->flags | 2; // mark for deferred deletion
      return;
    }
    (**(code **)(*node + 4))(1); // vtable call to delete node (size=1)
  }
  return;
}