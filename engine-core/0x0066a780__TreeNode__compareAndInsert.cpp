// FUNC_NAME: TreeNode::compareAndInsert
void TreeNode::compareAndInsert(TreeNode *param_1, TreeNode *param_2)
{
  int newKey;
  int conditionResult;
  
  newKey = param_1->key; // +0x08: key value of new node
  if (newKey != param_2->key) {
    // Keys differ: store the new key into this node (usually the parent or root)
    this->key = newKey;
    // Perform a left/right rotation or reattach operation between the two nodes
    FUN_0066bb40(param_1, param_2);
    return;
  }
  // Keys equal: check some condition (e.g., color of parent or sibling)
  conditionResult = FUN_00665c30(); // returns -1 if neutral, else branch ID
  if (conditionResult != -1) {
    // Condition satisfied: store the new key and fixup with param_1
    this->key = newKey;
    FUN_0066c8d0(param_1);
    return;
  }
  // Condition not satisfied: store a boolean based on whether newKey is zero
  this->key = (uint)(newKey == 0);
  // Fixup with the other node (param_2)
  FUN_0066c8d0(param_2);
  return;
}