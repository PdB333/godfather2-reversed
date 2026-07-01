// FUNC_NAME: SpawnManager::computeSpawnCount
void SpawnManager::computeSpawnCount(void) {
    bool bSpawnEnabled;
    uint uMaxCount;
    uint uSpawnCount;
    float fMaxFloat;
    float fFraction;
    int iRand;
    uint uResult;
    
    bSpawnEnabled = isSpawningEnabled(); // FUN_00701010, checks if spawning is allowed
    if (bSpawnEnabled) {
        uMaxCount = *(uint *)(this + 0x32c); // +0x32c m_maxSpawnCount (e.g., max NPCs to spawn)
        if (0x1e < uMaxCount) {
            uMaxCount = 0x1e;
        }
        fMaxFloat = (float)(int)uMaxCount;
        if ((int)uMaxCount < 0) {
            fMaxFloat = fMaxFloat + DAT_00e44578; // constant for unsigned handling (likely 0.0)
        }
        fFraction = fMaxFloat * _DAT_00d5c458; // _DAT_00d5c458 is a multiplier, e.g., 0.3 (minimum fraction)
        iRand = _rand();
        // Calculate random offset from minimum to max
        uResult = (int)(longlong)ROUND((float)iRand * DAT_00e44590 * (float)((int)fMaxFloat - (int)fFraction));
        uSpawnCount = uResult + (int)fFraction;
        if (uMaxCount < uSpawnCount) {
            uSpawnCount = uMaxCount;
        }
        if ((uSpawnCount < 2) && (uSpawnCount = 2, uMaxCount < 3)) {
            uSpawnCount = uMaxCount;
        }
        setSpawnCount(uSpawnCount); // FUN_00701290, applies spawn count (e.g., spawns that many NPCs)
        return;
    }
    setSpawnCount(1); // default: spawn 1 if not enabled
    return;
}