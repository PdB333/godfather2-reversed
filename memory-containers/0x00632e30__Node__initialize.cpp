// FUNC_NAME: Node::initialize
void Node::initialize(void *vtable1, void *vtable2)
{
  // Set vtable pointers for object virtualization
  *(void **)(this + 0x08) = vtable1;  // +0x08: primary vtable pointer
  *(void **)(this + 0x04) = vtable2;  // +0x04: secondary vtable pointer
  
  // Set initial node IDs to invalid (-1)
  *(int *)(this + 0x14) = -1;  // +0x14: nodeId or parentId (invalid)
  *(int *)(this + 0x1c) = -1;  // +0x1c: siblingId or index (invalid)
  
  // Set data pointer and name
  *(void **)(this + 0x0c) = &DAT_00e41ec0;  // +0x0c: pointer to node data
  *(char **)(this + 0x10) = "=(tail call)";  // +0x10: node name/label
  
  // Initialize child list (calling string constructor)
  FUN_00636c20(this + 0x20, "=(tail call)");  // +0x20: child list / string member
  
  // Set flags to 0
  *(int *)(this + 0x18) = 0;  // +0x18: flags or state
  
  // Clear first pointer in the object referenced by param_1+8
  **(int **)(param_1 + 8) = 0;
}