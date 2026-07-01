// FUNC_NAME: EventDispatcher::dispatch
void __thiscall EventDispatcher::dispatch(void* eventData) {
    uint count = *(uint*)(this + 0xdc);
    if (count != 0) {
        // Array of listener objects at +0xd8
        void** listeners = *(void***)(this + 0xd8);
        for (uint i = 0; i < count; i++) {
            void* listener = listeners[i];
            // Call 4th virtual function (offset 0xc) on listener with eventData
            (*(void(__thiscall**)(void*))(*(uint*)listener + 0xc))(eventData);
        }
    }
}