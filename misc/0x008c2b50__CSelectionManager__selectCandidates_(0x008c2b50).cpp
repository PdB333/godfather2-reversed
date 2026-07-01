// FUNC_NAME: CSelectionManager::selectCandidates (0x008c2b50)
// This function selects a set of valid candidates within a time budget and outputs their IDs.
// It uses a dynamic local array for filtered candidate indices, weighted selection, and time accumulation.

// Internal structures:
// - this+0x1a4: pointer to array of candidate pointers (int** m_candidateArray)
// - this+0x1a8: number of candidates (uint m_candidateCount)
// - this+0x1b0: array of floats for weights (float* m_weights)
// - this+0x1b4: global weight multiplier (float m_weightMultiplier)
// Output array descriptor (int* outArray): [0]=buffer pointer, [1]=count, [2]=capacity

extern float g_globalTimeScale; // DAT_00d5eee4

// Memory wrappers (replace as needed)
void* __cdecl allocate(int size); // FUN_009c8e80
void  __cdecl free(void* ptr);    // FUN_009c8f10
void  __cdecl resizeIntArray(int newSize); // FUN_00486800 (for local array)
void  __cdecl resizeOutArray(int newCapacity); // FUN_006b1e10 (for output array)

char __thiscall CSelectionManager::isCandidateActive(void) // FUN_008c8110
{
    // Uses some state to determine if the current candidate (index uVar11) is active.
    // Return 0/1.
    return 0;
}

int  __thiscall CSelectionManager::getCurrentWeightIndex(void) // FUN_008c8170
{
    // Returns an index into m_weights for the currently selected candidate.
    return 0;
}

int  __cdecl pickWeightedIndex(int* countPtr, float currentTime, float maxTime) // FUN_008be670
{
    // Picks an index from the local dynamic array based on current time and maxTime.
    // Returns the index to remove.
    return 0;
}

bool __thiscall CSelectionManager::selectCandidates(float maxTime, uint maxResults, int* outArray)
{
    uint candidateCount = *(uint*)(this + 0x1a8);
    int* localBuffer = (int*)allocate(candidateCount * 4);
    uint localCount = 0;
    uint localCapacity = candidateCount;

    // First pass: filter active candidates into local dynamic array.
    for (uint i = 0; i < candidateCount; i++)
    {
        if (isCandidateActive())
        {
            if (localCount >= localCapacity)
            {
                // Double capacity if needed
                if (localCapacity == 0)
                    localCapacity = 1;
                else
                    localCapacity *= 2;
                resizeIntArray(localCapacity);
                // Note: localBuffer may be reallocated; update pointer accordingly.
                // In the original code, localBuffer is updated after resize call.
                // Since we don't have the exact implementation, we assume localBuffer is a global.
                // For simplicity, we treat localBuffer as a fixed pointer from allocate.
                // Actually the code uses iVar5 as the buffer pointer, and after resize it becomes new pointer.
                // We'll emulate that.
                localBuffer = (int*)localBuffer; // placeholder
            }
            localBuffer[localCount] = i;
            localCount++;
        }
    }

    uint outputCount = outArray[1];
    float accumulatedTime = *(float*)(this + 0x1b4) * g_globalTimeScale;

    while (outputCount < maxResults && localCount > 0)
    {
        uint chosenIdx = pickWeightedIndex(&localCount, accumulatedTime, maxTime);
        uint candidateIdx = localBuffer[chosenIdx];

        localCount--;
        // Shift remaining elements left
        for (; chosenIdx < localCount; chosenIdx++)
        {
            localBuffer[chosenIdx] = localBuffer[chosenIdx + 1];
        }

        // Get candidate data
        int* candidatePtr = *(int**)(this + 0x1a4);
        candidatePtr = (int*)(candidatePtr[candidateIdx]); // candidate object
        int weightIdx = getCurrentWeightIndex();
        int outputCapacity = outArray[2];
        accumulatedTime += *(float*)(this + 0x1b0 + weightIdx * 4);

        int valueToOutput = *(int*)(candidatePtr + 2); // offset 8 = 2 ints (0,4) -> 8 bytes -> index 2

        // Ensure output array has capacity
        if (outputCount == (uint)outputCapacity)
        {
            if (outputCapacity == 0)
                outputCapacity = 1;
            else
                outputCapacity *= 2;
            resizeOutArray(outputCapacity);
            outArray[2] = outputCapacity;
        }

        // Append value to output
        if (outArray[0] != 0)
        {
            *((int*)(outArray[0] + outputCount * 4)) = valueToOutput;
        }
        outArray[1] = ++outputCount;

        // Check time budget
        if (maxTime < accumulatedTime)
            break;
    }

    bool result = (accumulatedTime > maxTime) ? 1 : 0;

    if (localBuffer != 0)
        free(localBuffer);

    return result;
}