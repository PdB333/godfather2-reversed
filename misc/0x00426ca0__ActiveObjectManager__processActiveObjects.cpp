// FUNC_NAME: ActiveObjectManager::processActiveObjects
void ActiveObjectManager::processActiveObjects(int32_t param_1)
{
    // Acquire mutex for the object list (global mutex at 0x00e2e6f0)
    FUN_00ab4db0(&DAT_00e2e6f0); // mutexLock(&g_objectListMutex)

    // First pass: iterate over linked list at this+0x4c (list head pointer)
    // Each node: [objectPtr (4 bytes)] [nextNodePtr (4 bytes)]
    for (Node* currentNode = *(Node**)(this + 0x4c);
         currentNode != nullptr;
         currentNode = currentNode->nextNode)
    {
        // Check if the object's state field (offset 0) is 1 (active)
        if (*(int32_t*)currentNode->objectPtr == 1)
        {
            // Call first update function on the active object
            FUN_004c7120((int32_t*)currentNode->objectPtr); // object::preprocess()
        }
    }

    // Second pass: another update with the parameter
    for (Node* currentNode = *(Node**)(this + 0x4c);
         currentNode != nullptr;
         currentNode = currentNode->nextNode)
    {
        if (*(int32_t*)currentNode->objectPtr == 1)
        {
            // Call second update function, passing the external parameter (e.g., delta time)
            FUN_004c7260((int32_t*)currentNode->objectPtr, param_1); // object::update(param_1)
        }
    }

    // Release mutex
    FUN_00ab4e70(); // mutexUnlock()
}