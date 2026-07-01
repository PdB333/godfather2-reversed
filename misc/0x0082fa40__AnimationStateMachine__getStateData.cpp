// FUNC_NAME: AnimationStateMachine::getStateData

undefined4 * __thiscall AnimationStateMachine::getStateData(int thisPtr, undefined4 *output, undefined4 input)
{
    undefined ***tempArray;
    char comparisonResult;
    uint hashIndex;
    int nextIndex;
    undefined ***selectedPtr;
    undefined *localArray[19];
    undefined4 local_24;
    undefined4 uStack_20;
    undefined4 local_1c;
    undefined4 uStack_18;
    undefined4 local_14;

    // State machine based on thisPtr+0xc
    if (*(int *)(thisPtr + 0xc) == 0) {
        // State 0: Initialize with default data
        FUN_008334a0(); // Likely a global initialization or reset
        local_24 = DAT_00d5ef88;
        uStack_20 = DAT_00d6471c;
        localArray[0] = &PTR_LAB_00d7377c; // Vtable or static pointer
        local_1c = _DAT_00d5cf70;
        uStack_18 = DAT_00e44630;
        local_14 = _DAT_00d5cf70;
        FUN_0081f9f0(localArray); // Copy or process localArray
        // Fill output structure at offsets 0x4c, 0x54, 0x5c
        *(ulonglong *)(output + 0x13) = CONCAT44(uStack_20, local_24);
        *(ulonglong *)(output + 0x15) = CONCAT44(uStack_18, local_1c);
        *output = &PTR_LAB_00d7377c; // Set vtable pointer
        output[0x17] = local_14;
        return output;
    }
    if (*(int *)(thisPtr + 0xc) != 1) {
        // State >=2: Transition based on input hash
        hashIndex = FUN_0082c5b0(input); // Hash function returning index
        if (hashIndex == 0xffffffff) {
            // Invalid hash: use default data
            FUN_008334a0();
            local_24 = DAT_00d5ef88;
            uStack_20 = DAT_00d6471c;
            localArray[0] = &PTR_LAB_00d7377c;
            local_1c = _DAT_00d5cf70;
            uStack_18 = DAT_00e44630;
            local_14 = _DAT_00d5cf70;
            selectedPtr = localArray;
        }
        else {
            // Valid hash: update current index and select next state
            *(uint *)(thisPtr + 4) = hashIndex;
            if (hashIndex < *(int *)(thisPtr + 0xc) - 1U) {
                nextIndex = hashIndex + 1;
            }
            else {
                nextIndex = 0;
            }
            // Get pointers to current and next state data from array at thisPtr+8
            selectedPtr = *(undefined ****)(*(int *)(thisPtr + 8) + hashIndex * 4);
            undefined ***nextPtr = *(undefined ****)(*(int *)(thisPtr + 8) + nextIndex * 4);
            // Compare input with next state's data (offset +1)
            comparisonResult = FUN_00835a00(input, nextPtr + 1);
            if (comparisonResult != '\0') {
                // If match, use current state instead
                selectedPtr = selectedPtr;
            }
        }
        FUN_0082b6a0(selectedPtr); // Process selected state
        return output;
    }
    // State 1: Copy data from first element of array
    int *firstElement = **(int ***)(thisPtr + 8); // Dereference twice to get first pointer
    FUN_0081f9f0(firstElement); // Copy or process
    *output = &PTR_LAB_00d7377c;
    *(undefined8 *)(output + 0x13) = *(undefined8 *)(firstElement + 0x4c);
    *(undefined8 *)(output + 0x15) = *(undefined8 *)(firstElement + 0x54);
    output[0x17] = *(undefined4 *)(firstElement + 0x5c);
    return output;
}