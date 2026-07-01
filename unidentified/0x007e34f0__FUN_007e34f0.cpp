// FUNC_NAME: SomeObject::removeFromActiveList
void __thiscall SomeObject::removeFromActiveList(void) {
  int* pPrevField; // pointer to offset 0x48 (prev pointer)
  int local_4; // unused, possibly next pointer value
  int* ptrToField; // will hold address of pPrevField

  // Guard: this must be valid
  if (this == 0) {
    return;
  }

  // Check global state – possibly system not shutting down
  if (isSystemReady() != 0) {
    return;
  }

  // pPrevField = pointer to the "prev" link field at +0x48
  pPrevField = (int*)((int)this + 0x48); // +0x48: pointer to previous node in list
  local_4 = 0;

  // pPrevField is guaranteed non-null as long as this is valid
  if (pPrevField != 0) {
    // Save current "next" pointer (at +0x4c) – not used further
    local_4 = *(int*)((int)this + 0x4c); // +0x4c: pointer to next node in list

    // Replace next pointer with address of the local pPrevField variable
    // This creates an indirect reference for the unlink routines
    *(int**)((int)this + 0x4c) = &pPrevField;
  }

  // Unlink: the first helper function uses the address of the prev field
  // to fix pointers and detach this node from the list
  linkedListUnlink(&pPrevField);

  // If the prev field was not cleared by the unlink, do additional cleanup
  if (pPrevField != 0) {
    linkedListCleanup(&pPrevField);
  }
}