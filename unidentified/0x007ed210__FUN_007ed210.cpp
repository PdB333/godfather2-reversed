// FUNC_NAME: SomeContainer::countMatchingElements
int __thiscall SomeContainer::countMatchingElements(int this, int param_2, int *param_3, int *param_4)
{
  int iVar1;
  undefined4 *puVar2;
  char cVar3;
  int iVar4;
  undefined4 *puVar5;
  int local_10;
  int local_8;
  
  iVar1 = *(int *)(this + 0x18); // +0x18: pointer to some internal data structure
  puVar5 = (undefined4 *)**(undefined4 **)(iVar1 + 0x18); // +0x18: pointer to first element in a linked list
  iVar4 = 0;
  local_10 = 0;
  do {
    puVar2 = *(undefined4 **)(*(int *)(this + 0x18) + 0x18);
    if (iVar1 != *(int *)(this + 0x18)) {
      FUN_00b97aea(); // likely an assertion or error handler
    }
    if (puVar5 == puVar2) {
      return local_10;
    }
    if (puVar5 == *(undefined4 **)(iVar1 + 0x18)) {
      FUN_00b97aea(); // assertion
    }
    iVar4 = iVar4 + puVar5[3]; // accumulate some value from element (offset +0x0C)
    if (param_2 == 0) {
LAB_007ed271:
      if (param_3 != (int *)0x0) {
        if (puVar5 == *(undefined4 **)(iVar1 + 0x18)) {
          FUN_00b97aea(); // assertion
        }
        if (*param_3 != puVar5[5]) goto LAB_007ed2dd; // compare with element field at +0x14
      }
      if (param_4 != (int *)0x0) {
        local_8 = (int)(longlong)ROUND(*(float *)(this + 0x20)); // +0x20: some float threshold
        local_8 = iVar4 - local_8;
        if (local_8 < 1) {
          local_8 = 10;
        }
        cVar3 = (**(code **)(*param_4 + 4))(puVar5 + 2, local_8); // call virtual function on param_4 object with element+0x08 and local_8
        if (cVar3 == '\\0') {
          return local_10;
        }
      }
      local_10 = local_10 + 1;
    }
    else {
      if (puVar5 == *(undefined4 **)(iVar1 + 0x18)) {
        FUN_00b97aea(); // assertion
      }
      if (puVar5[7] == param_2) goto LAB_007ed271; // compare element field at +0x1C with param_2
    }
LAB_007ed2dd:
    if (puVar5 == *(undefined4 **)(iVar1 + 0x18)) {
      FUN_00b97aea(); // assertion
    }
    puVar5 = (undefined4 *)*puVar5; // advance to next linked list element
  } while( true );
}