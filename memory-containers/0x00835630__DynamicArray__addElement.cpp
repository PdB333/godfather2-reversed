// FUNC_NAME: DynamicArray::addElement
int __thiscall DynamicArray::addElement(int this, undefined4 *param_2)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = FUN_009c8e50(0x4c); // allocate memory for element (size 0x4c)
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_00827630(); // construct element
  }
  *(undefined4 *)(iVar2 + 0x24) = *param_2; // copy data to element +0x24
  *(undefined4 *)(iVar2 + 0x28) = param_2[1]; // +0x28
  *(undefined4 *)(iVar2 + 0x2c) = param_2[2]; // +0x2c
  *(undefined4 *)(iVar2 + 0x30) = param_2[3]; // +0x30
  iVar3 = *(int *)(this + 0x1c); // capacity (this+0x1c)
  if (*(int *)(this + 0x18) == iVar3) { // if count == capacity
    if (iVar3 == 0) {
      iVar3 = 1;
    }
    else {
      iVar3 = iVar3 * 2; // double capacity
    }
    FUN_00834ec0(iVar3); // resize array
  }
  piVar1 = (int *)(*(int *)(this + 0x14) + *(int *)(this + 0x18) * 4); // pointer to element slot
  *(int *)(this + 0x18) = *(int *)(this + 0x18) + 1; // increment count
  if (piVar1 != (int *)0x0) {
    *piVar1 = iVar2; // store element pointer
  }
  if (*(int *)(this + 0x18) == 1) { // if first element
    *(undefined4 *)(this + 0x34) = 0; // reset iterator state
    *(undefined4 *)(this + 0x30) = 0;
    FUN_00834960(iVar2,0,0); // initialize element
  }
  return iVar2;
}