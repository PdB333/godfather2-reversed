// FUN_NAME: ObjectManager::processPendingOperations
void __thiscall ObjectManager::processPendingOperations(void)
{
    uint *hashBucketEntry;
    int globalPtr; // pointer to global HashTableManager
    uint hashValue;
    uint newItemId;
    undefined *defaultString;
    bool bFlag;
    uint *currentPtr;
    undefined4 local_14;
    int local_10;
    undefined local_c;

    // +0x90: count of pending removal hashes
    // +0x10: array of hash values to remove (size at +0x90)
    globalPtr = DAT_0122337c; // global HashTableManager structure
    uint index = *(int *)(this + 0x90) - 1;

    if ((int)index >= 0)
    {
        currentPtr = (uint *)(this + 0x10 + index * 4);
        do
        {
            hashValue = *currentPtr;

            // Look up hashValue in the global hash table
            // DAT_0122337c+0x50: pointer to bucket array
            // DAT_0122337c+0x54: number of buckets (used for modulo)
            for (hashBucketEntry = *(uint **)(*(int *)(globalPtr + 0x50) + (hashValue % *(uint *)(globalPtr + 0x54)) * 4);
                 hashBucketEntry != (uint *)0x0;
                 hashBucketEntry = (uint *)hashBucketEntry[2])
            {
                if (*hashBucketEntry == hashValue)
                {
                    // Found entry. Check if it's valid and not already deleted (+0x24 == -1)
                    if ((hashBucketEntry != (uint *)0x0) &&
                        (hashBucketEntry[1] != 0) &&
                        (*(int *)(hashBucketEntry[1] + 0x24) != -1))
                    {
                        // Re-fetch bucket head (reset chain)
                        hashBucketEntry = *(uint **)(*(int *)(globalPtr + 0x50) + (hashValue % *(uint *)(globalPtr + 0x54)) * 4);
                        goto found_and_not_deleted;
                    }
                    break;
                }
            }

            // If we reach here, entry is not found or already deleted.
            // Remove this hash from the pending list by shifting subsequent elements.
            if (index < *(uint *)(this + 0x90))
            {
                uint shiftIndex = index;
                if (index < *(uint *)(this + 0x90) - 1)
                {
                    do
                    {
                        *(undefined4 *)(this + 0x10 + shiftIndex * 4) = *(undefined4 *)(this + 0x14 + shiftIndex * 4);
                        shiftIndex = shiftIndex + 1;
                    } while (shiftIndex < *(int *)(this + 0x90) - 1U);
                }
                *(int *)(this + 0x90) = *(int *)(this + 0x90) + -1; // decrement count
            }
            goto after_remove;

found_and_not_deleted:
            // Found a valid entry that hasn't been deleted yet.
            // Reset chain and delete the object associated with the entry.
            if (hashBucketEntry == (uint *)0x0)
                goto after_remove;
            if (*hashBucketEntry == hashValue)
            {
                if ((hashBucketEntry != (uint *)0x0) && (hashBucketEntry[1] != 0))
                {
                    // hashBucketEntry[1] is a pointer to an object; delete it
                    FUN_004048c0(hashBucketEntry[1], 0);
                }
                goto after_remove;
            }
            // Continue traversing chain if not matching (shouldn't happen)
            hashBucketEntry = (uint *)hashBucketEntry[2];
            goto found_and_not_deleted;

after_remove:
            currentPtr = currentPtr + -1;
            index = index - 1;
        } while ((int)index >= 0);
    }

    // After processing all pending removals, check if we have a pending addition.
    // +0x198: count of items in the pending queue (+0x118, max 0x20)
    if ((*(int *)(this + 0x90) == 0) && (*(int *)(this + 0x198) == 0))
    {
        bFlag = *(int *)(this + 0x6c4) == 0; // +0x6c4: some flag (e.g., bPendingAdditionProcessed)
        if (bFlag)
            goto check_all_empty;

        if (*(char *)(this + 0x1c4) == '\0')
        {
            // No specific type flag, use a string-based resource creation
            defaultString = *(undefined1 **)(this + 0x1d8); // +0x1d8: pointer to string
            if (defaultString == (undefined1 *)0x0)
            {
                defaultString = &DAT_0120546e; // default string constant
            }
            newItemId = FUN_00403a50(defaultString, _DAT_00e2e524, 0, 0, 0);
        }
        else
        {
            // Use integer-based resource creation from four 32-bit fields
            newItemId = FUN_00404280(
                ((*(int *)(this + 0x1c8) * 0x21 + *(int *)(this + 0x1cc)) * 0x21 + *(int *)(this + 0x1d0)) * 0x21 + *(int *)(this + 0x1d4),
                _DAT_00e2e524,
                0
            );
        }

        // Enqueue the new item ID (up to 32 elements)
        if (*(uint *)(this + 0x198) < 0x20)
        {
            *(undefined4 *)(this + 0x118 + *(uint *)(this + 0x198) * 4) = newItemId;
            *(int *)(this + 0x198) = *(int *)(this + 0x198) + 1;
        }

        // Backup the pending addition data
        // +0x19c to +0x1ac correspond to +0x1c4 to +0x1d4
        *(undefined1 *)(this + 0x19c) = *(undefined1 *)(this + 0x1c4);
        *(undefined4 *)(this + 0x1a0) = *(undefined4 *)(this + 0x1c8);
        *(undefined4 *)(this + 0x1a4) = *(undefined4 *)(this + 0x1cc);
        *(undefined4 *)(this + 0x1a8) = *(undefined4 *)(this + 0x1d0);
        *(undefined4 *)(this + 0x1ac) = *(undefined4 *)(this + 0x1d4);

        // Clear the source string
        FUN_004d3e20(this + 0x1d8);

        // Copy another flag
        *(undefined1 *)(this + 0x1c0) = *(undefined1 *)(this + 0x1e8);
        FUN_004524b0();
    }

    bFlag = *(int *)(this + 0x6c4) == 0;

check_all_empty:
    // If both pending remove list and pending queue are empty, signal condition
    if ((bFlag) && (*(int *)(this + 0x90) == 0) && (*(int *)(this + 0x198) == 0))
    {
        // Lock/enter critical section
        FUN_004086d0(&DAT_01206940);
        // Prepare a local structure for signaling
        local_10 = this + 0xbcc; // +0xbcc: some offset (maybe a condition or event)
        local_14 = DAT_0120e970;
        local_c = 0;
        FUN_00408a00(&local_14, 0); // Signal condition
    }
    return;
}