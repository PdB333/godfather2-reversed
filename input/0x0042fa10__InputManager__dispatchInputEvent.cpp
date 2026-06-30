// FUNC_NAME: InputManager::dispatchInputEvent
void __fastcall InputManager::dispatchInputEvent(int thisPtr, undefined4 eventType, undefined4 param1, undefined4 param2)
{
    // +0x3a40: baseCallback (function pointer taking pointer to EventData)
    // +0x3a54: overrideCallback (function pointer taking baseCallback pointer and pointer to EventData)
    // +0x39f8: someData (stored in event as offset 4)
    // +0x3350: userDataPtr (stored as offset 5)
    
    int *baseCallback = (int *)(thisPtr + 0x3a40);
    
    // Proceed only if either callback is registered
    if (*(int *)(thisPtr + 0x3a54) != 0 || *baseCallback != 0) {
        // Build event data structure on stack
        struct EventData {
            undefined4 field0;   // eventType (param2)
            undefined4 field4;   // param1
            undefined4 field8;   // param2
            undefined4 fieldC;   // some data from this+0x39f8
            int field10;         // pointer to this+0x3350
        } eventData;
        
        eventData.field0 = eventType;
        eventData.field4 = param1;
        eventData.field8 = param2;
        eventData.fieldC = *(undefined4 *)(thisPtr + 0x39f8);
        eventData.field10 = thisPtr + 0x3350;
        
        if (*(void (__fastcall **)(int *, EventData *))(thisPtr + 0x3a54) != (void (__fastcall **)(int *, EventData *))0) {
            // Use override callback: takes baseCallback pointer and event data
            (*(void (__fastcall *)(int *, EventData *))(*(int *)(thisPtr + 0x3a54)))(baseCallback, &eventData);
        } else {
            // Use base callback: takes only event data
            (*(void (__fastcall *)(EventData *))*baseCallback)(&eventData);
        }
    }
}