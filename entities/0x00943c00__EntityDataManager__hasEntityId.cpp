// FUNC_NAME: EntityDataManager::hasEntityId
bool __thiscall EntityDataManager::hasEntityId(int entityId) {
    int index;
    IdTable* table;
    IdEntry* entry;

    if (entityId == -1) {
        return false;
    }

    // Convert ID to a bucket index (likely hash or direct mapping)
    index = hashToIndex(&entityId); // FUN_00941490
    if (index < 0) {
        return false;
    }

    // Access the ID table stored at +0xF0
    table = *(IdTable**)(this + 0xF0);
    if (table == nullptr) {
        return false;
    }

    // Each entry is 8 bytes: pointer to object + padding? Actually entry->pObject is a pointer,
    // and the object's ID is at offset 4 of that object.
    entry = &table->entries[index];
    if (entry->pObject == nullptr) {
        return false;
    }

    // Verify that the object's stored ID matches the requested ID (collision check)
    return (entry->pObject->id == entityId);
}