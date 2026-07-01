// FUNC_NAME: InviteManager::handleInviteStatus

void __thiscall InviteManager::handleInviteStatus(void* thisPtr, int* actionData)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  
  iVar4 = DAT_0112980c; // g_pGameManager
  if (*actionData == DAT_01206940) // Some action ID constant (likely kActionInvite)
  {
    // Check flag: waiting for invite response?
    if (*(char*)(thisPtr + 0x140) == '\0')
    {
      // Not waiting, check if accept ignored flag is set
      if (*(char*)(thisPtr + 0x141) == '\0')
      {
        // Neither waiting nor ignored, check if showing invite accept
        if ((*(char*)(thisPtr + 0x142) != '\0') &&
            (fVar5 = *(float*)(thisPtr + 0x144) - DAT_01206800, *(float*)(thisPtr + 0x144) = fVar5,
            fVar5 <= 0.0))
        {
          // Timer expired: hide invite accept UI
          *(undefined1*)(thisPtr + 0x142) = 0;
          *(undefined4*)(thisPtr + 0x144) = 0;
          if ((DAT_0112982c != 0) && // g_pUIManager
              (iVar4 = FUN_004d4b70("$ui_invite_accepts_ignored"), iVar4 == 0)) // string compare
          {
            FUN_00983120(0,0,0); // Clear UI text?
          }
        }
      }
      else
      {
        // Accept ignored flag set
        if (((DAT_0112982c != 0) && (*(int*)(DAT_0112982c + 0x7c) == 0)) &&
            (cVar1 = FUN_00982670(), cVar1 != '\0'))
        {
          // Show invite accepted but ignored message
          FUN_00983120("$ui_invite_accepts_ignored",0,0);
          uVar2 = DAT_00e44948; // Timeout duration
          *(undefined1*)(thisPtr + 0x141) = 0;
          *(undefined1*)(thisPtr + 0x142) = 1;
          *(undefined4*)(thisPtr + 0x144) = uVar2;
          FUN_004bed20(actionData);
          return;
        }
      }
    }
    else
    {
      // Waiting for invite response
      uVar2 = FUN_00683280("GameMainLoop"); // Get game state string
      iVar3 = FUN_006833d0(uVar2); // Get game state ID
      if (iVar3 != *(int*)(iVar4 + 4)) // Compare to current game state
      {
        // Game state changed, stop waiting
        *(undefined1*)(thisPtr + 0x140) = 0;
        FUN_004bed20(actionData);
        return;
      }
      if ((DAT_011298a0 == 0) || (*(char*)(DAT_011298a0 + 0x2c) == '\0')) // Check some flag (maybe menu active)
      {
        // Not in correct state, cancel invite
        *(undefined1*)(thisPtr + 0x140) = 0;
        DAT_00e5672c = 0x19; // Set some game state/timer
        FUN_0067c920(); // Reset something
        FUN_004bed20(actionData);
        return;
      }
    }
  }
  FUN_004bed20(actionData);
  return;
}