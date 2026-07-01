// FUNC_NAME: IdListContainer::findIndexOfCurrentId
uint __fastcall IdListContainer::findIndexOfCurrentId(int this)
{
    int targetId = getCurrentContextId();
    uint count = *(uint *)(this + 0x68); // +0x68: number of elements
    if (count == 0) {
        return 0xFFFFFFFF;
    }
    int* idArray = *(int**)(this + 0x64); // +0x64: pointer to array of IDs
    for (uint i = 0; i < count; i++) {
        if (idArray[i] == targetId) {
            return i;
        }
    }
    return 0xFFFFFFFF;
}