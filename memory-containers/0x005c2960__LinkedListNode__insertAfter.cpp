// FUNC_NAME: LinkedListNode::insertAfter
void LinkedListNode::insertAfter(void)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int *this;
  
  iVar3 = FUN_005c4410(0x14,0);
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  else {
    *(undefined4 *)(iVar3 + 0xc) = 0;
    *(undefined4 *)(iVar3 + 0x10) = 0;
  }
  iVar1 = this[1]; // +0x04: head pointer
  if (iVar1 == 0) {
    this[1] = iVar3; // head = newNode
    *this = iVar3;   // tail = newNode
    return;
  }
  iVar2 = *(int *)(iVar1 + 0xc); // head->prev
  if (iVar2 != 0) {
    *(int *)(iVar2 + 0x10) = iVar3; // prev->next = newNode
    *(int *)(iVar3 + 0xc) = iVar2;  // newNode->prev = prev
  }
  *(int *)(iVar3 + 0x10) = iVar1;  // newNode->next = head
  *(int *)(iVar1 + 0xc) = iVar3;   // head->prev = newNode
  if (this[1] == *this) {          // head == tail (single element)
    *this = iVar3;                 // tail = newNode
  }
  return;
}