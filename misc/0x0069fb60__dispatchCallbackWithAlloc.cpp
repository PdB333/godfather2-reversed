// FUNC_NAME: dispatchCallbackWithAlloc
void dispatchCallbackWithAlloc(int unused, void** callbackFuncPtr)
{
    int allocatedData; // +0x00: 4-byte value allocated/initialized
    initTempData(&allocatedData, 4, 4); // FUN_0049c470: creates a temporary event/handle with size 4 and param 4 (possibly type/flags)
    ((void (*)(int))(*callbackFuncPtr))(allocatedData); // invoke the callback with the newly created data
    return;
}