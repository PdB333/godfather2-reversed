// FUNC_NAME: SomeClass::insertSortedNode
void SomeClass::insertSortedNode(uint param_1)
{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int unaff_EDI;
  
  puVar4 = *(undefined4 **)(unaff_EDI + 0x48); // +0x48: head of linked list
  puVar3 = (undefined4 *)(unaff_EDI + 0x48); // +0x48: pointer to head pointer
  while ((puVar2 = puVar4, puVar2 != (undefined4 *)0x0 && (param_1 <= (uint)puVar2[2]))) {
    if (puVar2[2] == param_1) {
      return; // duplicate key, already exists
    }
    puVar3 = puVar2;
    puVar4 = (undefined4 *)*puVar2; // next node
  }
  puVar4 = (undefined4 *)(*DAT_012059dc)(0,0x14); // allocate 20 bytes
  if (puVar4 != (undefined4 *)0x0) {
    if (unaff_EDI != 0) {
      piVar1 = (int *)(*(int *)(unaff_EDI + 0x10) + 0x24); // +0x10: some manager, +0x24: allocation counter
      *piVar1 = *piVar1 + 0x14;
    }
    *(undefined1 *)(puVar4 + 1) = 10; // node type/size field
    *(undefined1 *)((int)puVar4 + 5) = 1; // flags
    puVar4[2] = param_1; // key value
    *puVar4 = *puVar3; // link to next node
    *puVar3 = puVar4; // insert into list
    return;
  }
  if (unaff_EDI != 0) {
    FUN_00635a80(); // allocation failure handler
    return;
  }
  // fallback: use static storage when this is null
  _DAT_00000008 = param_1;
  DAT_00000004 = 10;
  uRam00000005 = 1;
  uRam00000000 = *puVar3;
  *puVar3 = 0;
  return;
}