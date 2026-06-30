// FUNC_NAME: EntityManager::removeByID
bool EntityManager::removeByID(ContainerDescriptor* pContainer, int id) {
    // pContainer->elements: array of IDs, pContainer->count: number of elements
    if (pContainer->count == 0) {
        return false;
    }

    int* current = pContainer->elements;
    for (uint i = 0; i < pContainer->count; i++) {
        if (*current == id) {
            // Found; call internal removal hooks
            this->onRemove();          // notifies object of removal
            this->removeSlot(i);       // shifts array down from index i
            return true;
        }
        current++;
    }
    return false;
}