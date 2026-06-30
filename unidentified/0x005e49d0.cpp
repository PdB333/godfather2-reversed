// FUN_005e49d0: EntityDataManager::createFromEntry
// Function at 0x005e49d0: Attempts to create an entity instance from a resource entry.
// Given a resource identifier (name or handle) and an optional user data parameter,
// it looks up the entry and, if found and allowed by flags, creates and returns an instance.
// Returns 0 on failure.

int __thiscall EntityDataManager::createFromEntry(int resourceName, int userData)
{
    int flags = 0;
    char outFlag = 0;
    int entryHandle = findEntry(resourceName, &outFlag, &flags); // FUN_005f0560
    if (entryHandle != 0 && flags != 0) {
        return createInstance(userData, entryHandle); // FUN_005e4a20
    }
    return 0;
}