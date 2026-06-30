// FUNC_NAME: EntityManager::findObjectById
int EntityManager::findObjectById(int id) {
    int count = *(char *)(this + 0x79); // +0x79: number of active indices
    if (count != 0) {
        for (int i = 0; i < count; i++) {
            uint index = *(byte *)(this + 0x7a + i); // +0x7a: array of byte indices
            int *typeArray = *(int **)(this + 0x1bc); // +0x1bc: pointer to manager
            int typeId = *(int *)(typeArray[0x24 / 4] + index * 4); // manager+0x24: type/flags array
            if (typeId != -2) {
                // Call some debug/notification function from global vtable
                (**(code **)(*DAT_01205590 + 4))();
            }
            int **objectArray = *(int ***)(typeArray + 0x20 / 4); // manager+0x20: object pointer array
            int *object = objectArray[index];
            if (*(int *)(object + 0x70 / 4) == id) { // object+0x70: ID field
                return (int)object;
            }
        }
    }
    return 0;
}