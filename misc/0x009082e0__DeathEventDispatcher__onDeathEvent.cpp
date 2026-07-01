// FUNC_NAME: DeathEventDispatcher::onDeathEvent
void __thiscall DeathEventDispatcher::onDeathEvent(int eventData)
{
  bool bFlag;
  int iVar2;
  int *piVar3;
  char *sourceString;
  float *pFloatArray;
  undefined8 uVar5;
  char formattedString[16];
  char nameBuffer[16];

  // Compare event type with this object's expected type
  if (*(int *)(eventData + 8) == this->expectedEventType) {
    bFlag = false;

    // Check global state: see if game is active and player data is valid
    if ((((*(int *)(g_gameManager + 0x40) != 0) &&
          (*(int *)(*(int *)(g_gameManager + 0x40) + 0x60) != 0)) &&
         (iVar2 = **(int **)(g_playerData + 4), iVar2 != 0)) && (iVar2 != 0x1f30)) {

      // Determine which player ID slot to use
      if ((*(int *)(eventData + 0x14) == -1) || (*(int *)(iVar2 + -0x38) != *(int *)(eventData + 0x14))) {
        if (*(int *)(eventData + 0x10) == -1) {
          return;
        }
        if (*(int *)(iVar2 + -0x38) != *(int *)(eventData + 0x10)) {
          return;
        }
        bFlag = true; // Use killer ID
      }

      // Lock/sync (unknown purpose)
      FUN_00471610();

      // Get packed event identifier (three 16-bit floats + 12-bit subcode)
      uVar5 = FUN_00907fb0(eventData, *(undefined4 *)(iVar2 + -0x3c));
      pFloatArray = (float *)((ulonglong)uVar5 >> 0x20);

      // Format: four hex groups (e.g., "AB12CD34EF56G78")
      __snprintf(formattedString, 0x10, "%04X%04X%04X%03X",
                 (int)*pFloatArray & 0xffff,
                 (int)pFloatArray[1] & 0xffff,
                 (int)pFloatArray[2] & 0xffff,
                 (uint)uVar5 & 0xfff);
      formattedString[15] = 0; // null terminate

      // Send the event message (likely to other players or UI)
      // Message type: 'MPGP' (maybe "GamePlay Message"?)
      // Subtype depends on bFlag: 'DIED' (victim) or 'KILL' (killer)
      (*(code **)(*g_messageSystem + 0x14))(0x4d504750,
                                            ((-(uint)bFlag & 0x7000708) + 0x44494544),
                                            formattedString);

      // If we used the killer ID (bFlag true) and the player exists and is alive
      if ((bFlag) && (iVar2 = FUN_004baf60(*(undefined4 *)(eventData + 0x14)), iVar2 != 0) &&
          ((*(byte *)(iVar2 + 0x30) & 1) != 0)) {

        // Get player name from internal structure
        piVar3 = (int *)FUN_004bb600(iVar2);
        sourceString = (char *)*piVar3;
        if (sourceString == (char *)0x0) {
          sourceString = &defaultName; // e.g., "Unknown"
        }

        // Copy name into buffer (max 15 chars)
        _strncpy(nameBuffer, sourceString, 0x10);
        nameBuffer[15] = 0;

        // Send player name message
        (**(code **)(*g_messageSystem + 0x14))(0x4d504750, 0x4b4c4944, nameBuffer);
      }
    }
  }
  return;
}