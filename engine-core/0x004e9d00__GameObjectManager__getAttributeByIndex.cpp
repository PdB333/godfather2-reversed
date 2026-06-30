// FUNC_NAME: GameObjectManager::getAttributeByIndex
int GameObjectManager::getAttributeByIndex(unsigned int index)
{
    int result = s_databaseReady; // DAT_012054f8 - global flag indicating if database is ready
    if ((s_databaseReady == 0) && 
        (index < s_objectManager->count) && // s_objectManager->count at +0x0c
        (s_objectManager->objectArray[index] != nullptr)) // array at +0x04
    {
        // Call virtual function at vtable+0x0c to get an inner object
        void* innerObj = (*(code**)(s_objectManager->objectArray[index]->vtable + 0x0C))();
        if (innerObj != nullptr)
        {
            // Call virtual function at vtable+0x50 to retrieve the attribute value
            result = (*(code**)(innerObj->vtable + 0x50))();
        }
    }
    return result;
}