// FUNC_NAME: GodfatherGameManager::isFeatureActive
// Address: 0x00785ee0
// Checks if a specific feature flag (0x100) is active for the given entity.
// Uses a global singleton manager (DAT_01131040) and its internal data block.

typedef bool (__thiscall* IsFeatureActiveFunc)(void* self, int flag);

bool __cdecl GodfatherGameManager::isFeatureActive(void* entity) {
    if (entity == nullptr) return false;

    // Retrieve the manager's internal data from the global pointer
    int* managerData = (int*)FUN_0043b870(DAT_01131040);
    if (managerData == nullptr) return false;

    // Call the virtual function at vtable offset 0x1c to test the flag
    IsFeatureActiveFunc isFeature = (IsFeatureActiveFunc)(*(int*)(*managerData + 0x1c));
    return isFeature(managerData, 0x100) != 0;
}