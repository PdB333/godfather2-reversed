// FUNC_NAME: ResourceManager::createAndAttach
bool __cdecl ResourceManager::createAndAttach(int key, int context, RefCounted* targetRef)
{
    // Local array for output pointer and auxiliary data
    int resultPtr[2] = {0, 0};
    bool success = false;

    // Attempt to create a resource from the given key and context
    // The internal function sets resultPtr[0] to a newly allocated resource if successful
    // resultPtr[1] is passed as an auxiliary output (maybe a counter or identifier)
    FUN_004df270(resultPtr, &context, key, context, 0, &resultPtr[1]);

    if (resultPtr[0] != 0)
    {
        // Attach the newly created resource to the target reference object
        FUN_004df7f0(targetRef);
        success = true;

        // Clean up the local resource pointer by nulling its internal data
        if (resultPtr[0] != 0)
        {
            *(int*)(resultPtr[0] + 8) = 0;   // +0x08 likely points to resource data
            resultPtr[0] = 0;
        }
    }

    // Decrement the reference count of the target reference object
    if (targetRef != 0)
    {
        targetRef->refCount--;
        if (targetRef->refCount == 0)
        {
            // Invoke virtual destructor via vtable at offset +0x04
            (*(void(__thiscall**)(RefCounted*))targetRef->vtable[1])(targetRef);
        }
    }

    return success;
}