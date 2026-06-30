// FUNC_NAME: LinkedListNode::removeFromBothLists
void __fastcall LinkedListNode::removeFromBothLists(undefined4 *this)
{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  // Remove from first linked list (offset +0x14 = next, +0x18 = prev)
  piVar1 = this + 5; // +0x14
  iVar2 = *piVar1;
  if (iVar2 != 0) {
    piVar3 = *(int **)(iVar2 + 4); // prev pointer of head
    if (piVar3 == piVar1) {
      *(undefined4 *)(iVar2 + 4) = this[6]; // +0x18
    }
    else {
      piVar4 = (int *)piVar3[1];
      while (piVar4 != piVar1) {
        piVar3 = (int *)piVar3[1];
        piVar4 = (int *)piVar3[1];
      }
      piVar3[1] = this[6]; // +0x18
    }
  }
  
  // Remove from second linked list (offset +0x0C = next, +0x10 = prev)
  iVar2 = this[3]; // +0x0C
  if (iVar2 != 0) {
    puVar5 = *(undefined4 **)(iVar2 + 4); // prev pointer of head
    if (puVar5 == this + 3) {
      *(undefined4 *)(iVar2 + 4) = this[4]; // +0x10
      *this = &PTR_LAB_00e3729c; // vtable pointer
      return;
    }
    puVar6 = (undefined4 *)puVar5[1];
    while (puVar6 != this + 3) {
      puVar5 = (undefined4 *)puVar5[1];
      puVar6 = (undefined4 *)puVar5[1];
    }
    puVar5[1] = this[4]; // +0x10
  }
  
  *this = &PTR_LAB_00e3729c; // vtable pointer
  return;
}