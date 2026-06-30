// FUNC_NAME: ObjectManager::getObjectIdByName
// Function address: 0x0043c1c0
// Role: Looks up an object ID by string name, returning -1 on failure.

int __thiscall ObjectManager::getObjectIdByName(void* thisPtr, const char* name)
{
    int index;
    int id;

    if (name != nullptr && *name != '\0')
    {
        // Likely a hash lookup or string-to-index conversion (0x004dafd0)
        index = hashNameToIndex(name);
        if (index != -1)
        {
            // Retrieve or create object by index (0x0043c140)
            id = getObjectIdByIndex(thisPtr, index, 1);
            return id;
        }
    }
    return -1;
}