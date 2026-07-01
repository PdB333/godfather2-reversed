// FUNC_NAME: EARSLinkedListNode::constructor
void __fastcall EARSLinkedListNode::constructor(EARSLinkedListNode *this)

{
  FUN_0089ebc0();  // Base constructor call
  this->next = this;  // +0x00: pointer to next node
  this->prev = this;  // +0x04: pointer to previous node
  return;
}