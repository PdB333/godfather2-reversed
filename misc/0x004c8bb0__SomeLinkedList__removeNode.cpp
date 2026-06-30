// FUNC_NAME: SomeLinkedList::removeNode
void SomeLinkedList::removeNode(void)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int this; // unaff_ESI
  bool bVar4;
  
  iVar3 = DAT_012054a4; // head of linked list
  bVar4 = DAT_012054a4 != 0;
  *(undefined1 *)(this + 0x1c) = 1; // mark node as removed? +0x1c
  if (bVar4) {
    if (iVar3 == this) {
      DAT_012054a4 = 0; // list becomes empty
LAB_004c8be9:
      if (*(int *)(this + 0x14) != 0) { // +0x14 some flag/resource
        *(undefined4 *)(this + 0x14) = 0;
        FUN_005e5080(); // cleanup/release function
        return;
      }
    }
    else {
      iVar1 = *(int *)(iVar3 + 8); // +0x08 next pointer
      while (iVar1 != 0) {
        iVar2 = *(int *)(iVar3 + 8);
        if (iVar2 == this) {
          *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(iVar2 + 8); // unlink from list
          goto LAB_004c8be9;
        }
        iVar3 = iVar2;
        iVar1 = *(int *)(iVar2 + 8);
      }
    }
  }
  return;
}