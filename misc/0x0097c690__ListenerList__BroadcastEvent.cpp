// FUNC_NAME: ListenerList::BroadcastEvent

void __thiscall ListenerList::BroadcastEvent(int eventData) {
    // +0xD8: pointer to array of handler pointers
    // +0xDC: count of handlers
    unsigned int idx = 0;
    if (this->handlerCount != 0) {
        do {
            // Get handler object and its vtable, then call method at vtable+0x10 (4th virtual function)
            void* handler = this->handlers[idx];
            void** vtable = *(void***)handler;
            typedef void (*HandlerFunc)(int);
            HandlerFunc callback = (HandlerFunc)(vtable[4]); // vtable index 4 = +0x10 offset
            callback(eventData);
            idx = idx + 1;
        } while (idx < this->handlerCount);
    }
}