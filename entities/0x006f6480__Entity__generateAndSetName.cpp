// FUNC_NAME: Entity::generateAndSetName

void __thiscall Entity::generateAndSetName(int *this, int *eventData)
{
  int basePtr;
  char *nameBaseStr;
  unsigned short counter;
  int nameId;
  char buffer[64];

  // Parse the event data (e.g., network message or creation trigger)
  parseNameAssignmentEvent(eventData);

  // Check if the event type matches our expected constant (e.g., kEventType_AssignName)
  if (*eventData == DAT_012069c4) {
    // Ensure we are in a state that allows name generation (state at +0xAC == 2)
    // and that the pending name flag is set (+0xB8 bit 0)
    if ((*(int *)(this + 0xac) == 2) && ((*(byte *)(this + 0xb8) & 1) != 0)) {
      // Increment the local counter for generating unique names (+0xB0)
      counter = *(int *)(this + 0xb0) + 1;
      *(int *)(this + 0xb0) = counter;

      // Obtain the base name string from the owning parent or default
      // +0x78: pointer to parent or owning context structure
      if (*(int *)(this + 0x78) == 0) {
        basePtr = 0;
      } else {
        // Parent structure offset: -0x48 from the pointer at +0x78
        basePtr = *(int *)(this + 0x78) - 0x48;
      }
      // +0x88: string pointer relative to parent base
      nameBaseStr = *(char **)(basePtr + 0x88);
      if (nameBaseStr == (char *)0x0) {
        nameBaseStr = &DAT_0120546e;  // Default base name (e.g., "Object_")
      }

      // Generate the unique name: baseName_XX (two digits, zero-padded)
      _sprintf(buffer, "%s_%2.2d", nameBaseStr, counter);

      // Convert the name to a registered hash/ID (likely via a string table)
      nameId = FUN_004dafd0(buffer);
      *(int *)(this + 0x94) = nameId;  // Store the new name ID
      *(int *)(this + 0x90) = nameId;  // Duplicate storage (perhaps for synced/unsynced)

      // Clear the pending name flag (bit 0 at +0xB8)
      *(uint *)(this + 0xb8) = *(uint *)(this + 0xb8) & 0xfffffffe;
    }
    // Finalize or broadcast the name assignment
    FUN_006f1840(DAT_01206800);
  }
  return;
}