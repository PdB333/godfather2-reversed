// FUNC_NAME: NavPathfinder::expandNode
// Address: 0x005f8520
// Role: Single iteration of A* pathfinding expansion. Processes one node from the open list and expands its neighbors.

void NavPathfinder::expandNode(uint maxIterations)
{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  float *pfVar9;
  bool bVar10;
  int *openNodePtr; // local_4c
  int goalData; // local_48
  undefined4 startData; // local_44
  int neighborListIdx; // local_40
  uint iteration; // local_3c
  float fVar11; // local_30
  uint neighborCount; // local_2c
  float fVar12; // fStack_28
  int iVar13; // local_24
  uint uVar14; // local_20
  int iVar15; // local_1c
  int iVar16; // local_18
  int iVar17; // iStack_14
  int iVar18; // iStack_10

  iteration = 0;
  if ((*(uint *)(this + 0x20) & 1) != 0) {
    maxIterations = 0xffffffff;
  }
  iVar16 = DAT_01223520; // global memory pool
  if (*(int *)(this + 8) == 0) {
    *(uint *)(this + 0x38) |= 0x204;
    startData = 0;
  }
  else {
    startData = *(undefined4 *)(this + 0x10);
  }
  iVar13 = *(int *)(this + 0x14); // goal node index
  if (iVar13 == 0) {
    *(uint *)(this + 0x38) |= 0x404;
    goalData = 0;
  }
  else {
    goalData = *(int *)(this + 0x1c);
  }
  openNodePtr = *(int **)(this + 0x30);
  if ((*(int *)(this + 0x38) == 0) && (openNodePtr == (int *)0x0)) {
    openNodePtr = (int *)allocateOpenNode(this, *(int *)(this + 8), startData, iVar13, goalData);
  }
  if (*(int *)(this + 0x38) == 0) {
    if (((openNodePtr != (int *)0x0) && (*(int *)(this + 0x28) == 0)) &&
       (iVar6 = isStartNodeValid(startData), iVar6 != 0)) {
      initializeExpansion();
    }
    if (*(int *)(this + 0x38) == 0) {
      do {
        if ((*openNodePtr == 0) || (maxIterations <= iteration)) break;
        iteration++;
        iVar7 = popNextNode(&iVar15); // iVar7 = current node address
        bVar5 = *(byte *)(iVar7 + 0xb); // node type or index
        iVar6 = *(int *)(*(int *)(this + 0x24) + (uint)bVar5 * 0xc); // pointer to graph data for this layer
        piVar8 = (int *)(*(int *)(this + 0x24) + (uint)bVar5 * 0xc);
        if (iVar6 != 0) {
          iVar1 = *(int *)(iVar6 + 0x20) + ((iVar7 - piVar8[2]) / 0xc) * 0x24;
          *(int *)(this + 0x34) = iVar7; // current node
          if ((iVar1 == goalData) && (iVar6 == iVar13)) {
            *(uint *)(this + 0x38) |= 1; // path found
          }
          else if (*(float *)(iVar7 + 4) <= *(float *)(this + 0x3c)) {
            // Expand primary neighbors
            uVar14 = (uint)*(byte *)(iVar1 + 0x14); // count of primary neighbors
            iVar2 = *(int *)(this + 0x38);
            for (neighborCount = 0; (iVar2 == 0 && ((int)neighborCount < (int)uVar14));
                neighborCount++) {
              pfVar9 = (float *)((uint)(ushort)(*(short *)(iVar1 + 0x10) + (short)neighborCount) * 0x10 +
                                *(int *)(iVar6 + 0x24)); // pointer to neighbor entry (16 bytes)
              fVar11 = 0.0;
              if (*(int **)(this + 0x44) == (int *)0x0) {
                cVar4 = (*(uint *)(this + 0x4c) & (uint)*(ushort *)((int)pfVar9 + 10)) == 0;
              }
              else {
                cVar4 = (**(code **)(**(int **)(this + 0x44) + 4))(pfVar9, iVar6, &fVar11);
              }
              if (cVar4 != '\0') {
                iVar2 = *(int *)(iVar6 + 0x20) + (uint)*(ushort *)(pfVar9 + 1) * 0x24; // target node data address
                if ((*(int **)(this + 0x44) == (int *)0x0) || (iVar2 == 0)) {
                  if ((*(ushort *)(this + 0x48) & *(ushort *)(iVar2 + 0x18)) != 0) {
                    bVar10 = (*(uint *)(this + 0x20) & 0x800) == 0;
                    goto LAB_005f875e;
                  }
                }
                else {
                  cVar4 = (**(code **)(**(int **)(this + 0x44) + 0xc))(iVar2, iVar6);
                  bVar10 = cVar4 == '\0';
LAB_005f875e:
                  if (bVar10) goto LAB_005f87bc;
                }
                iVar2 = piVar8[2] + ((iVar2 - *(int *)(*piVar8 + 0x20)) / 0x24) * 0xc;
                *(byte *)(iVar2 + 0xb) = bVar5; // store back pointer to layer
                cVar4 = addNodeToPathTree(iVar7, iVar2, *pfVar9 + fVar11, openNodePtr);
                if (cVar4 == '\0') {
                  *(uint *)(this + 0x38) |= 0x24; // error flags
                }
              }
LAB_005f87bc:
              iVar2 = *(int *)(this + 0x38);
            }
            // Expand secondary neighbors if allowed
            if ((*(byte *)(this + 0x20) & 4) == 0) {
              uVar14 = (uint)*(byte *)(iVar1 + 0x1c) + (uint)*(byte *)(iVar1 + 0x15); // count of secondary neighbors
              iVar2 = *(int *)(this + 0x38);
              for (neighborCount = 0; (iVar2 == 0 && (neighborCount < uVar14)); neighborCount++) {
                pfVar9 = (float *)((uint)(ushort)(*(short *)(iVar1 + 0x16) + (short)neighborCount) * 0x10
                                  + *(int *)(iVar6 + 0x30)); // secondary neighbor list
                fVar12 = 0.0;
                if (*(int **)(this + 0x44) == (int *)0x0) {
                  cVar4 = (*(uint *)(this + 0x4c) & (uint)*(ushort *)((int)pfVar9 + 10)) == 0;
                }
                else {
                  cVar4 = (**(code **)(**(int **)(this + 0x44) + 8))(pfVar9, iVar6, &fVar12);
                }
                if (cVar4 != '\0') {
                  piVar8 = (int *)extractNeighborList(&iVar17, pfVar9);
                  iVar15 = *piVar8;
                  if (iVar15 == 0) {
                    neighborListIdx = 0;
                  }
                  else {
                    neighborListIdx = piVar8[2];
                  }
                  if (iVar17 != 0) {
                    piVar8 = *(int **)(iVar17 + 4);
                    if (piVar8 == &iVar17) {
                      *(int *)(iVar17 + 4) = iVar18;
                    }
                    else {
                      if ((int *)piVar8[1] != &iVar17) {
                        do {
                          piVar8 = (int *)piVar8[1];
                        } while ((int *)piVar8[1] != &iVar17);
                      }
                      piVar8[1] = iVar18;
                    }
                  }
                  if ((iVar15 != 0) &&
                     (((((*(ushort *)(this + 0x48) & *(ushort *)(neighborListIdx + 0x18)) == 0 ||
                        ((*(uint *)(this + 0x20) & 0x800) != 0)) &&
                       (bVar5 = allocateCell(), bVar5 != 0xff)) &&
                      (piVar8 = (int *)(*(int *)(this + 0x24) + (uint)bVar5 * 0xc),
                      piVar8 != (int *)0x0)))) {
                    iVar2 = piVar8[2] + ((neighborListIdx - *(int *)(*piVar8 + 0x20)) / 0x24) * 0xc;
                    *(byte *)(iVar2 + 0xb) = bVar5;
                    cVar4 = addNodeToPathTree(iVar7, iVar2, *pfVar9 + fVar12, openNodePtr);
                    if (cVar4 == '\0') {
                      *(uint *)(this + 0x38) |= 0x24;
                    }
                  }
                }
                iVar2 = *(int *)(this + 0x38);
              }
            }
          }
        }
        *(byte *)(iVar7 + 10) |= 2; // mark node as closed/visited
      } while (*(int *)(this + 0x38) == 0);
      if (*(int *)(this + 0x38) == 0) {
        if ((openNodePtr != (int *)0x0) && (*openNodePtr == 0)) {
          *(undefined4 *)(this + 0x38) = 2; // no path
        }
        if (*(int *)(this + 0x38) == 0) goto LAB_005f8a03;
      }
    }
  }
  if (openNodePtr != (int *)0x0) {
    *openNodePtr = 0;
    puVar3 = *(undefined4 **)(iVar16 + 0x30); // global pool
    piVar8 = (int *)*puVar3;
    if (piVar8 != (int *)0x0) {
      if (((int *)puVar3[7] == (int *)0x0) ||
         ((piVar8 <= openNodePtr && (openNodePtr < (int *)(puVar3[1] + (int)piVar8))))) {
        *openNodePtr = puVar3[2];
        puVar3[5] = puVar3[5] + 1;
        puVar3[2] = openNodePtr;
      }
      else {
        (**(code **)(*(int *)puVar3[7] + 8))(openNodePtr);
      }
    }
    *(undefined4 *)(this + 0x30) = 0;
  }
LAB_005f8a03:
  *(int *)(this + 0x40) += iteration; // accumulate iterations
  return;
}