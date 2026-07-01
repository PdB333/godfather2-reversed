// FUNC_NAME: EntityManager::isEntityActive
// Function address: 0x0077bea0
int EntityManager::isEntityActive(void* entity) {
    if (entity != 0) {
        // Check if the global entity manager (stored at DAT_01131074) reports this entity as active
        return (int)getGlobalEntityStatus(g_entityManager); // FUN_0043b870
    }
    return 0;
}