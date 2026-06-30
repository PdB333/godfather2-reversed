// FUNC_NAME: AudioManager::updateActiveStreams
undefined4 __fastcall AudioManager::updateActiveStreams(AudioManager *this)
{
    int iVar1;
    int iVar2;
    int iVar3;
    uint uVar4;
    bool bVar5;
    char cVar6;
    uint uVar7;
    int *piVar8;
    uint uVar9;
    float *pStreamFloat;
    float local_20;
    int local_1c;
    float local_18 [2];
    float fStack_10;

    // pStreamFloat points to the first float of each stream structure in the array.
    // Array of 10 stream structures, each 0x5c bytes, starting at offset 0x8344.
    pStreamFloat = (float *)((int)this + 0x8344);
    local_1c = 10;
    do {
        // Check flag in the last dword of the previous stream (offset -4 from current stream)
        // Flag bits: bit 1 indicates "active" or "needs update"
        if ((((uint)*(int *)(pStreamFloat - 1)) >> 1 & 1) != 0) {
            bVar5 = true;
            // Condition: stream volume >= 0.0, some index (at streamOffset -0x98) >= -1,
            // and a pointer (at offset 0x34) is non-null (as float != 0.0)
            if (((0.0 <= *pStreamFloat) && 
                 (-1 < (int)*(int *)(pStreamFloat - 0x26))) && 
                (*(float *)(pStreamFloat + 0xd) != 0.0)) {
                local_20 = 0.0;
                // FUN_00c9cbe0: likely getSpatialAudioInfo(?, ?, ?, local_18)
                FUN_00c9cbe0(*(undefined4 *)((int)this + 0x580),
                             *(undefined4 *)(*(int *)(pStreamFloat + 0xd) + 0x10),
                             2, local_18);
                local_18[0] = *pStreamFloat;  // set target volume? 
                FUN_00c9eac0();   // push matrix or lock
                FUN_00c9cd00(0, &local_20);  // some comparison
                if (local_20 < *pStreamFloat) {
LAB_005ee453:
                    bVar5 = false;
                }
                else if (local_20 == *pStreamFloat) {
                    FUN_00c9cd40(2, local_18);
                    if (fStack_10 == DAT_00e2b05c) goto LAB_005ee453;
                }
                FUN_00c9eae0();   // pop matrix or unlock
                if (!bVar5) goto LAB_005ee48a;
            }
            if (-1 < (int)*(int *)(pStreamFloat - 0x26)) {
                // Decrement a counter associated with this stream's index
                piVar8 = (int *)((int)*(int *)(pStreamFloat - 0x26) * 0x10 + 0x81bc + (int)this);
                LOCK();
                *piVar8 = *piVar8 + -1;
                UNLOCK();
            }
            // FUN_005ea0d0: cleanup or release resources for this stream
            FUN_005ea0d0();
        }
LAB_005ee48a:
        pStreamFloat = pStreamFloat + 0x5c / 4;  // move to next stream (0x5c bytes)
        local_1c = local_1c + -1;
        if (local_1c == 0) {
            // After processing all 10 streams, clean up any completed entries
            if ((*(int *)((int)this + 0x580) != 0) && (*(int *)((int)this + 0x81a4) != 0)) {
                uVar9 = 0;
                FUN_00c9eac0();   // lock
                if (*(int *)((int)this + 0x81a4) != 0) {
                    do {
                        // array at 0x81a0: pairs of ints, length at 0x81a4
                        iVar1 = uVar9 * 8;
                        cVar6 = FUN_00c9eb10(*(undefined4 *)(*(int *)((int)this + 0x81a0) + 4 + iVar1));
                        if (cVar6 == '\0') {
                            uVar9 = uVar9 + 1;
                        }
                        else {
                            // Swap with last element and decrement count
                            iVar2 = *(int *)((int)this + 0x81a4);
                            if (uVar9 != iVar2 - 1U) {
                                iVar3 = *(int *)((int)this + 0x81a0);
                                *(undefined4 *)(iVar3 + iVar1) = *(undefined4 *)(iVar3 + -8 + iVar2 * 8);
                                *(undefined4 *)(iVar3 + 4 + iVar1) = *(undefined4 *)(iVar3 + -4 + iVar2 * 8);
                            }
                            *(int *)((int)this + 0x81a4) = *(int *)((int)this + 0x81a4) + -1;
                        }
                    } while (uVar9 < *(uint *)((int)this + 0x81a4));
                }
                FUN_00c9eae0();   // unlock
            }
            // Another cleanup for a different list (function pointers at 0x81ac, count at 0x81b0)
            if ((*(int *)((int)this + 0x81b0) != 0) && (uVar9 = 0, *(int *)((int)this + 0x81b0) != 0)) {
                do {
                    uVar4 = *(uint *)((int)this + 0x81a4);
                    if ((uVar4 != 0) && (uVar7 = 0, uVar4 != 0)) {
                        piVar8 = *(int **)((int)this + 0x81a0);
                        do {
                            if (*piVar8 == *(int *)(*(int *)((int)this + 0x81ac) + uVar9 * 4)) {
                                uVar9 = uVar9 + 1;
                                goto LAB_005ee5a0;
                            }
                            uVar7 = uVar7 + 1;
                            piVar8 = piVar8 + 2;
                        } while (uVar7 < uVar4);
                    }
                    // If not found in first list, call callback at 0x81b8 and remove from second list
                    if (*(code **)((int)this + 0x81b8) != (code *)0x0) {
                        (**(code **)((int)this + 0x81b8))(*(undefined4 *)(*(int *)((int)this + 0x81ac) + uVar9 * 4));
                    }
                    if (uVar9 != *(int *)((int)this + 0x81b0) - 1U) {
                        *(undefined4 *)(*(int *)((int)this + 0x81ac) + uVar9 * 4) =
                             *(undefined4 *)(*(int *)((int)this + 0x81ac) + -4 + *(int *)((int)this + 0x81b0) * 4);
                    }
                    *(int *)((int)this + 0x81b0) = *(int *)((int)this + 0x81b0) + -1;
LAB_005ee5a0:
                } while (uVar9 < *(uint *)((int)this + 0x81b0));
            }
            // Remove from four different lists (callbacks for destroyed objects)
            FUN_005ebfa0(this, *(undefined4 *)((int)this + 0x454), (int)this + 0x428);
            FUN_005ebfa0(this, *(undefined4 *)((int)this + 0x3c4), (int)this + 0x398);
            FUN_005ebfa0(this, *(undefined4 *)((int)this + 0x3f4), (int)this + 0x3c8);
            FUN_005ebfa0(this, *(undefined4 *)((int)this + 0x424), (int)this + 0x3f8);
            return 1;
        }
    } while( true );
}