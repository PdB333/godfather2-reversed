// FUNC_NAME: EventSystem::dispatchEvent
// Address: 0x005e5200
// Role: Dispatches an event to registered handlers based on event object pointer.
// Calling convention: Custom: this in ECX (or EDI?), eventObj in EAX, eventData on stack.
// Reconstructed as __thiscall with two explicit parameters for readability.

int __thiscall EventSystem::dispatchEvent(void* eventObj, int eventData) {
    int index;
    uint uVar2;

    // eventObj must be non-null
    if (eventObj != nullptr) {
        // Compute index: (eventObj - baseOfEventArray) / sizeof(EventObject) (0x74)
        // Base is stored at this+0x603c
        uVar2 = (uint)((int)eventObj - *(int*)((int)this + 0x603c)) / 0x74;

        // Ensure index is within 0x200 (max 512 events)
        if (uVar2 < 0x200) {
            // Access handler array at this+0x10, stride 0x30
            Handler* handler = (Handler*)((int)this + 0x10 + uVar2 * 0x30);

            if (handler != nullptr) {
                // If callback is registered, call it
                if (handler->callback != nullptr) {
                    handler->callback(handler->object, eventData, handler->userData);
                }

                // Call a generic handler function (likely for default processing)
                EventSystem::defaultProcess((int)this, handler->object, eventData);
            }
            return 1;
        }
    }
    return 1;
}

// Handler structure (size 0x30)
struct Handler {
    char unknown[0x24];        // +0x00: other fields
    void (*callback)(void* object, int eventData, void* userData); // +0x24
    void* userData;            // +0x28
    void* object;              // +0x2C
};

// Note: The function FUN_005e64b0 (called as defaultProcess) is not reconstructed here.
// It likely performs additional event propagation or default behavior.