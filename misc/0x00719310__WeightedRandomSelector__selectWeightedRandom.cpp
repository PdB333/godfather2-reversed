// FUNC_NAME: WeightedRandomSelector::selectWeightedRandom

// Reconstructed from 0x00719310
// Selects a random outcome from a two-level weighted probability table.
// The table consists of up to 16 entries, each with 4 floats representing probabilities for sub-outcomes.
// Returns the index of the selected sub-outcome (0..63) or 0 if none selected.
// Uses a cumulative distribution traversal.

class WeightedRandomSelector {
    // Offset 0x18: pointer to some manager/data (e.g., a large structure)
    // This structure's offset 0x2004 holds a pointer to the probability table base
    // The actual table starts at (tableBase - 0x48) + 0x54 = tableBase + 0xC
    // Actually: iVar5 = *(int*)(*(int*)(this+0x18) + 0x2004);
    // If iVar5 != 0, iVar5 = iVar5 - 0x48; // adjust pointer to entry list
    // Then each entry is at iVar5 + 0x54, and contains 4 floats (-1, 0, 1, 2 indices)
    // But note: pfVar3 starts at iVar5+0x54, so the first float is at iVar5+0x50 (pfVar3[-1]),
    // then iVar5+0x54 (*pfVar3), iVar5+0x58 (pfVar3[1]), iVar5+0x5C (pfVar3[2]).
    // So each entry occupies 16 bytes (4 floats).
    // The loop iterates over up to 16 entries, each contributing 4 possible sub-outcomes.
    // The selected index is accumulated from previous entries (iVar4 += 0,1,2,3,4? Actually it adds 0,1,2,3,4 for each condition within an entry.
    // But the break statements add only when condition false? Let's examine:
    // if (fVar6 < entry.prevProb) break; // iVar4 unchanged, sub-index 0 selected within this entry
    // else fVar6 -= entry.prevProb;
    // if (fVar6 < entry.prob0) { iVar4 += 1; break; }
    // else fVar6 -= entry.prob0; then check entry.prob1: iVar4 += 2; break;
    // else fVar6 -= entry.prob1; check entry.prob2: iVar4 += 3; break;
    // else iVar4 += 4; and continue to next entry (fVar6 already subtracted prob2).
    // So within an entry, each sub-outcome increases index by 0,1,2,3,4 respectively.
    // But iVar4 starts at 0 and is incremented by the cumulative count of sub-outcomes from previous entries.
    // At the start of the function, iVar5 is calculated, then if iVar5 == 0, iVar5 = 0 (so pfVar3 might be invalid).
    // The loop runs while iVar4 < 0x10 (16 entries max). If iVar4 reaches 16, returns 0.
    // Returns iVar4 as the selected sub-outcome index (0-63). However, if iVar5 is 0, the loop may not run and returns 0.

    // This is a weighted random selection for a decision with up to 64 options grouped in 4s.
    // Likely used for dialog line selection, reward distribution, or AI behavior selection.

    // Define internal structures for clarity (not part of actual class).
    struct ProbabilityEntry {
        float probBefore;   // Actually stored at offset -4 relative to the entry base
        float prob0;        // offset 0
        float prob1;        // offset +4
        float prob2;        // offset +8
        // Total probability for this entry = probBefore + prob0 + prob1 + prob2
    };

    // Actual class members (inferred)
    void* m_pManager; // offset 0x18 - pointer to some manager object

public:
    int selectWeightedRandom() const;
};

int __fastcall WeightedRandomSelector::selectWeightedRandom() const {
    // Calculate base pointer to probability table
    float* pfVar3;
    int selectedIndex = 0;
    int iVar5;

    // Get pointer to table base from manager's large offset
    int* pManagerData = *(int**)((char*)this + 0x18);
    if (pManagerData != nullptr) {
        // Offset 0x2004 in that manager data holds a pointer to the probability table start
        int tableStart = *(int*)((char*)pManagerData + 0x2004);
        if (tableStart != 0) {
            iVar5 = tableStart - 0x48; // Adjust to actual entry list base
        } else {
            iVar5 = 0;
        }
    } else {
        iVar5 = 0;
    }

    // Generate normalized random value in [0,1)
    int r = _rand();
    float randomValue = (float)r * DAT_00e44590; // DAT_00e44590 likely = 1.0f / RAND_MAX

    if (iVar5 != 0) {
        // Point to first entry's probabilities (entry at offset +0x54 from adjusted base)
        pfVar3 = (float*)(iVar5 + 0x54);

        // Iterate over entries until random value lands or max entries (16) reached
        while (selectedIndex < 16) {
            // Check probability before the entry (probBefore)
            if (randomValue < pfVar3[-1]) {
                break; // selected sub-index = selectedIndex (0 increment)
            }
            randomValue -= pfVar3[-1];

            // Check first probability of the entry
            if (randomValue < *pfVar3) {
                selectedIndex += 1;
                break;
            }
            randomValue -= *pfVar3;

            // Check second probability
            if (randomValue < pfVar3[1]) {
                selectedIndex += 2;
                break;
            }
            randomValue -= pfVar3[1];

            // Check third probability
            float* pfVar1 = pfVar3 + 2;
            if (randomValue < *pfVar1) {
                selectedIndex += 3;
                break;
            }
            // If all four probabilities consumed, move to next entry (add 4 to index)
            selectedIndex += 4;
            pfVar3 += 4; // Advance to next entry (4 floats)
            randomValue -= *pfVar1;
        }

        // If we exhausted all 16 entries without a break, return 0
        if (selectedIndex == 16) {
            return 0;
        }
    }

    return selectedIndex;
}