// FUNC_NAME: partitionElementsByKey (sorting 20-dword elements by uint key at offset 8)
// Address: 0x008899c0
// This function partitions an array of elements (each 20 dwords = 80 bytes) based on a pivot key.
// It reorders elements so that all keys < pivot are on the left, and all >= pivot on the right.
// The pivot is taken from the element pointed to by param_3.
// param_1: start pointer (left bound)
// param_2: end pointer (right bound) – initially points one element past the last? Actually moves backward.
// param_3: pointer to pivot element (its value is copied locally, then param_3 is consumed)
// Returns nothing, modifies the array in place.

void partitionElementsByKey(uint *param_1, uint *param_2, uint *param_3)
{
    uint uVar1;
    int iVar2;
    uint *puVar3;
    uint *puVar4;
    uint pivotBuffer[20]; // buffer to hold the pivot element (20 dwords)

    // Copy the pivot element from param_3 into local pivotBuffer (20 dwords)
    puVar3 = pivotBuffer;
    for (iVar2 = 0x14; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *param_3;
        param_3 = param_3 + 1;
        puVar3 = puVar3 + 1;
    }

    // Partition loop (Hoare scheme with element size 20 dwords)
    while( true ) {
        // Move left pointer forward while element's key < pivot key
        for (; param_1[2] < pivotBuffer[2]; param_1 = param_1 + 0x14) {
        }

        // Prepare to move right pointer backward
        uVar1 = param_2[-0x12];               // offset -0x12 in dwords? Possibly -18 words = -72 bytes? But element size is 20 words.
        puVar3 = param_2;
        // Move right pointer backward while element's key >= pivot key
        while (param_2 = puVar3 + -0x14, pivotBuffer[2] < uVar1) {
            // Decrement further: compute new candidate key
            uVar1 = puVar3[-0x26];            // offset -0x26 = -38 words = -152 bytes, sketchy arithmetic
            puVar3 = param_2;
        }

        // If pointers have crossed, exit the partition loop
        if (param_2 <= param_1) break;

        // Save element at left pointer into pivotBuffer (temporary)
        puVar3 = param_1;
        puVar4 = pivotBuffer;
        for (iVar2 = 0x14; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
        }

        // Move element from right pointer to left pointer
        puVar3 = param_2;
        puVar4 = param_1;
        for (iVar2 = 0x14; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
        }

        // Move saved element (from left) to right pointer
        puVar3 = pivotBuffer;
        puVar4 = param_2;
        for (iVar2 = 0x14; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
        }

        // Advance left pointer for next iteration
        param_1 = param_1 + 0x14;
    }

    // Partition complete – no further action (caller likely recurses)
    return;
}