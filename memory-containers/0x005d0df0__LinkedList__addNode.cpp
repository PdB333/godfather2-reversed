// FUNC_NAME: LinkedList::addNode
void FUN_005d0df0(void)
{
  int iVar1;   // current node pointer
  int iVar2;   // previous node pointer
  int iVar3;   // new node pointer
  int *unaff_EDI; // linked list head pointer (this)
  
  // Allocate node of size 0x98, using custom allocator
  iVar3 = FUN_005c4410(0x98, 0);
  if (iVar3 == 0) {
    // Allocation failed
    iVar3 = 0;
  }
  else {
    // Initialize node through constructor/init function
    FUN_005d04e0();
    // Initialize forward and backward pointers of the new node
    *(undefined4 *)(iVar3 + 0x90) = 0; // next pointer
    *(undefined4 *)(iVar3 + 0x94) = 0; // prev pointer
  }
  
  // Check if list is empty (first node)
  iVar1 = unaff_EDI[1];
  if (iVar1 == 0) {
    // List is empty, set head and tail to new node
    unaff_EDI[1] = iVar3; // tail = new node
    *unaff_EDI = iVar3;   // head = new node
    return;
  }
  
  // Insert new node after current tail
  iVar2 = *(int *)(iVar1 + 0x90); // Get next pointer of tail (+0x90)
  if (iVar2 != 0) {
    // If tail has a next node, adjust that nodes previous pointer
    *(int *)(iVar2 + 0x94) = iVar3; // Set its prev to new node
    *(int *)(iVar3 + 0x90) = iVar2; // Set new node's next to that node
  }
  
  // Link new node between tail and whatever follows
  *(int *)(iVar3 + 0x94) = iVar1; // Set new node's prev to old tail
  *(int *)(iVar1 + 0x90) = iVar3; // Set old tail's next to new node
  
  // Update tail if needed (when list had only one element)
  if (unaff_EDI[1] == *unaff_EDI) {
    *unaff_EDI = iVar3; // Update head (though this seems like it should be updating tail - possibly a bug)
  }
  
  return;
}