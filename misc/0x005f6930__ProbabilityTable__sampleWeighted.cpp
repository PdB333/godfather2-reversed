// FUNC_NAME: ProbabilityTable::sampleWeighted
char __thiscall ProbabilityTable::sampleWeighted(int thisPtr, char bContinue, float* outCumulativeWeight, float threshold, int* outPrevIndex, uint* outCurIndex)
{
    int iVar1;
    int* piVar2;
    float* pfWeight;
    int iPrevItem;
    int iPrevWeight;
    uint index;
    int iCurrentItem;
    float fCumulative;
    char bResult;
    float fEntryWeight;
    int local_14;
    int local_c;
    int local_8;
    int local_4;

    fCumulative = 0.0;
    bResult = bContinue;
    fEntryWeight = 0.0;
    
    // If the table has exactly 2 entries, check whether they are duplicates
    if (*(int*)(thisPtr + 0xC) == 2) {
        piVar2 = *(int**)(thisPtr + 8);
        // +0x00: pointer, +0x08: weight? Actually offsets within 0xC entry:
        // piVar2[0] = item1, piVar2[3] = item2 (since each entry is 3 ints? Actually 0xC = 12 bytes = 3 ints)
        // piVar2[2] = weight1, piVar2[5] = weight2
        if ((*piVar2 == piVar2[3]) && ((*piVar2 == 0 || (piVar2[2] == piVar2[5])))) {
            *outCumulativeWeight = 0.0;
            return bContinue;
        }
    }
    
    index = 0;
    // If count is 0, return immediately
    if (*(int*)(thisPtr + 0xC) == 0) {
LAB_005f6a98:
        *outCumulativeWeight = fCumulative;
        return bResult;
    }
    
    local_14 = 0;
    iPrevItem = 0;
    iPrevWeight = 0;
    do {
        // Each entry is 0xC bytes: layout = [int item, int unused?, int weight] ? Actually piVar2 points to current entry
        piVar2 = (int*)(*(int*)(thisPtr + 8) + local_14);
        iCurrentItem = *piVar2;  // +0x00
        iVar1 = iCurrentItem;
        if (iCurrentItem == 0) {
            iVar7 = 0;  // weight if item null?
        } else {
            iVar7 = piVar2[2];  // +0x08 (third int)
        }
        
        if (iPrevWeight != 0) {  // Skip first iteration
            if (iCurrentItem == iPrevItem) {
                // Same item as previous – combine weights
                pfWeight = (float*)FUN_005f5ec0(iPrevWeight, iVar7);
            } else {
                // Different item – need to finalize previous group using auxiliary list
                local_c = 0;
                local_8 = 0;
                if (iCurrentItem != 0) {
                    local_8 = *(int*)(iCurrentItem + 4);  // store previous linked list head?
                    *(int**)(iCurrentItem + 4) = &local_c;  // temporally overwrite
                    local_c = iCurrentItem;
                }
                local_4 = iVar7;  // weight for the new item
                pfWeight = (float*)FUN_005f5f20(iPrevWeight, &local_c);
                // Restore the linked list (if needed). The code restores the pointer.
                if (local_c != 0) {
                    piVar2 = *(int**)(local_c + 4);
                    if (piVar2 == &local_c) {
                        *(int*)(local_c + 4) = local_8;
                    } else {
                        while ((int*)piVar2[1] != &local_c) {
                            piVar2 = (int*)piVar2[1];
                        }
                        piVar2[1] = local_8;
                    }
                }
            }
            // Accumulate the weight of the current entry
            fCumulative = *pfWeight + fEntryWeight;
            fEntryWeight = fCumulative;
            
            // If we are not continuing and threshold is reached, return the entry indices
            if ((bContinue == '\0') && (threshold < fCumulative)) {
                // Subtract the last added weight to get the cumulative before this entry
                fCumulative = *pfWeight - (fCumulative - threshold);
                *outPrevIndex = index - 1;   // index of previous group end
                *outCurIndex = index;        // current index
                bResult = '\x01';            // found
                goto LAB_005f6a98;
            }
        }
        // Advance to next entry
        local_14 = local_14 + 0xC;
        index = index + 1;
        iPrevItem = iCurrentItem;
        iPrevWeight = iVar7;
        if (*(uint*)(thisPtr + 0xC) <= index) {
            *outCumulativeWeight = fCumulative;
            return bContinue;
        }
    } while (true);
}