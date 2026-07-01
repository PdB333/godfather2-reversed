// FUNC_NAME: SomeClass::appendToLinkedList
void __fastcall SomeClass::appendToLinkedList(int *this)
{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int iStack_54;
  undefined1 local_50 [76];

  // Check if any of the four fields at offsets 0x78-0x7b are non-zero
  // and the field at offset 0x80 is zero
  if (((((this[0x78] != 0) || (this[0x79] != 0)) || (this[0x7a] != 0)) ||
      (this[0x7b] != 0)) && (piVar1 = this + 0x80, this[0x80] == 0)) {
    uVar3 = FUN_00471610(); // Get some value
    FUN_0044b4e0(local_50, uVar3); // Convert to string or buffer
    uVar3 = (**(code **)(*this + 0x58))(0, this, 0xffffffff, 0); // Virtual call at vtable+0x58
    piVar4 = (int *)FUN_004df330(&iStack_54, this + 0x78, local_50, uVar3); // Allocate or find node
    if (*piVar1 != 0) {
      *(undefined4 *)(*piVar1 + 8) = 0; // Clear next pointer of existing head
      *piVar1 = 0;
    }
    iVar2 = *piVar4;
    *piVar1 = iVar2; // Set head to new node
    if (iVar2 != 0) {
      *(int **)(iVar2 + 8) = piVar1; // Set new node's prev pointer
      *piVar4 = 0; // Clear the source
    }
    if (iStack_54 != 0) {
      *(undefined4 *)(iStack_54 + 8) = 0; // Clear next pointer of tail
    }
  }
  return;
}