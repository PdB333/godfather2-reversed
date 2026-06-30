// FUNC_NAME: ObjectManager::getValidObjectId
uint ObjectManager::getValidObjectId()
{
    uint id = getBaseId(); // FUN_00424c90 returns current id from this object
    if (id < 4)
    {
        return generateFallbackId(); // FUN_004a1ee0 generates a new fallback id
    }
    // Mask off low byte (clear invalid bits) – id must be multiple of 256?
    return id & 0xffffff00;
}