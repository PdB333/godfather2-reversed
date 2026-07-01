// FUNC_NAME: GameObjectFactory::createGameObject
void __fastcall GameObjectFactory::createGameObject(unsigned int objectId)
{
    // Check if the game is ready to create objects
    bool isReady = isGameInitialized(); // FUN_00481660
    if (!isReady)
        return;

    // Allocate memory for the object (size 0x38 bytes)
    void* objectMemory = gameMemoryAlloc(0x38); // FUN_009c8e50, possible size for a small game object
    if (objectMemory == nullptr)
    {
        // Allocation failed; register a null object
        registerObject(nullptr); // FUN_00481690
        return;
    }

    // Construct the object on the allocated memory, passing the original identifier
    GameObject* newObject = constructGameObject(objectMemory, objectId); // FUN_008a9460, __thiscall with this==objectMemory

    // Register the newly created object with the manager
    registerObject(newObject); // FUN_00481690
}