// FUNC_NAME: GameObjectFactory::createObject
int __cdecl GameObjectFactory::createObject(int ownerPtr, int creationParam)
{
    int allocParams[3] = {2, 0x10, 0}; // allocation flags (persistent, aligned, zero)
    GameObject* newObj = (GameObject*)MemoryManager::allocate(0x68, allocParams, creationParam);
    if (newObj != NULL)
    {
        return newObj->initialize(ownerPtr);
    }
    return 0;
}