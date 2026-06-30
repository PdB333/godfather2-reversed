// FUNC_NAME: Sentient::evaluateCandidates
int* Sentient::evaluateCandidates(void)
{
    int iVar1;
    int in_EAX;  // implicit this: Sentient*
    int uVar2;
    int *piVar3;
    int iVar4;
    uint uVar5;
    int *piVar6;
    int *piVar7;
    int *piVar8;
    int *piVar9;
    double dVar10;
    float local_24;
    int *local_18;

    // Initialize timer or lock at +0x74 (short) to -1
    *(short *)(in_EAX + 0x74) = 0xffff;

    uVar2 = getSomeTimeValue();  // FUN_00571070 - maybe frame time or counter
    piVar3 = (int *)getTargetCandidate(in_EAX, uVar2); // FUN_00581c60 - gets initial candidate

    if (*(short *)(in_EAX + 0x74) == -1) {
        *(short *)(in_EAX + 0x74) = 0;
    }

    // Check if bit 20 of flags (+0x10) is set or no candidates available
    if (((*(uint *)(in_EAX + 0x10) >> 0x14 & 1) != 0) || (iVar4 = getNumCandidates(), iVar4 == 0)) {
        return piVar3;
    }

    piVar7 = (int *)0x0;
    local_24 = 0.0;
    uVar5 = getSomeTimeValue();  // again timestamp
    iVar4 = iVar4 + -1;  // loop count = numCandidates - 1
    piVar8 = piVar7;     // piVar8 = nullptr
    local_18 = (int *)uVar5;  // flags initially from timestamp

    if (-1 < iVar4) {
        do {
            // Compute index into circular buffer of candidates (size 0xe0 each)
            // Base at +0x2ec, count at +0x2e4, current index at +0x2e8
            int index = (((*(int *)(in_EAX + 0x2e4) - iVar4) + *(int *)(in_EAX + 0x2e8)) %
                         *(int *)(in_EAX + 0x2e4));
            piVar9 = (int *)(index * 0xe0 + *(int *)(in_EAX + 0x2ec));

            // Call virtual function at offset +0xc on the candidate object to get a node
            piVar6 = (int *)(**(code **)(*piVar9 + 0xc))();  // likely getScoreNode or similar
            piVar7 = piVar6;

            // If we have a previous best candidate and global threshold is less than current bestScore
            if ((piVar8 != (int *)0x0) && (piVar7 = piVar8, DAT_00e2b05c < local_24)) {
                if (piVar6 == (int *)0x0) {
                    local_18 = (int *)0x0;
                }
                else {
                    // Merge previous best (piVar8) with new node (piVar6) using current bestScore and flags
                    local_18 = (int *)mergeCandidateNodes(piVar8, piVar6, local_24, local_18);
                }
                // Release two references
                releaseRef();
                releaseRef();
                piVar7 = local_18;  // new best becomes merged result
            }

            // Evaluate score for current candidate
            if ((char)piVar9[0x1c] == '\0') {  // +0x70? Actually 0x1c*4 = 0x70
                local_24 = 0.0;
            }
            else {
                double d = (double)(((float)piVar9[0x1e] / (float)piVar9[0x1f]) * DAT_00e2afac - DAT_00e2a850);
                randomFunction();  // FUN_00b99fcb - maybe random factor
                local_24 = ((float)d + DAT_00e2b1a4) * DAT_00e2cd54;
            }

            // Reset flags from timestamp
            local_18 = (int *)uVar5;
            // If candidate type is 2 (offset 0x80 in structure)
            if (piVar9[0x20] == 2) {
                local_18 = (int *)(uVar5 | 0x100);  // set a flag in flags
            }

            iVar4 = iVar4 + -1;
            piVar8 = piVar7;  // previous becomes current for next iteration
        } while (-1 < iVar4);

        // After loop, if we have a best candidate and initial candidate, merge them
        if ((piVar7 != (int *)0x0) && (piVar3 != (int *)0x0)) {
            local_18 = (int *)mergeCandidateNodes(piVar7, piVar3, local_24, local_18);
            goto LAB_00578c84;
        }
    }
    local_18 = (int *)0x0;  // no best candidate

LAB_00578c84:
    iVar4 = DAT_01205568;  // global memory pool pointer

    // Decrease reference count and possibly free the node pointed to by piVar7
    if (piVar7 != (int *)0x0) {
        decrementRefCount();  // FUN_0056f4b0
        *(char *)((int)piVar7 + 9) = *(char *)((int)piVar7 + 9) + -1;
        if (((char)piVar7[2] == '\0') && (*(char *)((int)piVar7 + 9) == '\0')) {
            // Node structure: [prev(int), next(int), flags(int), refCount(char at +9)]
            iVar1 = *piVar7;          // prev
            piVar7 = (int *)piVar7[1]; // next
            if (iVar1 != 0) {
                *(int **)(iVar1 + 4) = piVar7; // list unlink
            }
            if (piVar7 == (int *)0x0) {
                // Update pool head
                *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(iVar4 + 4);
                *(int *)(iVar4 + 4) = iVar1;
                if (iVar1 == 0) {
                    *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(iVar4 + 0xc);
                }
            }
            else {
                *piVar7 = iVar1;
            }
        }
    }

    // Same for piVar3 (initial candidate)
    if (piVar3 != (int *)0x0) {
        decrementRefCount();
        *(char *)((int)piVar3 + 9) = *(char *)((int)piVar3 + 9) + -1;
        if (((char)piVar3[2] == '\0') && (*(char *)((int)piVar3 + 9) == '\0')) {
            iVar1 = *piVar3;
            piVar3 = (int *)piVar3[1];
            if (iVar1 != 0) {
                *(int **)(iVar1 + 4) = piVar3;
            }
            if (piVar3 != (int *)0x0) {
                *piVar3 = iVar1;
                return local_18;
            }
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(iVar4 + 4);
            *(int *)(iVar4 + 4) = iVar1;
            if (iVar1 == 0) {
                *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(iVar4 + 0xc);
            }
        }
    }

    return local_18;
}