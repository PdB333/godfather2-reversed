// FUNC_NAME: SimManager::registerSim
void SimManager::registerSim(void* simPtr)
{
    // DAT_01206880 is the global SimManager instance
    int** ppList = (int**)(*(int*)0x01206880 + 0x14); // pointer to list node pointer
    // Write vtable address for list node
    **(int***)ppList = &PTR_LAB_01126184; // set vtable of current node
    // Move to next slot (node size is 8 bytes: vtable + data)
    (*ppList)++;
    // Store the sim pointer
    *(void**)(*ppList) = simPtr;
    // Move past the stored pointer
    (*ppList)++;
}