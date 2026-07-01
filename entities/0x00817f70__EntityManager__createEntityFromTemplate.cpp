// FUNC_NAME: EntityManager::createEntityFromTemplate
uint8_t EntityManager::createEntityFromTemplate(int32_t templateId, int32_t param2, int32_t param3) {
    int32_t localArray[3] = {0, 0, 0}; // Output buffer: [0]=entityPtr, [1]=?, [2]=?
    uint8_t result = allocateEntity(templateId, localArray); // Returns status/success
    initializeEntity(localArray, param2, param3); // Initialize with additional params
    if (localArray[0] != 0) {
        operatorDelete((void*)localArray[0]); // Free if allocation failed? (unusual pattern: allocate then free if non-null)
    }
    return result;
}