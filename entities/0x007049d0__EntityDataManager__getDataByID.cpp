// FUNC_NAME: EntityDataManager::getDataByID
// Address: 0x007049d0
// Maps a game object ID to its data entry in the internal table (offset 0x24, stride 0x14).
// Returns zero if ID is zero or not found (via callee FUN_00704860 which converts ID to index).

undefined4 __thiscall EntityDataManager::getDataByID(int objectId) {
    undefined4 result = 0;
    if (objectId != 0) {
        int index = FUN_00704860(objectId); // transform ID to table index (likely hash or direct mapping)
        result = *(undefined4 *)(this + 0x24 + index * 20); // +0x24 base of array, each entry 0x14 bytes
    }
    return result;
}