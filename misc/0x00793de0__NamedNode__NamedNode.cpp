// FUNC_NAME: NamedNode::NamedNode
undefined4 * __thiscall NamedNode::NamedNode(undefined4 *this, char *name, undefined4 value1, undefined4 value2, undefined4 value3)
{
  // Call base class constructor
  Base::constructor(this);
  
  // Set vtable pointer
  *this = &NamedNode_vtable;
  
  // Copy name string (max 63 characters)
  _strncpy((char *)(this + 8), name, 0x3f);
  
  // Set additional fields (offsets: +0x04, +0x0C, +0x08)
  this[1] = value1;  // +0x04
  this[3] = value2;  // +0x0C (note: index 3 skips index 2)
  this[2] = value3;  // +0x08
  
  // Initialize zeroed fields (offsets +0x10, +0x14, +0x18, +0x1C)
  this[4] = 0;  // +0x10
  this[5] = 0;  // +0x14
  this[6] = 0;  // +0x18
  this[7] = 0;  // +0x1C
  
  // Link into global singly-linked list
  this[0x1C] = g_headNode;  // +0x70: next pointer
  g_headNode = this;
  
  return this;
}