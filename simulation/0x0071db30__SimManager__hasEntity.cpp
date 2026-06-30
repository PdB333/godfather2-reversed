// FUNC_NAME: SimManager::hasEntity
bool __thiscall SimManager::hasEntity(int entityId)
{
    int count = *(int *)(this + 0x74); // number of entries in the array
    if (count <= 0) return false;

    int *entry = (int *)(this + 0x14); // base of entry array (each entry is 12 bytes)
    for (int i = 0; i < count; ++i)
    {
        int rawVal = entry[0];  // first field of entry (0x0)
        int adjusted = (rawVal != 0) ? (rawVal - 0x48) : 0;
        if (adjusted == entityId)
            return true;
        entry += 3; // advance by 3 ints (12 bytes)
    }
    return false;
}