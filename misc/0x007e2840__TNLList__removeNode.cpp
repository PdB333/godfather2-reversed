// FUNC_NAME: TNLList::removeNode
void __thiscall TNLList::removeNode(int *this, undefined4 param_2, int *param_3)
{
  int *piVar1;
  int iVar2;
  int *unaff_EBX;
  
  piVar1 = (int *)*param_3; // Get the node to remove
  if (piVar1 == (int *)0x0) {
    iVar2 = 0;
  }
  else {
    iVar2 = piVar1[3]; // node->next
  }
  *param_3 = iVar2; // Update iterator to next node
  if (piVar1 == (int *)*this) { // If node is head
    if (piVar1 == (int *)this[1]) { // If node is also tail (single node)
      this[1] = 0; // Clear tail
      *this = 0; // Clear head
    }
    else {
      iVar2 = piVar1[3]; // node->next
      *this = iVar2; // Update head to next
      if (iVar2 != 0) {
        *(undefined4 *)(iVar2 + 0x10) = 0; // new head->prev = null
      }
    }
  }
  else {
    iVar2 = piVar1[4]; // node->prev
    if (piVar1 == (int *)this[1]) { // If node is tail
      this[1] = iVar2; // Update tail to prev
      *(undefined4 *)(iVar2 + 0xc) = 0; // new tail->next = null
    }
    else {
      *(int *)(iVar2 + 0xc) = piVar1[3]; // prev->next = node->next
      *(int *)(piVar1[3] + 0x10) = piVar1[4]; // next->prev = node->prev
    }
  }
  if (*piVar1 != 0) {
    FUN_004daf90(piVar1); // Free node memory
  }
  (**(code **)(*(int *)this[4] + 4))(piVar1,0); // Call destructor on node
  this[2] = this[2] + -1; // Decrement count
  *unaff_EBX = *param_3; // Update iterator
  return;
}