// FUNC_NAME: EventManager::sendEventToObject
void EventManager::sendEventToObject(void* targetObject)
{
    // Get the singleton EventManager instance
    EventManager* eventMgr = (EventManager*)FUN_009c8f80();

    // Build a message struct: messageId=2, dataSize=0x10, flags=0
    // This likely represents a specific event type (e.g., "Activate" or "Trigger")
    Message msg;
    msg.messageId = 2;      // +0x00: event type ID
    msg.dataSize = 0x10;    // +0x04: size of associated data (16 bytes)
    msg.flags = 0;          // +0x08: flags (none)

    // Call the virtual dispatch function on the EventManager singleton
    // The first argument is the target object, second is the message struct
    (*(void(__thiscall*)(EventManager*, void*, Message*))eventMgr->vtable[0])(eventMgr, targetObject, &msg);
}