// FUNC_NAME: ObjectFactory::createSceneObject
void ObjectFactory::createSceneObject()
{
    // Allocate memory for scene object (size 0x98 = 152 bytes)
    SceneObject* newObject = static_cast<SceneObject*>(MemoryManager::allocate(152));
    if (newObject != nullptr)
    {
        // Placement initialization - calls constructor at 0x00411790
        newObject->SceneObject();
    }
}