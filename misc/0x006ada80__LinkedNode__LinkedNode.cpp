// FUNC_NAME: LinkedNode::LinkedNode
void __thiscall LinkedNode::LinkedNode(LinkedNode *this, void *owner, int value)
{
  // +0x00: vtable pointer
  // +0x04: some value (param3)
  // +0x08: pointer to list anchor (inside owner at offset 0x48)
  // +0x0C: saved old head pointer (for removal)
  // +0x10: counter/flag
  // +0x14: counter/flag
  // +0x18: counter/flag
  // +0x1C: byte flag
  // +0x20: constant
  ListAnchor *anchor;
  
  this->vtable = &PTR_FUN_00d5dbbc; // base vtable
  this->value = value;
  
  // Owner is expected to have a ListAnchor at offset 0x48
  if (owner == NULL) {
    anchor = NULL;
  }
  else {
    anchor = (ListAnchor *)((char *)owner + 0x48);
  }
  
  // Store anchor pointer in node
  this->anchor = anchor;
  
  // Save old head and link this node as new head
  if (anchor != NULL) {
    // anchor->next is at offset +4 (the head pointer)
    this->oldHead = anchor->head;
    anchor->head = &this->anchor; // point to this node's anchor field? Actually sets head to address of field at +0x08
  }
  else {
    this->oldHead = NULL;
  }
  
  // Zero out additional fields
  this->field_10 = 0;
  this->field_14 = 0;
  this->field_18 = 0;
  this->field_1C = 0;
  this->field_20 = DAT_01205228; // global constant
}