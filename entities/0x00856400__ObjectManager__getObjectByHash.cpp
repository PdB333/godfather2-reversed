// FUNC_NAME: ObjectManager::getObjectByHash
// 0x00856400: Retrieves an object by type hash and index from the object manager.
uint32 ObjectManager::getObjectByHash(uint32 objectHash, uint32 param_2, uint32 param_3, int param_4)
{
    // Known object type hashes (likely from EA EARS engine)
    const uint32 HASH_ENTITY = 0x4ecfbe13;
    const uint32 HASH_OBJECT = 0x332d5a20;
    const uint32 HASH_ACTOR = 0xF26FB813; // -0xd9047ed

    if (objectHash == 0 ||
        (objectHash != HASH_ENTITY && objectHash != HASH_OBJECT && objectHash != HASH_ACTOR))
    {
        return 0;
    }

    ObjectManager* pManager = getObjectManagerInstance(); // FUN_00852d10
    int objectIndex = param_4;

    // Check if manager exists and its first four fields are nonzero (indicates active state)
    if (pManager != nullptr &&
        (pManager->field_0 != 0 || pManager->field_4 != 0 || pManager->field_8 != 0 || pManager->field_C != 0))
    {
        objectIndex = pManager->getObjectByIndex(0); // FUN_004461c0(pManager, 0)
    }

    if (objectIndex == 0)
    {
        return 0;
    }

    uint32 result = retrieveObject(objectHash, objectIndex, param_4, param_3); // FUN_00855d40
    return result;
}