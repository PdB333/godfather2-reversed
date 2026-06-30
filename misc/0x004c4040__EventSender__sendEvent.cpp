// FUNC_NAME: EventSender::sendEvent
void __thiscall EventSender::sendEvent(void* this, int param2, int param3, byte flags) {
    // Stack buffer for event data (16 bytes, but only used partially based on flags)
    int eventType;      // +0x00
    int eventSize;      // +0x04
    int eventFlags;     // +0x08
    int dataLow;        // +0x0C
    int dataHigh;       // +0x10

    // Default event: type 2, size 0x10, no flags
    eventType = 2;
    eventSize = 0x10;
    eventFlags = 0;

    if ((flags & 1) != 0) {
        // Alternate event layout: type 4, size 1 (or custom payload)
        dataLow = 4;
        dataHigh = 1;
        // Call virtual function at vtable[0] with pointer to custom payload (starting at dataLow)
        // Vtable is assumed to be stored at offset -4 from 'this' (compiler-specific layout)
        ((void (__thiscall*)(void*, int, int*))(*((int**)this - 1))[0])(this, param2, &dataLow);
        return;
    }
    // Default path: pass pointer to the full standard event structure
    ((void (__thiscall*)(void*, int, int*))(*((int**)this - 1))[0])(this, param2, &eventType);
}