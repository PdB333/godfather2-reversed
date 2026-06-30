// FUNC_NAME: FUN_005eb270
// Address: 0x005eb270
// Role: Validates animation clip transitions for a character slot (likely player or NPC)
//       Checks that the animation's start/end frame range is valid within the clip data.
// Returns true (1) if all animations in all slots/loops are valid, false (0) if any range check fails.
// Uses a global pointer at DAT_01223508+0xf4 as a manager or data root.
// param_2 is likely an animation request/state structure with:
//   +0x04: array of int* (slot data pointers?) - size at +0x0c
//   +0x08: array of int* (ID list?) - size at +0x0c
//   +0x0c: count (uint)
//   +0x14: base pointer to array of structures at +4 + index*0x0c
//   +0x2c: some ID/filter

undefined1 FUN_005eb270(undefined4 param_1, int param_2)
{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  int *piVar9;
  undefined1 uVar10;
  int *piVar11;
  bool bVar12;
  undefined1 allValid;
  int *currentSlotList;
  int loopCount;
  
  allValid = 1;
  loopCount = 5;
  
  // Check if global manager exists
  if ((*(int *)(DAT_01223508 + 0xf4) != 0) &&
      (puVar7 = (undefined4 *)FUN_005e9a20(*(undefined4 *)(param_2 + 0x2c)),
       puVar7 != (undefined4 *)0x0)) {
    // Loop through 5 animation slots (layers? e.g., full body, upper, lower, etc.)
    do {
      iVar2 = puVar7[10]; // number of animation entries in this slot
      bVar12 = iVar2 != 0;
      if (bVar12) {
        currentSlotList = (int *)*puVar7;
        // Walk linked list of animation entries
        while (bVar12) {
          if (currentSlotList != (int *)0x0) {
            iVar3 = currentSlotList[0x12]; // loop count (blend cycles?) for this entry
            bVar12 = iVar3 != 0;
            if (bVar12) {
              iVar4 = *currentSlotList; // pointer to animation clip data
              while (bVar12) {
                if (iVar4 != 0) {
                  uVar8 = 0;
                  // Check each request slot against our ID list
                  if (*(uint *)(param_2 + 0xc) != 0) {
                    piVar9 = *(int **)(param_2 + 8);
                    do {
                      if (*piVar9 == currentSlotList[0x11]) { // match ID
                        iVar5 = *(int *)(*(int *)(param_2 + 0x14) + 4 + uVar8 * 0xc);
                        currentSlotList = (int *)currentSlotList[0x13]; // save next pointer for iteration
                        if (*(int *)(*(int *)(param_2 + 4) + uVar8 * 4) != 0) {
                          fVar1 = *(float *)(iVar4 + 0x28); // current animation frame/time
                          iVar6 = *(int *)(iVar4 + 0x24); // animation clip index
                          FUN_00c9eac0(); // begin read of clip data (mutex?)
                          iVar5 = *(int *)(iVar5 + 0x18) +
                                  ((uint)*(byte *)(iVar5 + 0x2d) + iVar6) * 0x28;
                          // Check frame range: validity of current frame against clip start/end
                          if (((double)fVar1 < *(double *)(iVar5 + 0x10)) || // less than start frame
                             (*(double *)(iVar5 + 0x18) < (double)fVar1)) { // greater than end frame
                            allValid = 0; // frame out of range -> invalid
                          }
                          else {
                            FUN_00ca4e90(iVar6, fVar1); // apply frame to something (update pose?)
                          }
                          FUN_00c9eae0(); // end read of clip data (mutex?)
                        }
                        break;
                      }
                      uVar8 = uVar8 + 1;
                      piVar9 = piVar9 + 1;
                    } while (uVar8 < *(uint *)(param_2 + 0xc));
                  }
                }
                iVar3 = iVar3 + -1; // decrement loop count
                bVar12 = iVar3 != 0;
                iVar4 = *(int *)(iVar4 + 0x2c); // next clip in chain
              }
            }
            currentSlotList = (int *)currentSlotList[0x13]; // next linked list entry
          }
          iVar2 = iVar2 + -1;
          bVar12 = iVar2 != 0;
          uVar10 = allValid;
        }
      }
      loopCount = loopCount + -1;
    } while (loopCount != 0);
  }
  return uVar10;
}