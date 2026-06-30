// FUNC_NAME: ObjectFactory::createObject
int** __thiscall ObjectFactory::createObject(int** outObject, int someId, ObjectFactory* factory, int size, int extraData)
{
    // Initial state: clear output pointer
    *outObject = nullptr;

    if (factory != nullptr)
    {
        uint32 flags = 0;
        ObjectClass* objectClass = nullptr;

        // Look up a class by its ID (hash) - vtable +0x10
        if ((**(code***)factory)[4](0xae986323, &objectClass) != 0 && objectClass != nullptr)
        {
            // Get creation flags for this size - subclass vtable +0x98
            objectClass->getFlags(&flags, size);
        }

        // Store factory pointer for later
        int* factoryBackup = factory;

        // Determine allocation mode based on bit 0 of flags
        int mode;
        if ((flags & 1) == 0)
        {
            mode = 2;
        }
        else
        {
            mode = 3;
        }

        // Extract alignment/other info
        uint32 alignment = flags >> 2;

        int extraDataCopy = extraData;

        // Fetch some value from factory sub-object at offset 0x54 (+4 for vtable call)
        int uVar3 = (**(code***)(factory[0x15]))[1]();  // factory->subObject__getSomething()

        // Call factory method to initialize creation - vtable +0x58
        int uVar4 = (**(code***)factory)[0x16](0, &mode);  // factory->prepareCreation(0, &mode)

        // Perform the actual allocation / object creation
        int* newHandle = FUN_004df270(&objectClass, someId, uVar3, uVar4);

        // Clean up previous output state if any
        if (*outObject != nullptr)
        {
            *(int**)(*outObject + 8) = nullptr;  // clear prev link
            *outObject = nullptr;
        }

        // Transfer the handle to the output
        int newObject = *newHandle;  // newHandle is a pointer to the object pointer
        *outObject = newObject;

        if (newObject != nullptr)
        {
            // Store back-pointer to output slot in the object at offset +8
            *(int**)(newObject + 8) = outObject;
            *newHandle = 0;  // clear the temporary handle (move semantics)
        }

        // Clear class instance flag at offset 8
        if (objectClass != nullptr)
        {
            objectClass[2] = 0;  // objectClass->someFlag = false
        }
    }

    return outObject;
}