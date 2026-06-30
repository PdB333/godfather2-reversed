// FUNC_NAME: SomeListNode::deallocateList
void __fastcall SomeListNode::deallocateList(SomeListNode *this)
{
  int iVar1;
  SomeListNode *psVar2;
  SomeListNode *psVar3;
  
  this->vtable = &PTR_FUN_00e36c80;
  this->field_0x3c = &PTR_LAB_00e36ca0;
  this->field_0x48 = &PTR_LAB_00e36cb0;
  SomeListNode::constructor(this + 0x50); // +0x14 * 4 = 0x50
  SomeListNode::destructor(this + 0x50);
  SomeListNode::constructor(this + 0x58); // +0x16 * 4 = 0x58
  SomeListNode::destructor(this + 0x58);
  iVar1 = this[0x20]; // +0x80
  if (iVar1 != 0) {
    psVar2 = *(SomeListNode **)(iVar1 + 4);
    if (psVar2 == this + 0x20) { // +0x80
      *(int *)(iVar1 + 4) = this[0x21]; // +0x84
      FUN_0046c640();
      return;
    }
    psVar3 = (SomeListNode *)psVar2[1]; // +0x04
    while (psVar3 != this + 0x20) {
      psVar2 = (SomeListNode *)psVar2[1]; // +0x04
      psVar3 = (SomeListNode *)psVar2[1]; // +0x04
    }
    psVar2[1] = this[0x21]; // +0x84
  }
  FUN_0046c640();
  return;
}