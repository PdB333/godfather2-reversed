// FUNC_NAME: EntityManager::removeEntityById
bool __fastcall EntityManager::removeEntityById(void *this, int entityId) {
    uint count = *(uint *)((int)this + 0x6018);
    int **arrayPtr = *(int ***)((int)this + 0x6014);
    uint i = 0;
    bool result = false;

    if (count != 0) {
        while (i < count) {
            int *entity = arrayPtr[i];
            if (entity != nullptr && *entity == entityId) {
                // Check if game is running before deletion
                if (isGameRunning(g_gameRunningFlag)) {
                    // Call virtual destructor or cleanup via global vtable
                    result = ((bool (**)(int *))(*g_allocatorVTable))[0x14 / 4](entity);
                    // Remove entity from internal list
                    updateEntityList();
                    // Free memory
                    deallocateObject(entity);
                }
                break;
            }
            i++;
        }
    }
    return result;
}