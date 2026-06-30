// FUNC_NAME: EARSObject::processEvent
void __thiscall EARSObject::processEvent(int eventCode, int someValue) {
    // eventCode is passed in EAX, someValue in EDI
    // this pointer in ECX
    if (eventCode == 1) {
        // Structure for sub_408A00: points to a buffer and this object
        struct EventData {
            int* buffer;     // +0x00: pointer to data at this+0x64
            EARSObject* obj; // +0x04: this pointer
            int zero;        // +0x08: reserved/flag (set to 0)
        } localData;

        localData.buffer = *(int**)(this + 0x64); // offset +0x64: buffer pointer
        localData.obj = this;
        localData.zero = 0;

        sub_408A00(&localData, 0); // unknown function, passes struct and 0

        if (g_eventCallback != nullptr) {
            g_eventCallback(this + 0x6c); // offset +0x6c: some object/context
        }
    }
    else if (eventCode == 3 && *(int*)(this + 0xE8) == someValue) {
        *(int*)(this + 0xE8) = 0; // offset +0xE8: target/state ID
    }
    // No other cases handled
}