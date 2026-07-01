// FUNC_NAME: LinkedListNode::constructor
void __fastcall LinkedListNode_constructor(int param_1)
{
  // Call base constructor or initialization function
  FUN_0089ed40();
  
  // Initialize doubly-linked list node: next and prev pointers point to self
  *(int *)param_1 = param_1;      // +0x00: next = this
  *(int *)(param_1 + 4) = param_1; // +0x04: prev = this
  return;
}