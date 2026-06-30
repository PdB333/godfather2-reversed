// FUNC_NAME: NavPath::findPath
int NavPath::findPath(int *pathData, int *gridData, undefined4 *outputData, int bForceRecalc)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  undefined8 uVar11;
  int local_64;          // +0x64: padding/spacing
  int local_54[2];       // +0x54: array of 2 ints (maybe min/max node)
  int local_4c;          // +0x4c: flag
  int local_48;          // +0x48: pointer to node array (from)
  int local_44[2];       // +0x44: array of 2 ints (maybe other min/max)
  undefined4 local_3c;   // +0x3c: temporary
  int local_38;          // +0x38: pointer to node array (to)
  undefined4 local_34[3];// +0x34: array of 3 ints (used for tile/pos)
  undefined4 *local_28;  // +0x28: pointer into local_34
  int local_24;          // +0x24: some offset
  int local_18;          // +0x18: pointer to result array
  undefined4 local_14;   // +0x14: temp
  undefined4 *local_8;   // +0x08: another pointer
  
  // Check if grid is empty
  if (*gridData == 0) {
    return -3;
  }
  
  iVar5 = FUN_00665c30(); // check if pathfinding is idle?
  if (iVar5 == -1) {
    if (bForceRecalc == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = FUN_00665ce0(); // force recalc setup
    }
    if (outputData != (undefined4 *)0x0) {
      outputData[2] = 0;
      *outputData = 0;
      _memset((void *)outputData[3], 0, outputData[1] * 4);
    }
    return iVar5;
  }
  
  iVar5 = FUN_006678c0(); // check for errors
  if (iVar5 != 0) {
    return iVar5;
  }
  
  local_24 = *pathData + 2; // offset into pathData
  iVar5 = FUN_006677b0(); // lock or begin pathfinding
  if (iVar5 != 0) goto LAB_00666227;
  
  iVar5 = FUN_006677b0();
  if (iVar5 == 0) {
    iVar5 = FUN_006677e0(); // ?
    if (iVar5 == 0) {
      iVar5 = FUN_006677e0();
      if (iVar5 == 0) {
        iVar3 = pathData[2]; // some flag
        iVar2 = gridData[2];
        local_3c = 0;
        local_4c = 0;
        iVar5 = FUN_00665d40(); // get random or timer?
        // Align to 0x1c tokens?
        if (iVar5 % 0x1c < 0x1b) {
          local_64 = 0x1b - iVar5 % 0x1c;
          iVar5 = FUN_00668e40(local_64); // allocate memory?
          if ((iVar5 == 0) && (iVar5 = FUN_00668e40(local_64), iVar5 == 0)) goto LAB_00665ed6;
        }
        else {
          local_64 = 0;
LAB_00665ed6:
          iVar6 = local_44[0] + -1;   // end of first range
          iVar9 = local_54[0] + -1;   // end of second range
          iVar10 = iVar9 - iVar6;     // difference
          iVar5 = FUN_006687e0(iVar10); // validate range
          if (iVar5 == 0) {
            iVar5 = FUN_00665bd0(); // get next node?
            while (iVar5 != -1) {
              piVar1 = (int *)(local_18 + iVar10 * 4);
              *piVar1 = *piVar1 + 1; // increment count
              iVar5 = FUN_0066a780(local_54, local_44); // push nodes?
              if (iVar5 != 0) goto LAB_00666203;
              iVar5 = FUN_00665bd0();
            }
            FUN_0066a4d0(iVar10); // process range
            // Iterate from local_44[0] down to local_54[0]
            for (; local_44[0] <= iVar9; iVar9 = iVar9 + -1) {
              if (iVar9 <= local_54[0]) {
                uVar7 = *(uint *)(local_48 + iVar9 * 4);   // from node value
                uVar4 = *(uint *)(local_38 + iVar6 * 4);   // to node value
                if (uVar7 == uVar4) {
                  iVar10 = iVar9 - iVar6;
                  *(undefined4 *)(local_18 + -4 + iVar10 * 4) = 0xfffffff;
                }
                else {
                  // Fixed-point division: (uVar7 << 28 | prev) / uVar4
                  uVar11 = __aulldiv(uVar7 << 0x1c | *(uint *)(local_48 + -4 + iVar9 * 4),
                                     uVar7 >> 4,
                                     uVar4, 0);
                  uVar7 = (uint)uVar11;
                  if (((int)((ulonglong)uVar11 >> 0x20) != 0) || (0xfffffff < uVar7)) {
                    uVar7 = 0xfffffff;
                  }
                  iVar10 = iVar9 - iVar6;
                  *(uint *)(local_18 + -4 + iVar10 * 4) = uVar7 & 0xfffffff;
                }
                *(uint *)(local_18 + -4 + iVar10 * 4) =
                     *(int *)(local_18 + -4 + iVar10 * 4) + 1U & 0xfffffff;
                do {
                  *(uint *)(local_18 + -4 + iVar10 * 4) =
                       *(int *)(local_18 + -4 + iVar10 * 4) - 1U & 0xfffffff;
                  FUN_0066baa0(); // step function (Bresenham?)
                  if (local_44[0] + -2 < 0) {
                    uVar8 = 0;
                  }
                  else {
                    uVar8 = *(undefined4 *)(local_38 + -4 + iVar6 * 4);
                  }
                  *local_28 = uVar8;
                  local_28[1] = *(undefined4 *)(local_38 + iVar6 * 4);
                  local_34[0] = 2;
                  iVar5 = FUN_00668f50(local_34, *(undefined4 *)(local_18 + -4 + iVar10 * 4), local_34);
                  if (iVar5 != 0) goto LAB_00666203;
                  if (iVar9 + -2 < 0) {
                    uVar8 = 0;
                  }
                  else {
                    uVar8 = *(undefined4 *)(local_48 + (iVar9 + -2) * 4);
                  }
                  *local_8 = uVar8;
                  if (iVar9 + -1 < 0) {
                    uVar8 = 0;
                  }
                  else {
                    uVar8 = *(undefined4 *)(local_48 + -4 + iVar9 * 4);
                  }
                  local_8[1] = uVar8;
                  local_8[2] = *(undefined4 *)(local_48 + iVar9 * 4);
                  local_14 = 3;
                  iVar5 = FUN_00665c30();
                } while (iVar5 == 1); // repeat while not idle?
                iVar5 = FUN_00668f50(local_44, *(undefined4 *)(local_18 + -4 + iVar10 * 4), local_34);
                if ((iVar5 != 0) || (iVar5 = FUN_006687e0(iVar10 + -1), iVar5 != 0))
                  goto LAB_00666203;
                iVar5 = FUN_0066a780(local_54, local_34);
                if (iVar5 != 0) goto LAB_00666203;
                if (local_4c == 1) {
                  iVar5 = FUN_00665ce0();
                  if (((iVar5 != 0) || (iVar5 = FUN_006687e0(iVar10 + -1), iVar5 != 0)) ||
                     (iVar5 = FUN_006657c0(local_54), iVar5 != 0)) goto LAB_00666203;
                  *(uint *)(local_18 + -4 + iVar10 * 4) =
                       *(int *)(local_18 + -4 + iVar10 * 4) - 1U & 0xfffffff;
                }
              }
            }
            local_4c = pathData[2]; // save original flag
            if (outputData != (undefined4 *)0x0) {
              FUN_00665b10(); // update output?
              FUN_00666970(); // ?
              outputData[2] = (uint)(iVar3 != iVar2);
            }
            if (bForceRecalc != 0) {
              FUN_00666300(local_54, local_64, local_54, 0);
              FUN_00666970();
            }
            iVar5 = 0;
          }
        }
LAB_00666203:
        FUN_00665b40(); // cleanup
      }
      FUN_00665b40();
    }
    FUN_00665b40();
  }
  FUN_00665b40();
LAB_00666227:
  FUN_00665b40();
  return iVar5;
}