// FUNC_NAME: PlayerReputationTracker::updateMaxReputation
// Function address: 0x007ab2a0
// Updates the maximum reputation value to be at least currentReputation + constant.
// The object at this+0x58 is a sub-structure (likely reputation data) with a uint at +0x24f4 (maxReputation).

void __thiscall PlayerReputationTracker::updateMaxReputation(int param_2)
{
    // Get the reputation data pointer from this+0x58
    int* reputationData = *(int**)(this + 0x58); // +0x58: pointer to reputation data structure

    // Retrieve current reputation value using the callee function
    int currentReputation = getReputationValue(reputationData, param_2); // FUN_007dfa80

    if (currentReputation != 0)
    {
        // Pointer to the max reputation field at offset 0x24f4 within the reputation data
        uint* maxReputation = (uint*)(reputationData + 0x24f4 / 4); // +0x24f4: max reputation (uint)

        // Calculate new max candidate: currentReputation + global constant
        uint newMax = (uint)(currentReputation + kReputationMaxIncrement); // DAT_01205224

        // Update max reputation if it's smaller than the candidate
        if (*maxReputation < newMax)
        {
            *maxReputation = newMax;
        }
    }
}