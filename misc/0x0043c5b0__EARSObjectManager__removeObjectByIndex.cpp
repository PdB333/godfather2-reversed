// FUNC_NAME: EARSObjectManager::removeObjectByIndex
void __thiscall EARSObjectManager::removeObjectByIndex(uint objectIndex)
// Removes an object from the pool by index. Validates index is in range [0, 63] and not 0xFFFFFFFF.
{
    if ((objectIndex != 0xffffffff) && (objectIndex < 0x40))
    {
        this->internalRemoveObject(objectIndex); // FUN_0043c4e0
    }
}