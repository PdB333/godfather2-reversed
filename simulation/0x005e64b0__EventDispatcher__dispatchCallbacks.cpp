// FUNC_NAME: EventDispatcher::dispatchCallbacks
// Address: 0x005e64b0
// Iterates over registered callback list, calling each with provided arguments.

void __thiscall EventDispatcher::dispatchCallbacks(void* thisPtr, void* arg0, void* arg1) {
    uint count = *(uint*)((char*)thisPtr + 0x6030); // Number of registered callbacks
    if (count != 0) {
        // Pointer to array of callback entries (offset +0x602c)
        uint entryArray = *(uint*)((char*)thisPtr + 0x602c);
        if (entryArray != 0) {
            for (uint i = 0; i < count; i++) {
                // Each entry is 8 bytes: first 4 = function pointer, next 4 = userData
                void (*callback)(void*, void*, void*) = *(void (**)(void*, void*, void*))(entryArray + i * 8);
                void* userData = *(void**)(entryArray + i * 8 + 4);
                callback(arg0, arg1, userData);
            }
        }
    }
}