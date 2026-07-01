// FUNC_NAME: ObjectFactory::allocateAndConstruct
void ObjectFactory::allocateAndConstruct(void* objectPtr, uint parameter)
{
    ObjectFactory* factory = nullptr;

    // If a valid memory location is provided, retrieve the factory singleton
    if (objectPtr != nullptr) {
        factory = (ObjectFactory*)GetFactorySingleton(g_objectFactorySingleton); // DAT_01131018 -> global factory instance
    }

    // Call virtual function at vtable offset 0x34 to get allocator or context
    uint allocator = factory->getAllocator(); // vtable+0x34

    // Initialize/construct the object using the allocator and parameter
    ConstructObject(objectPtr, allocator, parameter); // FUN_00892c50
}