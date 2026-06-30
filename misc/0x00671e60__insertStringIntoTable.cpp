// FUNC_NAME: insertStringIntoTable
// Function address: 0x00671e60
// Role: Inserts a string index into a sorted bucket array (hash table with chaining).
// The object at param_1 (this) contains:
//   +0x0c: base pointer to an array of structs of size 0xc4 (each has string at +0x04 and short at +0x44)
//   +0x10: count of buckets (ushort)
//   +0x14: pointer to an array of bucket entries (each 8 bytes: short count, int* ptr to array of indices)
// param_2 is an index into the base array (multiplied by 0xc4 to get the struct).
// Returns 0 on success, or error codes (0x2718 = allocation failure, 0x271e = reallocation failure).

int __thiscall insertStringIntoTable(int thisPtr, int index)
{
    short *bucketPtr;
    char cVar2;
    ushort bucketCount;
    short sVar4;
    bool bVar5;
    bool bVar6;
    bool bVar7;
    bool bVar8;
    int iVar9;
    char *pcVar10;
    int iVar12;
    char *pcVar13;
    bool bVar14;
    uint local_9c;
    uint local_98;
    uint local_94;
    undefined2 local_80[64]; // temporary buffer for string copy (unused in final path)

    bucketCount = *(ushort *)(thisPtr + 0x10);
    local_9c = 0;

    if (bucketCount == 0) {
        // First insertion: allocate initial bucket array
        iVar9 = allocate(); // FUN_00673070
        *(int *)(thisPtr + 0x14) = iVar9;
        if (iVar9 != 0) {
            int newBucket = allocate(); // FUN_00673070
            *(int *)(*(int *)(thisPtr + 0x14) + 4) = newBucket;
            if (*(int *)(*(short **)(thisPtr + 0x14) + 2) != 0) {
                // Initialize bucket: count = 1, first element = index
                **(short **)(thisPtr + 0x14) = 1;
                **(short **)(*(int *)(thisPtr + 0x14) + 4) = (short)index;
                *(short *)(thisPtr + 0x10) = *(short *)(thisPtr + 0x10) + 1;
                return 0;
            }
        }
        return 0x2718; // allocation failed
    }

    bVar5 = false;
    bVar14 = false;
    local_94 = 0;

    do {
        if (bucketCount <= local_94) {
            // All buckets exhausted, need to add a new bucket
            if (!bVar5) {
                // Reallocate bucket array to hold one more bucket
                iVar9 = reallocate(*(int *)(thisPtr + 0x14), (uint)bucketCount * 8); // FUN_006730f0
                *(int *)(thisPtr + 0x14) = iVar9;
                if (iVar9 == 0) {
                    return 0x271e; // reallocation failed
                }
                int newBucket = allocate(); // FUN_00673070
                *(int *)(*(int *)(thisPtr + 0x14) + 4 + (uint)*(ushort *)(thisPtr + 0x10) * 8) = newBucket;
                if (*(int *)(*(int *)(thisPtr + 0x14) + 4 + (uint)*(ushort *)(thisPtr + 0x10) * 8) == 0) {
                    *(short *)(thisPtr + 0x10) = *(short *)(thisPtr + 0x10) + 1;
                    return 0x2718;
                }
                // Initialize new bucket
                *(short *)(*(int *)(thisPtr + 0x14) + (uint)*(ushort *)(thisPtr + 0x10) * 8) = 1;
                **(short **)(*(int *)(thisPtr + 0x14) + 4 + (uint)*(ushort *)(thisPtr + 0x10) * 8) = (short)index;
                *(short *)(thisPtr + 0x10) = *(short *)(thisPtr + 0x10) + 1;
                return 0;
            }
            break;
        }

        // Iterate over buckets
        bucketPtr = (short *)(*(int *)(thisPtr + 0x14) + local_94 * 8);
        sVar4 = *bucketPtr; // number of entries in this bucket

        for (local_98 = 0; (!bVar5 && (local_98 < (uint)(int)sVar4)); local_98 = local_98 + 1) {
            // Get the two structs to compare: new entry (index) and existing entry
            int newStruct = index * 0xc4 + *(int *)(thisPtr + 0xc);
            int existingStruct = (uint)*(ushort *)(*(int *)(bucketPtr + 2) + local_98 * 2) * 0xc4 + *(int *)(thisPtr + 0xc);

            cVar2 = *(char *)(newStruct + 4); // first char of new string
            pcVar13 = (char *)(newStruct + 4);
            pcVar10 = (char *)(existingStruct + 4);

            // Determine comparison mode based on null strings and flags
            if ((cVar2 == '\0') || (*pcVar10 == '\0')) {
                bVar5 = false;
            } else {
                bVar5 = true;
            }

            if ((*(short *)(newStruct + 0x44) == 0) || (bVar8 = true, *(short *)(existingStruct + 0x44) == 0)) {
                bVar8 = false;
            }

            if ((cVar2 == '\0') || (*(short *)(existingStruct + 0x44) == 0)) {
                bVar6 = false;
            } else {
                bVar6 = true;
            }

            if ((*(short *)(newStruct + 0x44) == 0) || (*pcVar10 == '\0')) {
                bVar7 = false;
            } else {
                bVar7 = true;
            }

            if (bVar5) {
                // Both strings non-null: compare lexicographically
                while (true) {
                    if ((*pcVar13 == '\0') && (*pcVar10 == '\0')) {
                        bVar14 = true; // equal strings
                        goto LAB_0067200e;
                    }
                    if (*pcVar13 != *pcVar10) break;
                    pcVar13 = pcVar13 + 1;
                    pcVar10 = pcVar10 + 1;
                }
                bVar14 = (char)((*pcVar10 <= *pcVar13) * '\x02') == '\x01'; // new string > existing?
LAB_0067200e:
                if (bVar14) goto LAB_00672012; // found insertion point
            } else {
                // One or both strings null: use flags to decide order
                if (bVar8) {
                    bVar14 = true;
                } else if (bVar6) {
                    // new string non-null, existing flag zero: compute length of new string (unused)
                    iVar9 = 0;
                    while (cVar2 != '\0') {
                        iVar9 = iVar9 + 1;
                        cVar2 = pcVar13[iVar9];
                    }
                    local_80[iVar9] = 0; // store null terminator (unused)
                    bVar14 = true;
                } else {
                    if (!bVar7) goto LAB_0067200e;
                    // existing string non-null, new flag zero: compute length of existing string (unused)
                    iVar9 = 0;
                    cVar2 = *pcVar10;
                    while (cVar2 != '\0') {
                        iVar12 = iVar9 + 1;
                        iVar9 = iVar9 + 1;
                        cVar2 = pcVar10[iVar12];
                    }
                    local_80[iVar9] = 0;
                    bVar14 = true;
                }
LAB_00672012:
                local_9c = local_94; // remember bucket index
            }
            bVar5 = bVar14;
        }
        local_94 = local_94 + 1;
    } while (!bVar5);

    // Insert index into the found bucket (local_9c) at the appropriate position
    int bucketArray = *(int *)(thisPtr + 0x14) + local_9c * 8;
    int bucketPtr2 = *(int *)(bucketArray + 4); // pointer to array of indices
    int newSize = *(short *)(bucketArray) * 4; // size in bytes (each index is 2 bytes, but realloc uses *4? Actually *4 for byte count)
    int reallocated = reallocate(bucketPtr2, newSize); // FUN_006730f0
    *(int *)(bucketArray + 4) = reallocated;
    iVar9 = *(int *)(bucketArray + 4);
    if (iVar9 == 0) {
        return 0x271e;
    }
    // Insert index at the end (since we found insertion point but didn't shift? Actually it just appends)
    *(short *)(iVar9 + *(short *)(bucketArray) * 2) = (short)index;
    // Increment bucket count
    short *countPtr = (short *)(bucketArray);
    *countPtr = *countPtr + 1;
    return 0;
}