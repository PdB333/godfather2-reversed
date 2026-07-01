// FUNC_NAME: PlayerReputationTracker::getReputationTier
int __thiscall PlayerReputationTracker::getReputationTier(float value) const
{
    // Offsets:
    // +0x54: float tier1Threshold (low->medium)
    // +0x58: float tier2Threshold (medium->high)
    // +0x5c: float tier3Threshold (high->very high)
    // Returns 0 (low), 1 (medium), 2 (high), 3 (very high)

    if (value <= *(float*)(this + 0x54))
        return 0;

    if (value <= *(float*)(this + 0x58))
        return 1;

    if (value <= *(float*)(this + 0x5c))
        return 2;

    return 3;
}