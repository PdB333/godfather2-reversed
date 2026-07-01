// FUNC_NAME: GameManager::QueryAttribute

int __thiscall GameManager::cachedAttributeQuery(int entityId)
{
    char bFound;
    int* pEntityData;
    int tempValue;

    // Look up entity data by ID (e.g., via a global hash table)
    pEntityData = (int*)LookupEntityData(entityId, 0);
    if (pEntityData != nullptr) {
        tempValue = 0;
        // vtable+0x10: virtual bool getPropertyByHash(uint hash, int& outValue)
        // 0x254cce9 is likely a hash for a specific attribute/flag
        bFound = (**(code**)(*pEntityData + 0x10))(0x254cce9, &tempValue);
        if (bFound && (this != nullptr)) {
            // vtable+0x154: condition check (e.g., isEnabled, isCurrentlyActive)
            bFound = (**(code**)(*reinterpret_cast<int**>(this) + 0x154))();
            if (bFound) {
                // vtable+0x160: return the final value (e.g., getCachedValue)
                return (**(code**)(*reinterpret_cast<int**>(this) + 0x160))();
            }
        }
    }
    return 0;
}