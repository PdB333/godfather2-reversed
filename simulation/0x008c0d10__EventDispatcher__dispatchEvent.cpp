// FUNC_NAME: EventDispatcher::dispatchEvent
void __thiscall EventDispatcher::dispatchEvent(int thisPtr, int eventData, char isPostEvent)
{
    int *listenerNode;
    char isActive;
    int eventId;
    int *listenerObj;
    void (**vtable)();

    // Get the listener list from this+0x88 (likely a linked list container)
    undefined4 *listContainer = (undefined4 *)getListenerList(*(undefined4 *)(thisPtr + 0x88));
    if ((0 < (int)listContainer[2]) && (*(int *)(eventData + 0x4c) != 0) &&
        (eventId = validateEvent(*(int *)(eventData + 0x4c)), eventId != 0)) {
        // Iterate over the linked list
        for (listenerNode = (int *)*listContainer; listenerNode != (int *)0x0; listenerNode = (int *)listenerNode[1]) {
            int listenerId = *listenerNode;
            isActive = isListenerActive(listenerId, 2);
            if (isActive == '\0') {
                if (listenerId == 0) goto skipListener;
                listenerObj = (int *)getListenerObject(gListenerManager);
            } else {
                int globalId = getGlobalListenerId();
                if (globalId == 0) {
skipListener:
                    listenerObj = (int *)0x0;
                } else {
                    listenerObj = (int *)getListenerObject(gListenerManager);
                }
            }
            // Choose virtual function based on isPostEvent
            if (isPostEvent == '\0') {
                vtable = *(void (***)())(*listenerObj + 0x24); // onEvent
            } else {
                vtable = *(void (***)())(*listenerObj + 0x20); // onEventPost
            }
            (*vtable)(eventId);
        }
    }
    return;
}