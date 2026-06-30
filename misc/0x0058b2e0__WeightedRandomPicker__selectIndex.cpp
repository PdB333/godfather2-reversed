// FUNC_NAME: WeightedRandomPicker::selectIndex
int WeightedRandomPicker::selectIndex(void* rngState, SelectionInfo* selectionInfo, RandomWeightTable* weightTable)
{
    // selectionInfo layout:
    // +0x00: unknown (maybe vtable or size)
    // +0x01: char numEntries (count of weightPointers array)
    // +0x04 (int*): pointer to short[2] (excludeIndex, excludeFlag)
    // +0x0C (int*): array of int* pointers to weight structs (float at +8)
    short* excludeData = (short*)selectionInfo->pointerToExcludeData; // selectionInfo[1]
    short excludeIndex = *excludeData;            // index to potentially exclude
    short excludeFlag = excludeData[1];           // if 1, exclude that index
    int numEntries = *(char*)((int)selectionInfo + 1);

    // Ensure weightTable has enough capacity
    if ((uint)weightTable->count <= (uint)(int)excludeIndex) {
        int* temp = 0;
        resizeWeightTable(&temp);  // likely expands the table
    }

    float totalWeight = 0.0f;
    // Convert excludeIndex to a weight array index: weightTable->weights[excludeIndex]
    int excludedWeightIndex = (int)(*weightTable->weights + excludeIndex * 4); // questionable? Actually weightTable->weights is float*, so *weightTable->weights is first float? No, *param_3[0] is first weight? Wait, original: iVar7 = (int)*(float *)(*piVar4 + sVar1 * 4); So *piVar4 is an int? Confusing. We'll assume weightTable->weights is a float array.

    // Actually from decompiled: piVar4 = param_3; then iVar7 = (int)*(float *)(*piVar4 + sVar1 * 4);
    // So *piVar4 gives int (pointer to float array), then index by sVar1*4.
    // So let weightTable->weights be a pointer to float array, and we have an index excludeIndex.
    int* weightArray = (int*)(*((int*)weightTable)); // first field is pointer to float weights
    float excludedWeight = *(float*)((int)weightArray + excludeIndex * 4); // but used as integer? Actually iVar7 is used as int for comparison, but then compared with iVar3 which is index. So iVar7 is the excludeIndex (as integer). So it's not the weight value, it's the index. Yes, iVar7 = (int)*(float*)(... ) is actually reading a float but then converting to int by truncation? That seems odd. Looking at usage: iVar7 is compared with iVar3 (loop index). So it's the exclude index itself, not a weight. So *piVar4 + sVar1 * 4 loads a float, but that float is then cast to int? That would be the exclude index value stored as float? More likely the weight array is actually an integer array (int) not float. Or the cast is wrong. But the function then uses iVar7 as an index to compare. So iVar7 is the excludeIndex. So the weightTable is actually an array of ints (the exclude index stored as a float? Nonsense). Maybe the code is doing something like: iVar7 = *(int*)(weightTable->weights + excludeIndex); So weightTable->weights is int*? Actually original: (int)*(float *)(*piVar4 + sVar1 * 4) - this takes the float at that address and casts to int, which would truncate. So it's probably a bug in decompilation. The intent is to get the integer value stored as float? That would be strange. More likely weightTable is a pointer to a struct with an int array, and the float cast is incorrect. But in many game codebases, weights are floats, and this function is using the exclude index as an integer read from the weights array? No, the exclude index is given by short from selectionInfo. So iVar7 should be the same as excludeIndex. Let's examine: sVar1 = *psVar2 (the first short from excludeData). So excludeIndex is sVar1. Then later iVar7 = (int)*(float*)(*piVar4 + sVar1*4). That reads a float at index sVar1 and casts to int. If the weights are stored as floats, truncation would give a different integer. But if the weights are stored as ints, then the float read would be wrong. I think the Ghidra decompiler misidentified the type. The pointer piVar4 is param_3, which is int*. *piVar4 is an int, which is treated as a pointer to float. But if the actual data is int, then the float read would be garbage. But maybe the array is actually float and the index is used as a float? Then iVar7 would be the truncated float value, but it's used as index. That doesn't make sense. I suspect the actual code is: iVar7 = *(int*)( (char*)(*piVar4) + sVar1*4 ); i.e., the weights array is int*. So the decompiler wrongly casts to float. Let's assume that. So weightTable->weights is an int array (or pointer to ints). And the value at sVar1 is the excluded index? But sVar1 is already the excluded index from selectionInfo. So it's double? Actually look: selectionInfo has a pointer to short[2]; first short is excludeIndex (sVar1). Then weightTable->weights at that index gives another integer (iVar7). Then later comparisons use iVar7 as the index to skip. So the exclude index from selectionInfo is used to look up another index from the weight table? That seems redundant. Alternatively, maybe the short array is not excludeData but something else. Let's re-evaluate: psVar2 = (short *)param_2[1]; sVar1 = *psVar2; This is the index to look up in weight table to get the excluded index iVar7. Then psVar2[2] is the flag. So the selectionInfo contains a pointer to a short array that gives the lookup index (sVar1) and a flag. Then weightTable->weights at that index gives the actual exclude index (iVar7). So iVar7 is the index to skip during summing/selection. That makes sense: the exclude index is stored in the weight table, and selectionInfo provides a key to retrieve it.

Thus: excludeIndexFromTable = weightTable->weights[ sVar1 ]; // integer
excludeFlag = *(short*)(selectionInfo->excludeData + 2); // but careful: psVar2 is pointer to short at offset after first short, so psVar2[2] is short at offset 4.

So the flag is at offset 2 from that pointer? Actually short array: psVar2[0] = sVar1, psVar2[1] = ?, psVar2[2] = flag? No, psVar2[2] is the third short (offset 4 bytes). But from the code, it's psVar2[2] == 1. So the flag is at offset 2 from the start of that short array. The array seems to have three shorts: [0] lookupIndex, [1] unknown, [2] excludeFlag. But in original, the first short is sVar1, then later psVar2[2] is compared to 1. So there is an unused short at offset 2? Actually short at offset 2 is the second short? Wait: short pointer incremented by 2 bytes per element. So psVar2 points to short0 at offset0, psVar2[1] is short at offset2, psVar2[2] is short at offset4. So the flag is at offset4. So the array has at least 5 bytes? Unclear. We'll keep it simple.

Given the complexity, we'll produce a reconstruction that captures the logic, using descriptive names and comments.

We'll assume WeightTable is a simple struct with a pointer to int array and count.

We'll also note the global random table.

Let's write it.// FUNC_NAME: WeightedRandomPicker::selectIndex
int WeightedRandomPicker::selectIndex(void* rngState, WeightedSelectionInfo* selectionInfo, RandomWeightTable* weightTable)
{
    // selectionInfo layout:
    // +0x00: unknown (size or padding)
    // +0x01: uint8_t numEntries (count of weight pointers)
    // +0x04: short* excludeDataPointer (points to short[3]: [lookupIndex], [unused], [excludeFlag?])
    // +0x0C: int** weightPointers (array of pointers to weight containers with float value at +0x08)

    short* excludeData = (short*)selectionInfo->excludeDataPointer;
    int lookupIndex = excludeData[0];      // Index into weightTable->weights to get actual exclude index
    int excludeFlag  = excludeData[2];     // If 1, exclude the index from summation/selection
    int numEntries = *(uint8_t*)((int)selectionInfo + 1);

    // Resize weightTable if needed (safety check)
    if ((uint)weightTable->count <= (uint)(int)lookupIndex)
    {
        int* temp = 0;
        resizeWeightTable(&temp); // Expands the table to accommodate lookupIndex
    }

    // Retrieve the exclude index from the weight table – this is the actual index to skip
    int excludeIndex = weightTable->weights[lookupIndex]; // stored as an int in the array
    float totalWeight = 0.0f;

    // -------- First pass: compute total weight sum (maybe excluding excludeIndex) --------
    if (excludeFlag == 1)
    {
        int i = 0;
        int* ptr = selectionInfo->weightPointers;
        // Unrolled loop for first 4 entries (or until remaining < 4)
        for (int group = 0; group <= numEntries - 4; group += 4)
        {
            if (i != excludeIndex) totalWeight += *(float*)(ptr[0] + 8);
            if (i+1 != excludeIndex) totalWeight += *(float*)(ptr[1] + 8);
            if (i+2 != excludeIndex) totalWeight += *(float*)(ptr[2] + 8);
            if (i+3 != excludeIndex) totalWeight += *(float*)(ptr[3] + 8);
            i += 4;
            ptr += 4;
        }
        // Remaining entries (0..3)
        for (; i < numEntries; i++)
        {
            if (i != excludeIndex) totalWeight += *(float*)(ptr[0] + 8);
            ptr++;
        }
    }
    else // no exclusion
    {
        int i = 0;
        int* ptr = selectionInfo->weightPointers;
        for (int group = 0; group <= numEntries - 4; group += 4)
        {
            totalWeight += *(float*)(ptr[0] + 8) + *(float*)(ptr[1] + 8) +
                           *(float*)(ptr[2] + 8) + *(float*)(ptr[3] + 8);
            i += 4;
            ptr += 4;
        }
        for (; i < numEntries; i++)
        {
            totalWeight += *(float*)(ptr[0] + 8);
            ptr++;
        }
    }

    // -------- Generate random threshold --------
    unsigned int randIndex;
    if (rngState != 0 && (*(uint8_t*)((int)rngState + 0x13) & 1) != 0)
    {
        // Use per-object RNG counter
        randIndex = (*(int*)((int)rngState + 0x2d4) + 1) & RANDOM_MASK;
        *(unsigned int*)((int)rngState + 0x2d4) = randIndex;
    }
    else
    {
        // Use global RNG counter
        randIndex = (g_globalRngCounter + 1) & RANDOM_MASK;
        g_globalRngCounter = randIndex;
    }

    float randomFactor = g_randomTable[randIndex]; // precomputed float in [0,1)
    float threshold = randomFactor * totalWeight;

    // -------- Second pass: accumulate weights until threshold is hit --------
    float cumulativeWeight = 0.0f;
    int* ptr = selectionInfo->weightPointers;
    if (excludeFlag == 1)
    {
        for (int i = 0; i < numEntries; i++)
        {
            if (i != excludeIndex) cumulativeWeight += *(float*)(ptr[i] + 8);
            if (threshold < cumulativeWeight) return i; // found
        }
    }
    else
    {
        for (int i = 0; i < numEntries; i++)
        {
            cumulativeWeight += *(float*)(ptr[i] + 8);
            if (threshold < cumulativeWeight) return i;
        }
    }

    // Fallback (should not happen)
    return 0;
}