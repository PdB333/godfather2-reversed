// FUNC_NAME: GhostManager::buildGhostPacket
void __thiscall GhostManager::buildGhostPacket(int ghostManager, uint bitstream, int outputList) {
    undefined4 *puVar1;
    int index;
    char cVar3;
    byte byteVar;
    undefined4 uVar5;
    int iVar6;
    int iVar7;
    uint *puVar8;
    void *pvVar9;
    byte *pbVar10;
    byte bVar11;
    uint uVar12;
    float10 fVar13;
    uint local_18;
    uint local_14;
    uint local_10;
    uint *local_c; // linked list of pending ghosts (head)
    int local_8;
    uint local_4;

    // this+0x7f = ghostList array pointer
    // this+0x80 = ghostCount
    // this+0x66 = debugFlag

    // Initialize the bitstream
    FUN_0064e6a0(bitstream, outputList); // probably a lock or init

    if ((char)ghostManager[0x66] != '\0') {
        // debug: write a sync marker? param_2 = 0x00FFB4AD? Actually -0xff24553 = 0x00FFB4AD? Let's compute: -0xff24553 = 0xFF00BAAF? No, it's unsigned: 0xFF00BAAF? Better to just note it's a debug marker.
        param_2 = 0xFF00BAAE; // corrected value? The code uses -0xff24553 which is 0xFF00BAAE? Wait: -0xff24553 = -26719315 -> 0xFE00BAAD? Not sure. Let's just name it DEBUG_MARKER.
        FUN_0064b810(32, &param_2); // write 32 bits of marker
    }

    *(undefined4 *)(outputList + 0x18) = 0; // clear output head pointer

    if (ghostManager[0x7f] == 0) return; // no ghosts

    // Determine updateType (0 or 1) based on flags
    if (((char)ghostManager[0x82] == '\0') || (ghostManager[0x87] == 0)) {
        uVar5 = 0; // normal update
    } else {
        uVar5 = 1; // forced/delta update
    }

    cVar3 = FUN_0064bb50(uVar5); // check if we can pack this type
    if (cVar3 == '\0') return;

    // Clear "dirty" flags? Loop over ghosts
    param_2 = ghostManager[0x80]; // count
    while (param_2 = param_2 + -1, -1 < (int)param_2) {
        if ((*(byte *)(*(int *)(ghostManager[0x7f] + param_2 * 4) + 0x20) & 1) == 0) {
            FUN_006501f0(); // probably clear something
        }
    }

    // First pass: compute priorities and handle special cases
    param_2 = 0;
    local_c = (uint *)ghostManager[0x80]; // reuse local_c as count iterator
    while (index = (int)local_c + -1, -1 < index) {
        puVar1 = *(undefined4 **)(ghostManager[0x7f] + index * 4);
        if (param_2 < (uint)puVar1[10]) {
            param_2 = puVar1[10]; // track max index? puVar1[10] might be ghostID
        }
        uVar12 = puVar1[8]; // flags
        local_c = (uint *)index;
        if (((uVar12 & 0x10) == 0) || ((uVar12 & 4) == 0)) {
            if ((uVar12 & 0x28) == 0) {
                uVar5 = DAT_00e44658; // some global priority constant?
                if ((uVar12 & 0x10) != 0) goto LAB_0064faf7;
                // Compute priority using a virtual function (vtable+0x1c)
                fVar13 = (float10)(**(code **)(*(int *)*puVar1 + 0x1c))(ghostManager[0x87], puVar1[1], puVar1[7]);
                puVar1[9] = (float)fVar13;
            } else {
                uVar5 = 0;
LAB_0064faf7:
                puVar1[9] = uVar5; // set priority to constant (0 or DAT_...)
            }
        } else {
            // Ghost has both 0x10 and 0x04 flags set? Special handling
            if ((puVar1[0xb] != 0x400) && ((int)puVar1[0xb] < ghostManager[0x80])) {
                puVar1[1] = 0;
                FUN_0064d500(); // something
            }
            FUN_0064f390(); // more processing
            local_c = (uint *)index;
        }
    }

    // Sort ghosts? (pointer check)
    local_c = (uint *)0x0;
    if (ghostManager[0x7f] != ghostManager[0x7f] + ghostManager[0x80] * 4) {
        FUN_00651450(); // sort or reorder
    }

    // Set each ghost's index within array (+0x2c)
    index = ghostManager[0x80];
    while (index = index + -1, -1 < index) {
        *(int *)(*(int *)(ghostManager[0x7f] + index * 4) + 0x2c) = index;
    }

    // Compute number of bits needed to encode max index (param_2)
    param_2 = param_2 >> 1;
    local_18 = 1;
    if (param_2 == 0) {
LAB_0064fb70:
        local_18 = 3; // at least 3 bits? actually base bits for ghost index
    } else {
        do {
            local_18 = local_18 + 1;
            param_2 = param_2 >> 1;
        } while (param_2 != 0);
        if ((int)local_18 < 3) goto LAB_0064fb70;
    }

    param_2 = local_18 - 3; // extra bits beyond base 3
    FUN_0064b810(3, &param_2); // write the extra bits count (3 bits)

    local_8 = ghostManager[0x80];
    uVar12 = local_4;
    while (local_8 = local_8 + -1, -1 < local_8) {
        local_4 = *(uint *)(bitstream + 0x18); // current bit offset
        if (*(uint *)(bitstream + 0x10) * 8 < local_4) break; // overflow?
        puVar1 = *(undefined4 **)(ghostManager[0x7f] + local_8 * 4);
        if ((*(byte *)(puVar1 + 8) & 0x28) == 0) { // not special flags
            local_10 = puVar1[1]; // ghostID
            local_14 = 0;
            // Write a bit indicating "this ghost is present" (1 bit)
            if (*(uint *)(bitstream + 0x30) < local_4 + 1) {
                // Need to reallocate buffer
                uVar12 = (*(uint *)(bitstream + 0x30) + 8 >> 3) + 0x5dc;
                if (*(uint *)(bitstream + 0x10) < uVar12) {
                    if (*(char *)(bitstream + 0x14) != '\0') {
                        *(uint *)(bitstream + 0x10) = uVar12;
                        pvVar9 = _realloc(*(void **)(bitstream + 0xc), uVar12);
                        *(void **)(bitstream + 0xc) = pvVar9;
                        *(uint *)(bitstream + 0x2c) = uVar12 * 8;
                        *(uint *)(bitstream + 0x30) = uVar12 * 8;
                        goto LAB_0064fc33;
                    }
                } else {
                    *(uint *)(bitstream + 0x10) = uVar12;
                }
                *(undefined1 *)(bitstream + 0x1c) = 1; // overflow flag
            } else {
LAB_0064fc33:
                pbVar10 = (byte *)((*(uint *)(bitstream + 0x18) >> 3) + *(int *)(bitstream + 0xc));
                *pbVar10 = *pbVar10 | '\x01' << ((byte)*(uint *)(bitstream + 0x18) & 7);
                *(int *)(bitstream + 0x18) = *(int *)(bitstream + 0x18) + 1;
            }
            // Write the ghost index using local_18 bits
            param_2 = puVar1[10]; // ghostID
            FUN_0064b810(local_18 & 0xff, &param_2);
            // Determine update type (1 bit) from flag bit 4
            byteVar = (byte)((uint)puVar1[8] >> 4);
            param_2 = CONCAT31(param_2._1_3_, byteVar) & 0xffffff01; // combine? Actually this is messy. Might be storing bit for "has delta?"
            byteVar = byteVar & 1;
            // Write the 1-bit update type
            if (*(uint *)(bitstream + 0x30) < *(int *)(bitstream + 0x18) + 1U) {
                // realloc again
                uVar12 = (*(uint *)(bitstream + 0x30) + 8 >> 3) + 0x5dc;
                if (*(uint *)(bitstream + 0x10) < uVar12) {
                    if (*(char *)(bitstream + 0x14) != '\0') {
                        *(uint *)(bitstream + 0x10) = uVar12;
                        pvVar9 = _realloc(*(void **)(bitstream + 0xc), uVar12);
                        *(void **)(bitstream + 0xc) = pvVar9;
                        *(uint *)(bitstream + 0x2c) = uVar12 * 8;
                        *(uint *)(bitstream + 0x30) = uVar12 * 8;
                        byteVar = (byte)param_2;
                        goto LAB_0064fcc3;
                    }
                } else {
                    *(uint *)(bitstream + 0x10) = uVar12;
                }
                *(undefined1 *)(bitstream + 0x1c) = 1;
LAB_0064fcef:
                // If debug flag set, add 16 pad bits? 
                if ((char)ghostManager[0x66] != '\0') {
                    *(int *)(bitstream + 0x18) = *(int *)(bitstream + 0x18) + 0x10;
                }
                param_2 = *(uint *)(bitstream + 0x18);
                // If ghost has 0x04 flag (delta), write custom update
                if ((*(byte *)(puVar1 + 8) & 4) != 0) {
                    iVar6 = (**(code **)(*ghostManager + 0x50))(); // get some index
                    iVar7 = (*(code *)**(undefined4 **)*puVar1)(); // vtable call
                    uVar12 = *(uint *)(iVar7 + 0x10 + iVar6 * 4);
                    iVar6 = (**(code **)(*ghostManager + 0x50))();
                    local_14 = uVar12;
                    // Write a known table value
                    FUN_0064b810((&DAT_012059f0)[iVar6 * 0xc], &local_14);
                    DAT_0120588b = '\x01'; // set flag for delta stats tracking
                }
                // Call ghost->packUpdate (vtable+0x20)
                (**(code **)(*(int *)*puVar1 + 0x20))(ghostManager, local_10, bitstream);
                iVar6 = *(int *)(bitstream + 0x18);
                // Update statistics
                if (DAT_0120588b == '\0') {
                    iVar7 = (*(code *)**(undefined4 **)*puVar1)();
                    *(int *)(iVar7 + 0x6c) = *(int *)(iVar7 + 0x6c) + 1;
                    *(int *)(iVar7 + 100) = *(int *)(iVar7 + 100) + (iVar6 - param_2);
                } else {
                    DAT_0120588b = '\0';
                    iVar7 = (*(code *)**(undefined4 **)*puVar1)();
                    *(int *)(iVar7 + 0x68) = *(int *)(iVar7 + 0x68) + 1;
                    *(int *)(iVar7 + 0x60) = *(int *)(iVar7 + 0x60) + (iVar6 - param_2);
                }
                // More debug padding
                if ((char)ghostManager[0x66] != '\0') {
                    uVar12 = *(uint *)(bitstream + 0x18);
                    *(uint *)(bitstream + 0x18) = param_2 - 0x10;
                    param_2 = uVar12;
                    FUN_0064b810(0x10, &param_2);
                    *(uint *)(bitstream + 0x18) = uVar12;
                }
            } else {
LAB_0064fcc3:
                // Write the 1-bit delta flag
                pbVar10 = (byte *)(*(int *)(bitstream + 0xc) + (*(uint *)(bitstream + 0x18) >> 3));
                bVar11 = '\x01' << ((byte)*(uint *)(bitstream + 0x18) & 7);
                if (byteVar == 0) {
                    *pbVar10 = *pbVar10 & ~bVar11;
                } else {
                    *pbVar10 = *pbVar10 | bVar11;
                }
                *(int *)(bitstream + 0x18) = *(int *)(bitstream + 0x18) + 1;
                if (byteVar == 0) goto LAB_0064fcef;
            }
            // Check if buffer is almost full (< 128 bits left)
            if ((uint)(*(int *)(bitstream + 0x30) - *(int *)(bitstream + 0x18)) < 0x80) {
                *(uint *)(bitstream + 0x18) = local_4; // restore bit offset? Actually rollback?
                *(undefined1 *)(bitstream + 0x1c) = 0;
                uVar12 = local_4;
                break;
            }
            // Allocate a pending ghost node (0x14 bytes)
            puVar8 = (uint *)FUN_009c8e50(0x14);
            puVar8[3] = (uint)local_c; // next pointer (linked list)
            if (puVar1[2] != 0) {
                *(uint **)(puVar1[2] + 0x10) = puVar8;
            }
            puVar1[2] = puVar8; // ghost's link to this node
            puVar8[2] = (uint)puVar1; // back pointer to ghost
            puVar8[1] = 0;
            puVar8[4] = 0;
            uVar12 = puVar1[8];
            local_c = puVar8; // update list head
            if ((uVar12 & 0x10) == 0) {
                if ((uVar12 & 4) != 0) {
                    puVar1[8] = uVar12 & 0xfffffffb | 8; // set flag 8, clear 4
                    puVar8[1] = 8;
                }
                puVar1[1] = local_14; // store delta data
                if (local_14 == 0) {
                    FUN_0064d500(); // handle zero
                }
                *puVar8 = ~local_14 & local_10; // some bitmask
                puVar1[7] = 0;
                uVar12 = local_4;
            } else {
                puVar1[1] = 0;
                puVar1[8] = uVar12 & 0xffffffef | 0x20; // set flag 0x20, clear 0x10
                *puVar8 = local_10;
                FUN_0064d500();
                puVar8[1] = 0x20;
                uVar12 = local_4;
            }
        }
    }
    local_4 = uVar12;
    // Write a terminating zero bit at end
    if (*(int *)(bitstream + 0x18) + 1U <= *(uint *)(bitstream + 0x30)) {
LAB_0064fee2:
        pbVar10 = (byte *)(*(int *)(bitstream + 0xc) + (*(uint *)(bitstream + 0x18) >> 3));
        *pbVar10 = *pbVar10 & ~('\x01' << ((byte)*(uint *)(bitstream + 0x18) & 7));
        *(int *)(bitstream + 0x18) = *(int *)(bitstream + 0x18) + 1;
        *(uint **)(outputList + 0x18) = local_c; // store head of pending list
        return;
    }
    // Realloc if needed
    uVar12 = (*(uint *)(bitstream + 0x30) + 8 >> 3) + 0x5dc;
    if (*(uint *)(bitstream + 0x10) < uVar12) {
        if (*(char *)(bitstream + 0x14) != '\0') {
            *(uint *)(bitstream + 0x10) = uVar12;
            pvVar9 = _realloc(*(void **)(bitstream + 0xc), uVar12);
            *(void **)(bitstream + 0xc) = pvVar9;
            *(uint *)(bitstream + 0x2c) = uVar12 * 8;
            *(uint *)(bitstream + 0x30) = uVar12 * 8;
            goto LAB_0064fee2;
        }
    } else {
        *(uint *)(bitstream + 0x10) = uVar12;
    }
    *(undefined1 *)(bitstream + 0x1c) = 1;
    *(uint **)(outputList + 0x18) = local_c;
    return;
}