// FUNC_NAME: EventScheduler::processPendingEvent
// Address: 0x00568410
// Role: Dispatches a pending event stored at `this+0x28` and `this+0x2C` when the scheduler
// is ready (virtual check at vtable+0x8c). Retrieves the global event dispatcher via
// FUN_00ad8d40, obtains a handler (vtable+0x34), and invokes the event processor
// (vtable+0x10) with the stored IDs and two additional parameters.
void __thiscall EventScheduler::processPendingEvent(int this, unsigned int param2, unsigned int param3)
{
    // Offsets relative to this:
    // +0x28 : first pending event identifier (ID or pointer)
    // +0x2C : second pending event identifier
    int* pendingId1 = (int*)(this + 0x28);
    int* pendingId2 = (int*)(this + 0x2C);

    if (*pendingId1 != 0 || *pendingId2 != 0)
    {
        // Virtual function at vtable offset 0x8c (index 35) – checks if scheduler can process
        code** vtable = (code**)*((int*)this);
        typedef bool (__thiscall *IsReadyFunc)(void*);
        IsReadyFunc isReady = (IsReadyFunc)(vtable[0x8c / 4]);
        if (isReady(this))
        {
            // Global singleton accessor – returns pointer to central event dispatcher
            void* dispatcher = (void*)FUN_00ad8d40();
            if (dispatcher != 0)
            {
                // Obtain a handler object from the dispatcher (vtable offset 0x34, index 13)
                code** dispVtable = (code**)*((int*)dispatcher);
                typedef void* (__thiscall *GetHandlerFunc)(void*);
                GetHandlerFunc getHandler = (GetHandlerFunc)(dispVtable[0x34 / 4]);
                void* handler = getHandler(dispatcher);
                if (handler != 0)
                {
                    // Call the event processing function on the handler (vtable offset 0x10, index 4)
                    // Signature: void process(void* handler, int id1, int id2, uint param2, uint param3)
                    code** handlerVtable = (code**)*((int*)handler);
                    typedef void (__thiscall *ProcessEventFunc)(void*, int, int, unsigned int, unsigned int);
                    ProcessEventFunc processEvent = (ProcessEventFunc)(handlerVtable[0x10 / 4]);
                    processEvent(handler, *pendingId1, *pendingId2, param2, param3);

                    // Clear pending event fields after dispatch
                    *pendingId1 = 0;
                    *pendingId2 = 0;
                }
            }
        }
    }
}