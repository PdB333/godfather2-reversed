// FUNC_NAME: maybePerformAction
// Address: 0x004df3c0
// Role: Conditionally performs an action if a key array is non-zero and a manager returns a valid resource.
// Takes an output pointer (outResult), a key array of 4 ints, and three additional parameters.
// If the key array has any non-zero element, it retrieves a resource via getSomeManager(). If that resource is valid (non-null first field),
// it calls applySomeAction() with that resource and the three parameters, and returns outResult unchanged.
// Otherwise, it sets *outResult to 0 and returns outResult.
uint32_t* __cdecl maybePerformAction(uint32_t* outResult, int32_t* keyArray, uint32_t arg3, uint32_t arg4, uint32_t arg5)
{
    int32_t* resourcePtr;

    // Check if any of the four ints in keyArray are non-zero (key is valid)
    if ((keyArray[0] != 0 || keyArray[1] != 0) || (keyArray[2] != 0 || keyArray[3] != 0)) {
        // Retrieve a resource handle from some manager (FUN_004e0f60)
        resourcePtr = (int32_t*)getSomeManager();
        // If resource exists and its first field (likely an object pointer or reference count) is non-zero
        if ((resourcePtr != (int32_t*)0x0) && (*resourcePtr != 0)) {
            // Perform the action using the resource and the three extra parameters (FUN_004df210)
            applySomeAction(*resourcePtr, arg3, arg4, arg5);
            return outResult;
        }
    }
    // If key was null/zero or manager returned null resource, set output to 0 (failure)
    *outResult = 0;
    return outResult;
}