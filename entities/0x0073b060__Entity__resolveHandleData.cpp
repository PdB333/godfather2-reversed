// FUNC_NAME: Entity::resolveHandleData
// Address: 0x0073b060
// Role: Checks if the entity (this) is non-null, then retrieves data from a global manager.

// Global manager pointer (0x01131038)
extern void* g_entityManager;

// Internal function at 0x0043b870 - retrieves data from the manager
extern undefined4 getGlobalData(void* manager);

undefined4 Entity::resolveHandleData() {
    if (this != 0) {
        return getGlobalData(g_entityManager);
    }
    return 0;
}