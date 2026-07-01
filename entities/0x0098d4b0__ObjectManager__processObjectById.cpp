// FUNC_NAME: ObjectManager::processObjectById
// Function address: 0x0098d4b0
// Role: Retrieves an object by ID and then processes it with the same ID.
void ObjectManager::processObjectById(void* manager, int id)
{
    void* obj = getObjectById(manager, id); // FUN_004dafd0: likely retrieves object from manager by ID
    processObject(obj, id);                 // FUN_0098d330: processes the object with the given ID
}