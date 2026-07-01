// FUNC_NAME: SomeContainer::addElement
void __thiscall SomeContainer::addElement(int this, undefined4 param_2)
{
  int iVar1;
  int local_14 [3];
  code *local_8;
  undefined4 local_4;
  
  local_14[0] = 0;
  local_14[1] = 0;
  local_14[2] = 0;
  local_8 = (code *)0x0;
  FUN_004d3d90(param_2); // likely some initialization or copy
  iVar1 = *(int *)(this + 0x84); // +0x84: capacity (max elements)
  if (*(int *)(this + 0x80) == iVar1) { // +0x80: current count
    if (iVar1 == 0) {
      iVar1 = 1;
    }
    else {
      iVar1 = iVar1 * 2; // double capacity
    }
    FUN_0098e0f0(iVar1); // resize internal buffer
  }
  iVar1 = *(int *)(this + 0x7c) + *(int *)(this + 0x80) * 0x14; // +0x7c: base pointer to elements, each element 0x14 bytes
  *(int *)(this + 0x80) = *(int *)(this + 0x80) + 1; // increment count
  if (iVar1 != 0) {
    FUN_004d3b50(local_14); // likely construct element
    *(undefined4 *)(iVar1 + 0x10) = local_4; // store element data at offset 0x10 within element
  }
  if (local_14[0] != 0) {
    (*local_8)(local_14[0]); // cleanup callback
  }
  return;
}