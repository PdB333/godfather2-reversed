// FUNC_NAME: GodfatherGameManager::constructor
undefined4* __fastcall GodfatherGameManager::constructor(undefined4* thisPtr)
{
    int subObjSize = 0x1c;
    undefined4* subObject;
    int allocResult;

    // Store this instance in global singleton pointer
    g_pGodfatherGameManager = thisPtr;

    // Set vtable pointer (polymorphic base)
    *thisPtr = &GodfatherGameManager_vtable;

    subObject = thisPtr; // local_4 initially points to thisObj? Wait, local_4 is set to param_1 then reassigned.
    // Actually, original: local_4 = param_1; then later: local_4 = (undefined4 *)0xff00c3c3; So it's reused.

    // Allocate memory for a sub-object (size 0x1c)
    allocResult = operatorNew(subObjSize);
    if (allocResult != 0) {
        // Call sub-object constructor
        initializeSubObject();
    }

    // Store a magic value for debug/logging
    subObject = (undefined4*)0xff00c3c3;
    // Call debug logging function with message type 0x13 and pointer to subObject
    debugPrint(0x13, &subObject);

    return thisPtr;
}