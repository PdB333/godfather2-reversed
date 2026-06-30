// FUNC_NAME: PlayerActionInputHandler::processActionInput
void __thiscall PlayerActionInputHandler::processActionInput(int thisPtr, int playerObj, int actionId, float *analogInput)
{
  uint uVar1;
  int iVar6;
  byte bVar4;
  char cVar5;
  int iVar10;
  undefined4 *puVar7;
  undefined4 uVar2;
  undefined4 uVar9;

  // Global singleton check: g_InputManager (base)
  if (g_InputManager == 0) {
    return;
  }
  // Get pointer to player state from manager +4 (maybe g_InputManager->playerState)
  iVar10 = *(int *)(g_InputManager + 4);
  if (iVar10 == 0) {
    return;
  }
  // Possibly an invalid player state sentinel (0x1f30)
  if (iVar10 == 0x1f30) {
    return;
  }

  // Get player mode (e.g., whether in menu, driving, etc.)
  iVar6 = getPlayerMode();

  // Read a flag from player object at large negative offset (field before object)
  uVar1 = *(uint *)(iVar10 - 0x1650);
  bVar4 = isInputActionActive(0x17a26743, playerObj, actionId);
  bVar4 = (byte)(uVar1 >> 1) & 1 | bVar4;  // Combine with global flag bit

  // Get action configuration from hash 0x776def75 (probably "context_action_config")
  puVar7 = (undefined4 *)getInputActionConfig(0x776def75);
  if (puVar7 != (undefined4 *)0x0) {
    // If player is in an interaction (e.g., using a vehicle, entering cover)
    if (*(char *)(playerObj + 0x1bb) != '\0') {
      *(char *)(thisPtr + 0x10) = 1;   // Set "action active" flag
      *(char *)(thisPtr + 0x11) = 0;   // Reset "press start" flag
      *(char *)(thisPtr + 0x12) = 0;   // Reset "hold start" flag
      *(char *)(thisPtr + 0x13) = 0;   // Reset "toggle" flag
    }

    uVar9 = *puVar7;          // First value: probably "action type"
    uVar2 = puVar7[1];       // Second value: sensitivity or range

    if (*(char *)(thisPtr + 0x10) == '\0') {
      // Not currently in an active blocking action — check for press/hold start
      iVar10 = thisPtr + 0x11;
      uVar9 = FUN_0049a890(uVar9, uVar2, iVar10);   // Get action state for press type
      cVar5 = evaluateActionCondition(actionId, uVar9, iVar10);
      if (cVar5 == '\0') {
        // Try hold start instead
        iVar10 = thisPtr + 0x12;
        uVar9 = FUN_0049a8b0(uVar9, uVar2, iVar10);
        cVar5 = evaluateActionCondition(actionId, uVar9, iVar10);
        if (cVar5 == '\0') {
          // Neither press nor hold — skip further processing
          goto LAB_00691063;
        }
      }

      // Condition satisfied — decide if it's a toggle or one-shot
      if (bVar4 == 0) {
        // Toggle off: flip the toggle state (if not in a special mode like driving)
        if (iVar6 != 2) {
          *(int *)(thisPtr + 0xc) = (uint)(*(int *)(thisPtr + 0xc) == 0);
        }
      } else {
        // One-shot: always set to active, play sound if enabled
        bVar4 = 0;  // Reset flag to prevent double processing
        *(int *)(thisPtr + 0xc) = 1;
        if (DAT_01223464 != 0) {  // Sound effects enabled?
          uVar9 = getSoundHandle(1);   // "action activate" sound
          playSound(uVar9);
        }
      }
    } else {
      // Currently in an active action — check if conditions to exit are met
      cVar5 = FUN_0049a890(uVar9, uVar2);
      if ((((cVar5 == '\0') || (cVar5 == -1)) || (cVar5 = FUN_00b930b0(cVar5), cVar5 == '\0')) &&
         (((cVar5 = FUN_0049a8b0(uVar9, uVar2), cVar5 == '\0' || (cVar5 == -1)) ||
          (cVar5 = FUN_00b930b0(cVar5), cVar5 == '\0')))) {
        // Both press and hold conditions are no longer valid — deactivate action
        *(char *)(thisPtr + 0x10) = 0;
      }
    }
  }

LAB_00691063:
  // Determine final action state (0=off, 1=on, 2=toggle)
  iVar10 = *(int *)(thisPtr + 0xc);
  if (bVar4 != 0) {
    iVar10 = 0;  // One-shot mode resets state
  }

  // Check for toggle input (second input, e.g., shoulder button)
  cVar5 = isInputActionActive(0x78467823, playerObj, actionId);
  if (cVar5 == '\0') {
    *(char *)(thisPtr + 0x13) = 0;  // No toggle input
  } else {
    iVar10 = 2;  // Force toggle mode
    *(bool *)(thisPtr + 0x13) = *(char *)(thisPtr + 0x13) == '\0';  // Flip toggle flag
  }

  // Analog input present?
  if (((*analogInput != 0.0f) || (analogInput[1] != 0.0f)) && (DAT_01223464 != 0)) {
    if (iVar10 == 1) {
      // Action active
      if (iVar6 != 2) {  // Not in a special mode (driving?)
        uVar9 = getSoundHandle(0);  // "action active" sound
        playSound(uVar9);
      }
    } else if (iVar10 == 2) {
      // Toggle mode
      uVar9 = getSoundHandle(0);
      playSound(uVar9);
      if (*(char *)(thisPtr + 0x13) != '\0') {
        // Toggle ON sound
        playSound(0x466dc7de);  // Specific sound hash for toggle on
        return;
      }
    }
  }
  return;
}