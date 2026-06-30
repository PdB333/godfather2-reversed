// FUNC_NAME: ConditionNode::evaluateComparison
int __thiscall ConditionNode::evaluateComparison(void* thisPtr, int* outputStruct)
{
    char* valueSource1;
    char* valueSource2;
    int index;
    float value1[3];
    float value2[3];
    void** sourceArray;

    // Get the array of two value sources (offset +0x08)
    sourceArray = *(void***)((char*)thisPtr + 0x08);
    valueSource1 = *(char**)sourceArray[0]; // First source pointer

    if (*valueSource1 == '\n') {
        // Reference: read short index at offset +2
        index = *(short*)(valueSource1 + 2);
        if ((index >= 0) && (index < g_valueProviderCount)) {
            // Call the value provider function from the global table
            void (*providerFunc)(int, int, float*) = *(void (__thiscall**)(int, int, float*))(g_valueProviderTable + 4 + index * 0x0C);
            if (providerFunc != nullptr) {
                providerFunc(outputStruct[0], index, value1);
            }
        }
    } else {
        // Inline float at offset +4
        value1[0] = *(float*)(valueSource1 + 4);
    }

    // Second value source (offset +4 from the array base)
    valueSource2 = *(char**)((char*)sourceArray + 4);
    if (*valueSource2 == '\n') {
        index = *(short*)(valueSource2 + 2);
        if ((index >= 0) && (index < g_valueProviderCount)) {
            void (*providerFunc)(int, int, float*) = *(void (__thiscall**)(int, int, float*))(g_valueProviderTable + 4 + index * 0x0C);
            if (providerFunc != nullptr) {
                providerFunc(outputStruct[0], index, value2);
            }
        }
    } else {
        value2[0] = *(float*)(valueSource2 + 4);
    }

    // Compare: return 1 if first > second, else 0
    if (value1[0] <= value2[0]) {
        return 0;
    }
    outputStruct[3] = (int)thisPtr; // Store this pointer in output
    return 1;
}