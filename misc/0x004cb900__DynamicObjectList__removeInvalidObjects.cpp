// FUNC_NAME: DynamicObjectList::removeInvalidObjects
// Address: 0x004cb900
// Role: Removes objects from internal list whose ID is not present in the global object registry.
//        Iterates through a dynamic array of game object pointers, checks their ID (offset +0x104)
//        against all registered objects from a global pool, and calls a removal function if not found.

void __thiscall DynamicObjectList::removeInvalidObjects(DynamicObjectList* this)
{
    // Get the global game object pool manager (singleton)
    ObjectPoolManager* poolMgr = GetGlobalObjectPoolManager();
    if (poolMgr == nullptr) {
        return;
    }
    // Get the object registry (contains all active objects)
    ObjectRegistry* registry = poolMgr->getRegistry(); // vtable +0x34 -> returns registry interface

    // Get the object ID map from the registry
    ObjectIdMap* idMap = registry->getIdMap(); // vtable +0x24 -> returns ID map object

    // Get count of registered objects
    int32_t registeredCount = idMap->getCount(); // vtable +0x3c (arg 0)

    // Current count of objects in this dynamic list
    int32_t currentCount = this->objectCount;
    int32_t index = 0;

    while (index < currentCount) {
        // Get the game object pointer from the internal array
        GameObject* obj = this->objectArray[index];
        int32_t objId = obj->id; // offset +0x104

        bool found = false;
        // Search through all registered objects
        for (int32_t regIdx = 0; regIdx < registeredCount; ++regIdx) {
            ObjectIdMapEntry* entry = idMap->getEntry(regIdx); // vtable +0x24 (regIdx)
            int32_t entryId = entry->getId(); // vtable +0xc

            if (entryId == objId) {
                found = true;
                break;
            }
        }

        if (found) {
            // Object still exists, move to next
            ++index;
        } else {
            // Object no longer present, remove it
            RemoveObjectFromList(obj->removalContext, obj); // offset +0x1a4 context pointer
            // Update the current list count (removal may shrink the list)
            currentCount = this->objectCount;
            // Do not increment index, as the next element has shifted into this position
        }
    }
}