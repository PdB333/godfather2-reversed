// FUNC_NAME: sendEvent
void sendEvent(void* receiver, uint eventData)
{
    // Global pointer to event manager pointer (at DAT_01223518+4)
    // Structure: EventData { int type; int data; int unused; }
    int** eventMgrPtr = (int**)(DAT_01223518 + 4);
    if (*eventMgrPtr != 0 && receiver != 0)
    {
        int eventBuf[3]; // EventData: type=2, data=eventData, unused=0
        eventBuf[0] = 2;   // event type 2
        eventBuf[1] = eventData; // event data
        eventBuf[2] = 0;   // padding/unused
        // Call dispatch function from event manager's vtable
        void (*dispatch)(void*, int*) = (void (*)(void*, int*))(**eventMgrPtr);
        dispatch(receiver, eventBuf);
    }
}