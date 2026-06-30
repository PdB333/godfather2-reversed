// FUNC_NAME: SimObject::updateEventQueue
void SimObject::updateEventQueue(int param_1)
{
  uint *puVar1;
  byte bVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  uint *puVar8;
  int *piVar9;
  uint *puVar10;
  byte *pbVar11;
  int *piVar12;
  int iVar13;
  uint local_24;
  uint *local_1c;
  uint uStack_18;
  int *piStack_14;
  byte uStack_10;
  uint local_c;
  int *local_8;
  byte local_4;
  
  iVar13 = *(int *)(param_1 + 0x98); // current event node
  do {
    if (iVar13 == 0) {
      return;
    }
    piVar3 = *(int **)(param_1 + 0x98); // current event node
    // Hash table lookup: key = piVar3[11] (eventId)
    // param_1+0x48 = hash table, param_1+0x4c = table size
    for (local_1c = *(uint **)(*(int *)(param_1 + 0x48) +
                              ((uint)piVar3[0xb] % *(uint *)(param_1 + 0x4c)) * 4);
        local_1c != (uint *)0x0; local_1c = (uint *)local_1c[6]) {
      if (*local_1c == piVar3[0xb]) {
        if (local_1c != (uint *)0x0) {
          local_1c = local_1c + 1; // skip key to data
          goto LAB_00447113;
        }
        break;
      }
    }
    local_1c = (uint *)0x0;
LAB_00447113:
    uVar4 = piVar3[7]; // number of actions for this event
    local_24 = 0;
    if (uVar4 != 0) {
      do {
        // piVar3[10] = array of action pointers
        piVar5 = *(int **)(piVar3[10] + local_24 * 4); // action
        if ((*(byte *)(piVar5 + 7) & 1) == 0) {
          // action uses a string hash (name)
          pbVar11 = (byte *)(piVar5 + 10); // pointer to name string
          iVar13 = 0;
          if (pbVar11 != (byte *)0x0) {
            bVar2 = *pbVar11;
            while (bVar2 != 0) {
              uVar7 = (uint)bVar2;
              pbVar11 = pbVar11 + 1;
              // lowercase conversion
              if (uVar7 - 0x41 < 0x1a) {
                uVar7 = uVar7 + 0x20;
              }
              iVar13 = iVar13 * 0x1003f + uVar7; // hash computation
              bVar2 = *pbVar11;
            }
          }
        }
        else {
          // action uses a direct integer key
          iVar13 = piVar5[10];
        }
        uVar7 = 0;
        // Search in callback table at param_1+0xd0 (array of (key, func) pairs)
        // size at param_1+0x2d0
        if (*(uint *)(param_1 + 0x2d0) != 0) {
          piVar12 = (int *)(param_1 + 0xd0); // start of callback array
LAB_00447195:
          if (*piVar12 != iVar13) {
            uVar7 = uVar7 + 1;
            piVar12 = piVar12 + 2; // each entry is 2 ints: key, func
            if (*(uint *)(param_1 + 0x2d0) <= uVar7) goto LAB_004471a7;
            goto LAB_00447195;
          }
          if ((code *)piVar12[1] != (code *)0x0) {
            // Build argument for callback (action data)
            if ((*(byte *)(piVar5 + 7) & 1) == 0) {
              // action with string name: traverse linked list to find data block
              piVar9 = piVar5 + 8;
              iVar6 = piVar5[9];
              while (iVar6 != 0x40000000) {
                piVar9 = (int *)((int)piVar9 + *piVar9);
                iVar6 = piVar9[1];
              }
              piVar9 = piVar9 + 2;
            }
            else if (piVar5[9] == 0) {
              // no data: use default zero vector
              if ((_DAT_01223d10 & 1) == 0) {
                _DAT_01223d10 = _DAT_01223d10 | 1;
                DAT_01223d00 = 0;
                DAT_01223d04 = 0;
                DAT_01223d08 = 0;
                DAT_01223d0c = 0;
              }
              piVar9 = &DAT_01223d00;
            }
            else {
              // action with integer key: data at offset 0x24 from action
              piVar9 = (int *)(piVar5[9] + 0x24 + (int)piVar5);
            }
            (*(code *)piVar12[1])(iVar13, piVar9, piVar3[0xb], piVar5, 2);
            goto LAB_00447210;
          }
        }
LAB_004471a7:
        // Process linked list of "listeners" or "targets" from action
        puVar1 = (uint *)(piVar5 + 5); // pointer to first listener
        uVar7 = *puVar1;
        while (uVar7 != 0) {
          piVar9 = (int *)*puVar1;
          iVar13 = 0;
          // Check if listener is in the event's "active listeners" list (local_1c[3])
          for (piVar12 = (int *)local_1c[3]; piVar12 != (int *)0x0; piVar12 = (int *)piVar12[2]) {
            if (piVar12 == piVar9) {
              if (-1 < iVar13) {
                // Call listener's notify function (vtable+0xc)
                (**(code **)(*piVar9 + 0xc))();
                piVar12 = piVar9;
                // Handle extended data if flag 0x8000000 set and subflag 2
                if (((piVar9[5] & 0x8000000U) != 0) &&
                   (piVar12 = piVar9 + 0xf, (*(byte *)(piVar9 + 0x10) & 2) != 0)) {
                  uStack_18 = DAT_012067dc; // default transform
                  uStack_10 = 0;
                  piStack_14 = piVar12;
                  (**(code **)(*piVar12 + 4))(&uStack_18);
                }
                (**(code **)*piVar12)(1); // call delete (vtable+0x0 with arg 1)
                goto LAB_0044720c;
              }
              break;
            }
            iVar13 = iVar13 + 1;
          }
          // If listener not in active list, remove it from action's listener list
          if (piVar9 != (int *)0x0) {
            if (piVar9[4] != 0) {
              *(uint **)(piVar9[4] + 0xc) = puVar1;
            }
            *puVar1 = *(uint *)(*puVar1 + 0x10);
            piVar9[3] = 0;
            piVar9[4] = 0;
          }
          // Add to free list at param_1+0x68
          puVar8 = (uint *)(param_1 + 0x68);
          piVar9[4] = *(int *)(param_1 + 0x68);
          piVar9[3] = (int)puVar8;
          if (*puVar8 != 0) {
            *(int **)(*puVar8 + 0xc) = piVar9 + 4;
          }
          *puVar8 = (uint)piVar9;
LAB_0044720c:
          uVar7 = *puVar1;
        }
LAB_00447210:
        FUN_004483c0(param_1, piVar3[0xb]); // cleanup or notify
        // Remove action from its list (double linked list)
        if ((int *)*piVar5 != (int *)0x0) {
          *(int *)*piVar5 = piVar5[1];
        }
        if ((int *)piVar5[1] != (int *)0x0) {
          *(int *)piVar5[1] = *piVar5;
        }
        local_24 = local_24 + 1;
        piVar5[1] = 0;
        *piVar5 = 0;
      } while (local_24 < uVar4);
    }
    // Process items in "pending remove" list at param_1+0x6c
    piVar5 = *(int **)(param_1 + 0x6c);
joined_r0x00447266:
    piVar12 = piVar5;
    if (piVar12 != (int *)0x0) {
      piVar5 = (int *)piVar12[4];
      // Check if this pending item's eventId matches current event
      if ((piVar12[7] == piVar3[0xb]) && (uVar7 = 0, uVar4 != 0)) {
        do {
          iVar13 = *(int *)(piVar3[10] + uVar7 * 4);
          if ((*(byte *)(iVar13 + 0x1c) & 1) == 0) {
            // string-based action: traverse linked list for data
            piVar9 = (int *)(iVar13 + 0x20);
            iVar13 = *(int *)(iVar13 + 0x24);
            while (iVar13 != 0x40000000) {
              piVar9 = (int *)((int)piVar9 + *piVar9);
              iVar13 = piVar9[1];
            }
            piVar9 = piVar9 + 2;
          }
          else if (*(int *)(iVar13 + 0x24) == 0) {
            if ((_DAT_01223d10 & 1) == 0) {
              _DAT_01223d10 = _DAT_01223d10 | 1;
              DAT_01223d00 = 0;
              DAT_01223d04 = 0;
              DAT_01223d08 = 0;
              DAT_01223d0c = 0;
            }
            piVar9 = &DAT_01223d00;
          }
          else {
            piVar9 = (int *)(*(int *)(iVar13 + 0x24) + 0x24 + iVar13);
          }
          // Compare data with pending item's position (piVar12[8..11])
          if ((((*piVar9 == piVar12[8]) && (piVar9[1] == piVar12[9])) && (piVar9[2] == piVar12[10]))
             && (piVar9[3] == piVar12[0xb])) {
            if ((piVar12[5] & 0x8000000U) == 0) {
              puVar10 = (undefined4 *)*piVar12;
            }
            else {
              piVar9 = piVar12 + 0xf;
              if ((*(byte *)(piVar12 + 0x10) & 2) != 0) {
                local_4 = 0;
                local_c = DAT_012067dc;
                local_8 = piVar9;
                (**(code **)(*piVar9 + 4))(&local_c);
              }
              puVar10 = (undefined4 *)*piVar9;
            }
            (*(code *)*puVar10)(1); // call delete
            break;
          }
          uVar7 = uVar7 + 1;
        } while (uVar7 < uVar4);
      }
      goto joined_r0x00447266;
    }
    // Reset action count for this event
    piVar3[7] = 0;
    // Remove current event node from its list (param_1+0x98 is head)
    if ((int *)piVar3[1] == (int *)0x0) {
      iVar13 = *piVar3;
      *(int *)(param_1 + 0x98) = iVar13;
      if (iVar13 != 0) {
        *(undefined4 *)(iVar13 + 4) = 0;
        goto LAB_00447468;
      }
LAB_00447476:
      puVar10 = (uint *)piVar3[1];
      *(uint **)(param_1 + 0x9c) = puVar10;
      if (puVar10 != (uint *)0x0) {
        *puVar10 = 0;
      }
    }
    else {
      *(int *)piVar3[1] = *piVar3;
LAB_00447468:
      if (*piVar3 == 0) goto LAB_00447476;
      *(int *)(*piVar3 + 4) = piVar3[1];
    }
    // Clear node links
    *piVar3 = 0;
    piVar3[1] = 0;
    *piVar3 = 0;
    // Move node to appropriate list based on flag 0x10
    if ((piVar3[5] & 0x10U) == 0) {
      // Add to normal free list
      piVar3[1] = *(int *)(param_1 + 0xac);
      if (*(uint **)(param_1 + 0xac) == (uint *)0x0) {
        *(int **)(param_1 + 0xa8) = piVar3;
      }
      else {
        **(uint **)(param_1 + 0xac) = piVar3;
      }
      *(int **)(param_1 + 0xac) = piVar3;
    }
    else {
      // Add to special free list (with flag 0x40 set)
      piVar3[5] = piVar3[5] | 0x40;
      piVar3[1] = *(int *)(param_1 + 0x94);
      if (*(uint **)(param_1 + 0x94) == (uint *)0x0) {
        *(int **)(param_1 + 0x90) = piVar3;
        *(int **)(param_1 + 0x94) = piVar3;
      }
      else {
        **(uint **)(param_1 + 0x94) = piVar3;
        *(int **)(param_1 + 0x94) = piVar3;
      }
    }
    iVar13 = *(int *)(param_1 + 0x98); // next event node
  } while( true );
}