// FUNC_NAME: getEntityData
int getEntityData(int entityId, int extraData)
{
    int handle = getObjectById(entityId, 0);
    if (handle != 0) {
        int manager = getManagerSingleton();
        return processEntityData(manager, entityId, extraData, handle);
    }
    return 0;
}