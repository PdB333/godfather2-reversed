// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::~EARSObject(int* thisPtr)
{
    struct LocalContext {
        int* self;      // +0x00: pointer to this object
        // further fields if used
    } ctx;
    int* ptrToSelf;     // local_1c
    int magic;          // local_18
    void (*cleanupFunc)(); // local_14 - unknown function pointer
    void* childObj;     // derived from param_1[6]

    // Set vtable to derived class during destruction
    *thisPtr = (int)&PTR_FUN_00e312cc;   // +0x00: derived vtable

    // Prepare context for a manager call
    ptrToSelf = thisPtr;                  // pointer to this object
    magic = 0x2a7ed975;                   // magic/id
    cleanupFunc = FUN_0044afa0;           // some cleanup routine
    ctx.self = thisPtr;                   // store pointer in context

    // Call manager with global reference and context
    FUN_00486cd0((int*)DAT_01223380, &ctx);

    // Clean up child object if present (offset +0x18)
    childObj = (void*)thisPtr[6];         // member at +0x18
    if (childObj != NULL) {
        FUN_009c8f10(childObj);           // delete or release child
    }

    // Switch to base vtable for base destruction
    *thisPtr = (int)&PTR_LAB_00e31354;    // +0x00: base vtable

    // Mark global state as inactive
    DAT_01223444 = 0;                     // global flag
}