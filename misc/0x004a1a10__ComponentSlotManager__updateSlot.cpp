// FUNC_NAME: ComponentSlotManager::updateSlot
void __thiscall ComponentSlotManager::updateSlot(int *pThis, int someId, void *pObject, int extra1, int extra2, char boolFlag)
{
  int *pSlotEntry;
  int iVar2;
  int iVar3;
  int *pPair;
  int *pSrc;
  int local_18;
  int local_14;
  
  if (pObject != (void *)0x0) {
    if (*(char *)(pThis + 0x70) != '\0') {
      // Pending addition: use separate slot array
      pThis[0x6f] = pThis[0x6f] + 1;  // increment pending index
      pSlotEntry = pThis + pThis[0x6f] * 7 + 0x53;  // base of 7-int slot
      *pSlotEntry = 1;  // mark as active
      iVar2 = (int)pObject + 0x48;  // address of field at +0x48
      if (pSlotEntry[1] != iVar2) {
        if (pSlotEntry[1] != 0) {
          FUN_004daf90(pSlotEntry + 1);  // free old reference
        }
        pSlotEntry[1] = iVar2;
        if (iVar2 != 0) {
          pSlotEntry[2] = *(int *)((int)pObject + 0x4c);  // save previous link
          *(int **)((int)pObject + 0x4c) = pSlotEntry;  // link object to slot
        }
      }
      pSlotEntry[3] = extra1;
      pSlotEntry[4] = someId;
      pSlotEntry[5] = extra2;
      return;
    }
    // Active slot count management (max 7)
    if (pThis[0x21] == 7) {
      // Compact if full: array of pairs at +0x11
      // +0x11 = 0x44 bytes offset, each pair is 2 ints (8 bytes)
      pPair = pThis + 0x11;
      local_18 = 0;
      local_14 = 0;
      do {
        if ((pPair[0] != 0) && (pPair[0] != 0x48)) {
          local_18 = local_18 + 1;
          pPair = pPair + 2;
        }
        if (local_18 < local_14) {
          if (pPair != pThis + 0x11) {
            iVar2 = pThis[0x11];
            if (pPair[0] != iVar2) {
              if (pPair[0] != 0) {
                FUN_004daf90(pPair);
              }
              pPair[0] = iVar2;
              if (iVar2 != 0) {
                pPair[1] = *(int *)(iVar2 + 4);
                *(int **)(iVar2 + 4) = pPair;
              }
            }
          }
          if (pThis[0x11] != 0) {
            FUN_004daf90(pThis + 0x11);
            pThis[0x11] = 0;
          }
        }
        local_14 = local_14 + 1;
        pThis = pThis + 2;
      } while (local_14 <= pThis[0x21]);
      // Shrink active count
      iVar2 = pThis[0x21];
      while (iVar2 >= 0) {
        if ((pThis[pThis[0x21] * 2 + 0x11] != 0) && (pThis[pThis[0x21] * 2 + 0x11] != 0x48))
          break;
        iVar2 = pThis[0x21] - 1;
        pThis[0x21] = iVar2;
      }
    }
    iVar2 = pThis[0x21];
    if (iVar2 != 7) {
      if (iVar2 >= 0) {
        // Check if this slot already contains this object
        iVar3 = pThis[iVar2 * 2 + 0x11];
        if (iVar3 == 0) {
          iVar3 = 0;
        } else {
          iVar3 = iVar3 - 0x48;
        }
        if (iVar3 == (int)pObject) {
          return;  // already registered
        }
        // If slot occupied and not removable
        if ((iVar2 >= 0) && (iVar3 = pThis[iVar2 * 2 + 0x11], iVar3 != 0) && (iVar3 != 0x48) && (*(char *)(iVar3 + 0xd) != '\0')) {
          pThis[0x21] = iVar2 + 1;
          FUN_004a2f90();  // some setup/clear
          FUN_004a2f60();  // notify/update
          return;
        }
      }
      if (iVar2 < 0) {
        // Backup current state when entering negative index
        boolFlag = 1;
        pThis[4] = pThis[0];
        pThis[5] = pThis[1];
        pThis[6] = pThis[2];
        pThis[7] = pThis[3];
      }
      pThis[0x21] = pThis[0x21] + 1;
      FUN_004a2f60();  // pre-update callback
      FUN_004a20a0(someId, extra1, extra2, boolFlag);  // process slot addition
      if (pThis[0x21] == 0) {
        // Restore saved state from another array when count resets
        // +0x46 is index into a triplet array at +0x22 (=0x88 bytes)
        // Each triplet is 3 ints, so +0x46 * 3 + 0x22 points to a pointer
        pSrc = (int *)(pThis[pThis[0x46] * 3 + 0x22] + 0x20);
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *pThis = *pSrc;
          pSrc = pSrc + 1;
          pThis = pThis + 1;
        }
        return;
      }
    }
  }
  return;
}