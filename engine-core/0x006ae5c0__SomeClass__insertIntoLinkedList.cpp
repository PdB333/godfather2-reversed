// FUNC_NAME: SomeClass::insertIntoLinkedList
void __thiscall SomeClass::insertIntoLinkedList(int this, int param_2)
{
  int *piVar2;
  int iVar1;
  
  // Calculate pointer to slot in array at this+0x1ac, indexed by param_2+0x184
  piVar2 = (int *)(this + 0x1ac + *(int *)(param_2 + 0x184) * 8);
  iVar1 = param_2 + 0x48; // Node to insert (param_2+0x48)
  
  if (*piVar2 != iVar1) {
    // If slot is occupied, remove existing node
    if (*piVar2 != 0) {
      FUN_004daf90(piVar2); // Remove node from linked list
    }
    // Insert new node
    *piVar2 = iVar1;
    if (iVar1 != 0) {
      // Set next pointer (piVar2[1]) to current head of list at param_2+0x4c
      piVar2[1] = *(int *)(param_2 + 0x4c);
      // Update head of list to point to new node
      *(int **)(param_2 + 0x4c) = piVar2;
    }
  }
  return;
}