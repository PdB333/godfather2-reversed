// FUNC_NAME: SomeClass::appendToLinkedList
void __fastcall SomeClass::appendToLinkedList(int this)
{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int local_54;
  undefined1 local_50 [76];
  
  // Check if any of the four linked list head pointers are non-null
  if ((((*(int *)(this + 400) != 0) || (*(int *)(this + 0x194) != 0)) ||
      (*(int *)(this + 0x198) != 0)) || (*(int *)(this + 0x19c) != 0)) {
    // Get some string identifier
    uVar3 = FUN_00471610(); // likely getStringId or similar
    // Format a string into local_50 buffer (76 bytes)
    FUN_0044b4e0(local_50, uVar3); // likely sprintf or string format
    // Allocate or find a node in a linked list
    piVar4 = (int *)FUN_004df330(&local_54, this + 400, local_50, 0x1ff, 0, this, 0xffffffff, 0);
    // Pointer to the "next" field at this+0x1a0
    piVar1 = (int *)(this + 0x1a0);
    // If there's already a node at this+0x1a0, clear its back pointer
    if (*(int *)(this + 0x1a0) != 0) {
      *(undefined4 *)(*(int *)(this + 0x1a0) + 8) = 0;
      *piVar1 = 0;
    }
    // Get the new node from the allocation
    iVar2 = *piVar4;
    *piVar1 = iVar2;
    // If new node exists, set its back pointer to piVar1 and clear the source
    if (iVar2 != 0) {
      *(int **)(iVar2 + 8) = piVar1;
      *piVar4 = 0;
    }
    // If local_54 was allocated, clear its back pointer too
    if (local_54 != 0) {
      *(undefined4 *)(local_54 + 8) = 0;
    }
  }
  return;
}