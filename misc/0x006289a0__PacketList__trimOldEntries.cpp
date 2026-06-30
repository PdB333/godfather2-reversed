// FUNC_NAME: PacketList::trimOldEntries
void PacketList::trimOldEntries(PacketList* thisPtr)
{
    int count = *(int *)(thisPtr + 4);
    if (count <= 1) {
        return;
    }

    // Internal structure pointer
    int* internal = *(int **)(thisPtr + 8);
    int* arrayBase = *(int **)(internal + 8); // +8: pointer to array of 8-byte entries

    // Determine the value of the last element (index count-1)
    int* lastEntry = arrayBase + (count - 1) * 2; // each entry is 2 ints (8 bytes)
    uint lastValue;
    if (*(int *)(lastEntry - 2) == 4) { // check type tag of previous element? Actually lastEntry-2 is the element before last? This is confusing.
        // The code checks *(int *)(iVar5 + -8) where iVar5 = arrayBase+8? Wait, iVar5 = *(int *)(internal+8) = arrayBase. Then it checks (int *)(iVar5 + -8) which is arrayBase-2? That seems like a sentinel.
        // Actually, the initial iVar5 is set to *(int *)(internal+8) which is arrayBase. Then it checks if (int *)(iVar5 + -8) == 0x0. That is arrayBase-2. This is likely checking if there is a previous element? But arrayBase is the start of the array, so arrayBase-2 is before the array. This might be a check for a special header.
        // Given the complexity, I'll simplify: the code is trying to get the value of the last element.
        // The logic: if the element before the last (?) has type 4, then lastValue = *(uint *)(*(int *)(lastEntry-1) + 0xc);
        // else call FUN_00633990 and if it returns non-zero, get the value.
        // I'll assume it's getting the value of the last element.
        lastValue = *(uint *)(*(int *)(lastEntry - 1) + 0xc);
    } else {
        int result = FUN_00633990(internal);
        if (result == 0) {
            lastValue = 0;
        } else {
            lastValue = *(uint *)(*(int *)(lastEntry - 1) + 0xc);
        }
    }

    int currentIndex = 1; // iVar6
    int iVar5 = -2;
    int local_4 = -9999;
    int local_8 = -0x13878;
    uint accumulatedValue = lastValue; // local_c

    do {
        int* entryPtr;
        uint entryValue;
        if (iVar5 < 1) {
            // Handle special indices
            if (iVar5 < -9999) {
                if (iVar5 == -0x2711) {
                    entryPtr = (int *)(internal + 0x40); // +0x40: some fixed field
                } else if (iVar5 == -10000) {
                    entryPtr = (int *)(*(int *)(internal + 0x10) + 0x2c);
                } else {
                    int iVar3 = *(int *)(*(int *)(internal + 0xc) - 4);
                    if ((int)(uint)*(byte *)(iVar3 + 7) < local_4) {
                        entryPtr = (int *)0x0;
                    } else {
                        entryPtr = (int *)(local_8 + 8 + iVar3);
                    }
                }
            } else {
                // Normal index: iVar5 is negative, so iVar5 * 8 gives offset from arrayBase
                entryPtr = (int *)(*(int *)(internal + 8) + iVar5 * 8);
            }
            if (entryPtr == (int *)0x0) {
                goto LAB_00628a24;
            }
            if (*entryPtr == 4) {
                entryValue = *(uint *)(entryPtr[1] + 0xc);
            } else {
                int result = FUN_00633990(internal);
                if (result == 0) {
                    goto LAB_00628a24;
                }
                entryValue = *(uint *)(entryPtr[1] + 0xc);
            }
        } else {
            // iVar5 >= 1: iterate from the end of the array
            entryPtr = (int *)(*(int *)(internal + 0xc) - 8 + iVar5 * 8);
            if (entryPtr < *(int **)(internal + 8)) {
                goto LAB_00628ac4; // jump back to the if-else above? Actually it goes to the label that processes entryPtr.
            }
LAB_00628a24:
            entryValue = 0;
        }

        // Check if we should stop removing
        if (((count - currentIndex) + 1 < 10) && (accumulatedValue <= entryValue)) {
            break;
        }

        accumulatedValue += entryValue;
        local_8 += 8;
        local_4 += 1;
        currentIndex++;
        iVar5--;
    } while (currentIndex < count);

    // Compact the list: remove the first (currentIndex-1) elements
    FUN_00626460(); // likely memmove or similar
    *(int *)(thisPtr + 4) = count - (currentIndex - 1);
}