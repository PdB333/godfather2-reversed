// FUNC_NAME: NodeList::moveNodeToList
void __fastcall NodeList::moveNodeToList(undefined4 this, int param_2)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  int unaff_ESI;
  
  if (param_2 != 0) {
    *(char *)(param_2 + 9) = *(char *)(param_2 + 9) + '\x01'; // increment refCount at +0x09
  }
  piVar1 = *(int **)(unaff_ESI + 0x3c); // current list head at +0x3C
  if (piVar1 != (int *)0x0) {
    *(char *)((int)piVar1 + 9) = *(char *)((int)piVar1 + 9) + -1; // decrement refCount of old head
    if (((char)piVar1[2] == '\0') && (*(char *)((int)piVar1 + 9) == '\0')) { // check flags at +0x08 and refCount
      iVar2 = *piVar1; // next pointer at +0x00
      piVar1 = (int *)piVar1[1]; // prev pointer at +0x04
      if (iVar2 != 0) {
        *(int **)(iVar2 + 4) = piVar1; // fix next->prev
      }
      iVar3 = DAT_01205588; // global free list head
      if (piVar1 != (int *)0x0) {
        *piVar1 = iVar2; // fix prev->next
        *(int *)(unaff_ESI + 0x3c) = param_2; // set new head
        return;
      }
      *(undefined4 *)(DAT_01205588 + 8) = *(undefined4 *)(DAT_01205588 + 4); // update free list tail
      *(int *)(iVar3 + 4) = iVar2; // update free list head
      if (iVar2 == 0) {
        *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(iVar3 + 0xc); // update free list tail if empty
      }
    }
  }
  *(int *)(unaff_ESI + 0x3c) = param_2; // set new head
  return;
}