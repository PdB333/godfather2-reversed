// FUNC_NAME: EARSList::pushBack
void __thiscall EARSList::pushBack(int *this, int *node)
{
  int *piVar1;
  int iVar2;
  
  iVar2 = this[2]; // +0x08 capacity
  if (this[1] == iVar2) { // +0x04 size == capacity
    if (iVar2 == 0) {
      iVar2 = 1;
    }
    else {
      iVar2 = iVar2 * 2;
    }
    FUN_00827340(iVar2); // reallocate/resize internal array
  }
  piVar1 = (int *)(*this + this[1] * 8); // +0x00 data array, +0x04 size
  this[1] = this[1] + 1; // increment size
  if (piVar1 != (int *)0x0) {
    iVar2 = *param_2; // node's value
    *piVar1 = iVar2; // store value
    piVar1[1] = 0; // clear next pointer
    if (iVar2 != 0) {
      piVar1[1] = *(int *)(iVar2 + 4); // link to existing list
      *(int **)(iVar2 + 4) = piVar1;
    }
  }
  return;
}