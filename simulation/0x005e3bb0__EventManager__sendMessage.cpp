// FUNC_NAME: EventManager::sendMessage
// Address: 0x005e3bb0
// Sends a 32-bit message (event type 2) to a target object through the global event manager.
// The manager is a global struct (at 0x01223518) with a function table pointer at offset +4.
// The dispatched function is the first entry in that table.

struct EventMessage {
    uint32_t type;   // +0x00
    uint32_t data;   // +0x04
    uint32_t flags;  // +0x08
};

struct EventManager {
    uint32_t field0;       // +0x00
    void** functionTable;  // +0x04
};

extern EventManager g_eventManager; // located at DAT_01223518

void sendMessage(void* targetObject, uint32_t messageData) {
    if (g_eventManager.functionTable != nullptr && targetObject != nullptr) {
        EventMessage msg;
        msg.type = 2;          // e.g., EVENT_TYPE_ACTIVATE or EVENT_TYPE_INTERACT
        msg.data = messageData;
        msg.flags = 0;

        // The function pointer is stored as the first element of the function table.
        // It takes two arguments: the target object and a pointer to the event message.
        auto dispatchFunc = reinterpret_cast<void (*)(void*, EventMessage*)>(
            g_eventManager.functionTable[0]);
        dispatchFunc(targetObject, &msg);
    }
}