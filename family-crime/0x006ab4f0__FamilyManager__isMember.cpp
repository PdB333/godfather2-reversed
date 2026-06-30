// FUNC_NAME: FamilyManager::isMember
bool FamilyManager::isMember(Entity* entity) {
    // Retrieve the singleton FamilyManager instance (FUN_005e3070)
    FamilyManager* manager = getFamilyManagerInstance();
    // Check if the entity belongs to this family manager's family (FUN_005e6520)
    int result = checkFamilyMembership(manager, entity);
    return result != 0;
}