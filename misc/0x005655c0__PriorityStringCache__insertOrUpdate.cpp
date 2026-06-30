// FUNC_NAME: PriorityStringCache::insertOrUpdate
// Function address: 0x005655c0
// Role: Manages a small fixed-size cache (5 slots) of prioritized strings. 
// Each slot has a 128-byte string buffer (offset 0x00) and a 4-byte priority value (offset 0x80).
// The function inserts or updates a string, adjusting priorities and notifying external systems.

undefined4 PriorityStringCache::insertOrUpdate(byte* inputString, undefined4 param2) {
    int* piVar8;
    byte bVar2;
    int in_EAX; // this pointer from __thiscall
    byte* pbVar3;
    int iVar4;
    uint uVar5;
    byte* pbVar6;
    int iVar7;
    int* piLocalVar;
    bool bVar9;
    int maxPriority = -1;
    int slotIndex = 0;
    int local_28;
    code* successCallback;
    int aiStack_18[3];
    code* failureCallback;

    // Normalize the input string (e.g., strip whitespace)
    FUN_004d3bc0(inputString); // likely normalizeString

    piVar8 = (int*)(in_EAX + 700);   // Points to priority value of first slot (offset 0x80)
    iVar7 = 0;                       // current slot index
    do {
        // Get string pointer (slot start = piVar8 - 0x20 ints = piVar8 - 0x80 bytes)
        pbVar3 = (byte*)(piVar8 - 0x20);
        pbVar6 = inputString;

        // Compare strings byte-by-byte (manual strcmp)
        do {
            bVar2 = *pbVar3;
            bVar9 = bVar2 < *pbVar6;
            if (bVar2 != *pbVar6) {
                // Result: -1, 0, or 1
                iVar4 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
                goto LAB_0056561c;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar3[1];
            bVar9 = bVar2 < pbVar6[1];
            if (bVar2 != pbVar6[1]) goto LAB_00565617;
            pbVar3 = pbVar3 + 2;
            pbVar6 = pbVar6 + 2;
        } while (bVar2 != 0);
        iVar4 = 0;

LAB_0056561c:
        if (iVar4 == 0) { // Match found
            iVar7 = *piVar8; // Current priority of this slot

            // Update various internal counters if their associated flags are set
            // +0x23c, +0x2c0, +0x344, +0x3c8, +0x44c are boolean flags
            // +0x700, +0x340, +0x3c4, +0x448, +0x4cc are counters
            if (*(char*)(in_EAX + 0x23c) != '\0' && *(int*)(in_EAX + 700) < iVar7) {
                *(int*)(in_EAX + 700) += 1;
            }
            if (*(char*)(in_EAX + 0x2c0) != '\0' && *(int*)(in_EAX + 0x340) < iVar7) {
                *(int*)(in_EAX + 0x340) += 1;
            }
            if (*(char*)(in_EAX + 0x344) != '\0' && *(int*)(in_EAX + 0x3c4) < iVar7) {
                *(int*)(in_EAX + 0x3c4) += 1;
            }
            if (*(char*)(in_EAX + 0x3c8) != '\0' && *(int*)(in_EAX + 0x448) < iVar7) {
                *(int*)(in_EAX + 0x448) += 1;
            }
            if (*(char*)(in_EAX + 0x44c) != '\0' && *(int*)(in_EAX + 0x4cc) < iVar7) {
                *(int*)(in_EAX + 0x4cc) += 1;
            }

            *piVar8 = 0; // Clear priority of this slot

            // Check associated external manager (+0x20) for existence via FUN_00569bf0
            if (*(int*)(in_EAX + 0x20) != 0) {
                iVar7 = FUN_00569bf0(*(int*)(in_EAX + 0x20), inputString, 0);
                if (iVar7 != 2) goto LAB_00565834; // If not "duplicate", skip priority update
            }

            *piVar8 = 0xF; // Set priority to 15 (highest)
            maxPriority = 0xF;
            iVar7 = slotIndex;
            goto LAB_00565721;
        }

        // Track maximum priority among remaining slots
        if (maxPriority < *piVar8) {
            iVar7 = slotIndex;
            maxPriority = *piVar8;
        }

        slotIndex++;
        piVar8 += 0x21; // Move to next slot (0x84 bytes as int*)
        if (slotIndex > 4) { // All slots scanned, no match found
            // Use slot with highest priority (or last if none)
            // iVar7 already set to index of max priority slot
            goto LAB_00565721;
        }
    } while (true);

LAB_00565721:
    // iVar7 is the slot index to use (either matched or evicted)
    iVar7 = iVar7 * 0x84 + in_EAX; // Base address of the slot

    // Clear existing string at this slot
    if (*(char*)(iVar7 + 0x23c) != '\0') { // +0x23c seems to be another string field? Wait, that's inside the slot? Actually iVar7 is slot base, so +0x23c would be far into next slot? This doesn't align. Probably a bug in decompilation, but we keep as is.
        FUN_00565870((char*)(iVar7 + 0x23c)); // clearString
    }
    _strncpy((char*)(iVar7 + 0x23c), (char*)inputString, 0x80); // Copy new string

    // Update global counters again (same pattern as above) with the maxPriority
    if (*(char*)(in_EAX + 0x23c) != '\0' && *(int*)(in_EAX + 700) < maxPriority) {
        *(int*)(in_EAX + 700) += 1;
    }
    if (*(char*)(in_EAX + 0x2c0) != '\0' && *(int*)(in_EAX + 0x340) < maxPriority) {
        *(int*)(in_EAX + 0x340) += 1;
    }
    if (*(char*)(in_EAX + 0x344) != '\0' && *(int*)(in_EAX + 0x3c4) < maxPriority) {
        *(int*)(in_EAX + 0x3c4) += 1;
    }
    if (*(char*)(in_EAX + 0x3c8) != '\0' && *(int*)(in_EAX + 0x448) < maxPriority) {
        *(int*)(in_EAX + 0x448) += 1;
    }
    if (*(char*)(in_EAX + 0x44c) != '\0' && *(int*)(in_EAX + 0x4cc) < maxPriority) {
        *(int*)(in_EAX + 0x4cc) += 1;
    }

    // Set the priority for this slot to 0 (initial)
    *(undefined4*)(iVar7 + 700) = 0; // Note: +700 would be off by 0x84? Actually iVar7 is relative to in_EAX, so +700 is in global space. This is likely a mistake; probably should be *(undefined4*)(iVar7 + 0x80). But original code: iVar7 = iVar7 * 0x84 + in_EAX; then *(undefined4 *)(iVar7 + 700) = 0; That would be iVar7 + 700 = in_EAX + 700 + iVar7*0x84. That's clearly wrong because 700 is a large offset. Perhaps the decompiler misinterpreted the base. I'll keep as per original but comment.

    // Call external evaluation function (+0x20) to check if name is valid
    uVar5 = FUN_00569940(*(undefined4*)(in_EAX + 0x20), inputString, param2);
    if ((uVar5 & 1) == 0) {
        // Failure path
        if (local_28 != 0) {
            (*successCallback)(local_28);
        }
        return 0;
    }

    // Success: call virtual function through vtable (+0x128)
    (**(code**)*(undefined4**)(in_EAX + 0x128))(inputString);

    // Additional processing
    FUN_004d3bc0(inputString);
    FUN_005699f0(*(undefined4*)(in_EAX + 0x20), aiStack_18);
    if (aiStack_18[0] != 0) {
        (*failureCallback)(aiStack_18[0]);
    }

LAB_00565834:
    if (local_28 != 0) {
        (*successCallback)(local_28);
    }
    return 1;
}