// FUNC_NAME: NPCActionSelector::selectRandomItemExcludingCategory
// Address: 0x006f9820
// Role: Iterates over an array of items, filters out items matching the current category (this+0x38),
//       and randomly selects one based on a weight/threshold system.
//       The threshold is either passed in (param_3) or taken from a global default.
//       Stores the selected item's pointer in *param_3 (overwrites threshold?).
//       Returns 1 if selected, 0 if no valid item found.

int __thiscall NPCActionSelector::selectRandomItemExcludingCategory(
    ItemArray* pItemArray,  // param_2: pointer to array of item pointers and count
    int* pThresholdOrOutput // param_3: initially points to threshold value; if *pThresholdOrOutput == 0, use global default; then overwritten with selected item pointer
)
{
    int* pItemPtr;
    int* pEnd;
    int* pSelected = pThresholdOrOutput; // will store finally selected item into *pSelected
    bool bFound = false;
    bool bPrevFound = false;

    // Access global RNG context? (DAT_012233a0 + 4) - assumed pointer to RNG state.
    // Would normally be a pointer to a struct (maybe RNG seed manager)
    int rngSeedIndex;
    if (*(int**)(DAT_012233a0 + 4) == 0) {
        rngSeedIndex = 0;
    } else {
        // Offset -0x1f30 likely adjusts to some seed base
        rngSeedIndex = *(int*)(*(int*)(DAT_012233a0 + 4) - 0x1f30);
    }

    // Determine threshold: if *pThresholdOrOutput == 0, use global default (DAT_00d5f6f0 interpreted as float)
    float threshold;
    if (*pThresholdOrOutput == 0) {
        threshold = *(float*)(DAT_00d5f6f0);
    } else {
        // Otherwise generate a random threshold from the RNG
        threshold = randomFloat(rngSeedIndex);
        // The original code reinterprets threshold pointer as float? But we treat as float directly.
    }

    pItemPtr = (int*)*pItemArray; // start of array (pointer to first item pointer)
    pEnd = (int*)(pItemPtr + pItemArray->count); // end of array

    if (pItemPtr != pEnd) {
        do {
            bPrevFound = bFound;
            // Check if current item's category (at +0x0c) does NOT match this object's category (at +0x38)
            if (*(int*)(*pItemPtr + 0x0c) != *(int*)((int)this + 0x38)) {
                if (!bFound) {
                    // First valid item: select it
                    *pSelected = *pItemPtr;
                    // Generate new random threshold for future comparisons
                    threshold = randomFloat(rngSeedIndex);
                } else {
                    // Subsequent valid items: only overwrite if new random threshold is greater than current threshold
                    float newRand = randomFloat(rngSeedIndex);
                    if (newRand <= threshold) {
                        // Skip this item (keep previous selection)
                        goto LAB_006f98c8;
                    }
                    // Otherwise replace selection with current item
                    *pSelected = *pItemPtr;
                    threshold = newRand; // update threshold
                }
                bFound = true;
            }
LAB_006f98c8:
            // Move to next item (re-get end pointer due to possible array growth? but likely just for loop)
            pItemPtr = pItemPtr + 1;
            bPrevFound = bFound; // restore bPrevFound for next iteration? Actually uVar4 = uVar3 at bottom
        } while (pItemPtr != pEnd);
    }

    // Return bFound (1 if any item selected, else 0)
    // The original return had a convoluted composite of pointer and flag, but essentially returns bool
    return (int)bFound;
}