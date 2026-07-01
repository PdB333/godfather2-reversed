// FUNC_NAME: EntityDataManager::getEntityPointer
// Function address: 0x008934e0
// Role: Resolves an entity handle to a pointer to the actual entity object.
// Calls EntityDataManager::lookupHandleInternal(handle) to get an internal record,
// then dereferences offset +0x8 to get the entity pointer.
// Returns true if the handle was found and the pointer is valid.

bool EntityDataManager::getEntityPointer(unsigned int handle, void** outPointer)
{
    // Internal lookup: returns a record pointer if handle is valid
    int internalRecord = this->lookupHandleInternal(handle);
    if (internalRecord != 0) {
        // Record structure has entity pointer at offset +0x8
        *outPointer = *(void**)(internalRecord + 8);
    }
    return internalRecord != 0;
}