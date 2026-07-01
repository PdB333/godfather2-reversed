// FUNC_NAME: EntityDataManager::getEntityShortID
short EntityDataManager::getEntityShortID(void* self)
{
    // Retrieve the internal data block pointer from the entity manager
    int* dataBlock = (int*)FUN_004baf90(self); // GET_ENTITY_DATA_BLOCK
    if (dataBlock != 0) {
        // Dereference the first field (likely an ID or type index) and convert to short
        // FUN_008b4e20 extracts a short value (e.g., lower 16 bits or mapping)
        return FUN_008b4e20(*dataBlock); // EXTRACT_SHORT_FROM_ID
    }
    return 0;
}