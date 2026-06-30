// FUNC_NAME: PlayerReputationTracker::applyDecayTick
void __fastcall PlayerReputationTracker::applyDecayTick(PlayerReputationTracker* this)
{
    // Threshold for decay activation (global)
    float threshold = g_reputationDecayThreshold; // _DAT_00d5780c

    // Base decay timer value (global)
    this->decayTimer = g_baseDecayTimer; // +0x23c, DAT_01205224

    // If current decay value is below threshold, adjust timer
    if (this->currentDecayValue < threshold) { // +0x240 (float)
        float diff = threshold - this->currentDecayValue;
        this->currentDecayValue = diff;

        // Scale difference by a multiplier and round to int
        int scaledDiff = (int)(long long)ROUND(diff * g_decayMultiplier); // _DAT_00d5f51c
        this->decayTimer = g_baseDecayTimer - scaledDiff;
    }

    // Reset flags and counters
    this->decayActiveFlag = 0; // +0x248 (byte)
    this->decayCounter1 = 0;   // +600 = +0x258 (dword)
    this->decayCounter2 = 0;   // +0x25c (dword)
}