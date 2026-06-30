// FUNC_NAME: ChaseCamera::setTarget
// Function address: 0x006a6670
// Role: Sets the current target for the chase camera. Searches a pool of up to 32 slots (each with 4 sub-slots) for the target ID.
//       If found, clears the current target. If not found, assigns a new current target and loads its color/quaternion from a database.
//       The pool is used to pre-register valid chase targets (e.g., vehicles, objects).

void __thiscall ChaseCamera::setTarget(int param_2)
{
  int *piSlotCurr;
  int iSlotIndex;

  if (param_2 != m_currentTargetID) {
    // If the system was previously active but not locked, release the old target.
    if ((m_bTargetLocked == 0) && (m_currentTargetID != 0)) {
      releaseCurrentTarget(); // FUN_006a65d0
    }
    iSlotIndex = 0;
    piSlotCurr = (int *)&m_targetSlots; // +0x6d4 - base of slot array
    do {
      // Each slot occupies 0x18 (24) bytes in memory. The four sub-slot IDs are located at fixed offsets
      // relative to the slot's base address: -0x18 (piSlotCurr[-6]), 0x00 (*piSlotCurr), +0x18 (piSlotCurr[6]), +0x30 (piSlotCurr[12]).
      // The slot index is derived from iSlotIndex/4, and the sub-slot index is iSlotIndex%4.
      if (piSlotCurr[-6] == param_2) break;             // sub-slot 0
      if (*piSlotCurr == param_2) {
        iSlotIndex = iSlotIndex + 1;                     // sub-slot 1
        break;
      }
      if (piSlotCurr[6] == param_2) {
        iSlotIndex = iSlotIndex + 2;                     // sub-slot 2
        break;
      }
      if (piSlotCurr[0xc] == param_2) {
        iSlotIndex = iSlotIndex + 3;                     // sub-slot 3
        break;
      }
      iSlotIndex = iSlotIndex + 4;                       // advance to next slot
      piSlotCurr = piSlotCurr + 6;                       // move to next slot (6 ints = 0x18 bytes)
    } while (iSlotIndex < 0x20);                         // 32 slots
    if (iSlotIndex == 0x20) {
      // Target not found in any slot → set as new current target.
      m_currentTargetID = param_2;                       // +0x6a4
      m_bTargetLocked = 1;                               // +0x6b8
      int *pTargetData = (int *)getTargetData(&param_2); // FUN_0088d5f0 - retrieves data for target ID
      if (pTargetData == 0) {
        // Default color (white?) if no data available.
        m_targetColorR = 0;                              // +0x6a8
        m_targetColorG = 0;                              // +0x6ac
        m_targetColorB = 0;                              // +0x6b0
        m_targetColorA = _DAT_00d5780c;                  // +0x6b4 - global default alpha value
      } else {
        // Copy 16 bytes (RGBA or quaternion) from target data (+0x14 and +0x1c offsets).
        m_targetColorR = pTargetData[0x5];               // +0x14
        m_targetColorG = pTargetData[0x6];               // +0x18
        m_targetColorB = pTargetData[0x7];               // +0x1c
        m_targetColorA = pTargetData[0x8];               // +0x20
      }
    } else {
      // Target found in slot → clear current target.
      m_currentTargetID = 0;                             // +0x6a4
    }
  }
  // If param_2 already equals m_currentTargetID, do nothing.
}