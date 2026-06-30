// FUNC_NAME: GameStatManager::tryGetStatValue
// Address: 0x0045f1d0 - Attempts to retrieve a stat value if the data store and stat array are initialized
bool __thiscall GameStatManager::tryGetStatValue(int statKey, int* outValue) {
    // this+0x218: m_pDataStore (pointer to DataStore object)
    // DataStore+0x70: m_pStatArray (pointer to stat array)
    if ((this->m_pDataStore != 0) && (this->m_pDataStore->m_pStatArray != 0)) {
        int value = lookupStatValue(statKey);   // FUN_004dafd0 - resolves stat ID to value
        if (isStatsReady()) {                   // FUN_00573440 - checks if stat system is fully loaded
            *outValue = value;
            return true;
        }
    }
    return false;
}