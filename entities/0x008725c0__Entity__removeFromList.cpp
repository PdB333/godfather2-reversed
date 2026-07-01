// FUNC_NAME: Entity::removeFromList
void __fastcall Entity::removeFromList(int thisPtr)
{
  // +0x128: some stored value (unused in this function)
  int local_c = *(int *)(thisPtr + 0x128);
  // +0x12C (300): pointer to a node embedded in another object
  int nodePtr = *(int *)(thisPtr + 300);
  int local_4 = 0;
  int *containerObj;
  if (nodePtr == 0) {
    containerObj = (int *)0x0;
  }
  else {
    // Save the next pointer of the node (offset +4)
    local_4 = *(int *)(nodePtr + 4);
    // Overwrite next pointer with address of local variable (likely a sentinel or debug marker)
    *(int **)(nodePtr + 4) = &nodePtr;
    // The containing object is 0x48 bytes before the node
    containerObj = (int *)(nodePtr - 0x48);
  }
  int local_10 = 0;
  // Call virtual method at vtable+0x10 with a hash (0x37f596aa) – likely "isValid" or "isActive"
  char cVar1 = (*(char (__thiscall **)(int, uint))(*(int *)containerObj + 0x10))(containerObj, 0x37f596aa);
  // If the container is valid and stack condition holds, perform additional cleanup
  if ((cVar1 != '\0') && (&stack0x00000000 != (undefined1 *)0x10)) {
    FUN_0086d370(thisPtr);
  }
  // Delete local_10 if it was allocated (never set in this path, so no-op)
  if (local_10 != 0) {
    FUN_004daf90(&local_10);
  }
  return;
}