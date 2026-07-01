// FUNC_NAME: PlayerReputationTracker::updateReputationEvents
void __thiscall PlayerReputationTracker::updateReputationEvents(int thisPtr, int *param_2)
{
  undefined4 uVar1;
  float *pfVar2;
  float fVar3;
  int iStack_60;
  int iStack_5c;
  int iStack_58;
  float fStack_54;
  undefined1 auStack_50 [76];
  
  // Check if any reputation event flags are set (at offsets +0x168 to +0x174)
  if ((((*(int *)(thisPtr + 0x168) != 0) || (*(int *)(thisPtr + 0x16c) != 0)) ||
      (*(int *)(thisPtr + 0x170) != 0)) || (*(int *)(thisPtr + 0x174) != 0)) {
    // Call virtual function at vtable+0x220 to get number of reputation sources
    iStack_58 = (**(code **)(*param_2 + 0x220))();
    if (iStack_58 != 0) {
      iStack_60 = 0;
      pfVar2 = (float *)(thisPtr + 0x148); // +0x148: array of last update times for each source
      do {
        // Get current reputation value for this source from param_2[0xd8]->+0x48->+0x50 + offset
        fStack_54 = *(float *)(*(int *)(param_2[0xd8] + 0x48) + 0x50 + iStack_60);
        // Calculate time delta with bitwise AND for wrapping (DAT_00e44680 is likely a mask)
        fVar3 = (float)((uint)(fStack_54 - *pfVar2) & DAT_00e44680) * _DAT_00d76ad0;
        // Check if enough time has passed since last update (threshold at +0x144)
        if (*(float *)(thisPtr + 0x144) <= fVar3 && fVar3 != *(float *)(thisPtr + 0x144)) {
          // Check if we should trigger a reputation event (time-based throttling)
          if (((uint)DAT_01205210 < (uint)pfVar2[4]) ||
             (499 < (uint)((int)DAT_01205210 - (int)pfVar2[4]))) {
            pfVar2[4] = DAT_01205210; // Update timestamp
            uVar1 = FUN_00471610(); // Get some identifier
            FUN_0044b4e0(auStack_50, uVar1); // Format string or prepare data
            // Create reputation event (param_1 + 0x168 is event list, +0x134 is context)
            FUN_004df330(&iStack_5c, thisPtr + 0x168, auStack_50, *(undefined4 *)(thisPtr + 0x134), 0, 0, 0xffffffff, 0);
            if (iStack_5c != 0) {
              *(undefined4 *)(iStack_5c + 8) = 0; // Clear some flag on new event
              iStack_5c = 0;
            }
          }
        }
        iStack_60 = iStack_60 + 0xc0; // Each source entry is 0xC0 bytes
        *pfVar2 = fStack_54; // Update last tracked value
        pfVar2 = pfVar2 + 1; // Move to next source's timestamp
        iStack_58 = iStack_58 + -1;
      } while (iStack_58 != 0);
    }
  }
  return;
}