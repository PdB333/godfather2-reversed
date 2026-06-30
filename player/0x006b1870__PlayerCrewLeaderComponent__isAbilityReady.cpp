// FUNC_NAME: PlayerCrewLeaderComponent::isAbilityReady
bool __fastcall PlayerCrewLeaderComponent::isAbilityReady(int thisPtr) {
    // Check bit 27 of flags at +0x34 – indicates ability is unlocked/active
    uint32_t flags = *(uint32_t *)(thisPtr + 0x34);   // +0x34: statusFlags
    if (!((flags >> 27) & 1)) {
        return false;
    }

    // Cooldown check: global timer vs last usage time + 30000ms
    uint32_t lastUsed = *(uint32_t *)(thisPtr + 0x70); // +0x70: lastActivationTime (typically ms)
    uint32_t globalTime = DAT_01205224;                // global game time in ms

    // Cooldown is expired if current time < (lastUsed + 30000) i.e. still in cooldown? 
    // Actually condition returns true only if globalTime < lastUsed + 30000 -> meaning we are BEFORE the cooldown ends? 
    // That seems inverted. Possibly the logic: ability is ready when current time is less than the cooldown end time? 
    // Or the check is for "cooldown still active" but returns false if past? 
    // Let's keep original logic.
    return (globalTime < lastUsed + 30000U);
}