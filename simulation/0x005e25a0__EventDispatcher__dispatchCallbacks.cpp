// FUNC_NAME: EventDispatcher::dispatchCallbacks
// Address: 0x005e25a0
// Role: Iterates over a list of callback function pointers and invokes each with the provided parameters plus a stored context argument.
// The class holds a count (uVar1 at +0x173c) and an array of 8-byte entries at +0x1738.
// Each entry: first 4 bytes = function pointer, next 4 bytes = context pointer passed as third argument.

void __thiscall EventDispatcher::dispatchCallbacks(uint param_2, uint param_3)
{
    uint callbackCount = *(uint *)(this + 0x173c);   // Number of registered callbacks
    if (callbackCount != 0) {
        uint i = 0;
        do {
            uint callbackEntryPtr = *(uint *)(this + 0x1738) + i * 8; // Base of callback array
            void (*func)(uint, uint, void*) = *(void (**)(uint, uint, void*))(callbackEntryPtr); // Function pointer
            void* context = *(void **)(callbackEntryPtr + 4); // Context argument
            func(param_2, param_3, context);
            i++;
        } while (i < callbackCount);
    }
}