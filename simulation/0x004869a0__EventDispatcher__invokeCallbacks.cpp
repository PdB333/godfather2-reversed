// FUNC_NAME: EventDispatcher::invokeCallbacks
void __fastcall EventDispatcher::invokeCallbacks(EventDispatcher* this) {
    // Iterate over a list of callback entries stored between begin (offset +0x14) and current (offset +0x18)
    // Each entry is a structure with a pointer to a function followed by its argument data
    while (*(int*)((char*)this + 0x18) != *(int*)((char*)this + 0x14)) {
        int** currentEntry = *(int***)((char*)this + 0x18); // Dereference to get pointer to the current callback entry
        // The first element of the entry is the function pointer
        void (*callbackFunc)(EventDispatcher*, void*) = (void (*)(EventDispatcher*, void*))*currentEntry;
        // Advance the current pointer (offset +0x18) to the next entry
        *(int***)((char*)this + 0x18) = currentEntry + 1;
        // Invoke the callback, passing 'this' and the remaining data after the function pointer (the arguments)
        callbackFunc(this, currentEntry + 1);
    }
}