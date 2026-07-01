// FUNC_NAME: EventScheduler::dispatchEventWithEntities
void __thiscall EventScheduler::dispatchEventWithEntities(int this, int extraParam)
{
    // Search for a registered handler matching event type 0x637b907
    uint handlerCount = *(uint*)(this + 0x28); // Number of registered handlers
    int* handlerArray = *(int**)(this + 0x24); // Array of handler pointers
    int foundHandlerIndex = 0;
    int* handlerIter = handlerArray;
    while (foundHandlerIndex < handlerCount) {
        if (*(int*)(*handlerIter + 0x54) == 0x637b907) {
            break;
        }
        foundHandlerIndex++;
        handlerIter++;
    }

    // Process pending events (likely flushes or updates event queue)
    EventScheduler::processEvents(); // FUN_008c2f40

    // Build an event message on the stack
    EventMessage message; // sizeof: 0xD? extended by padding to 0x10?
    memset(&message, 0, sizeof(message));
    message.header = *DAT_00e44758; // some global event header constant
    message.flags = 0;
    message.extra = 0;
    message.hasArray = 0;

    // Initialize the message to accept an array of entities (set to empty)
    EventScheduler::setEventDataArray(0, this); // FUN_009c8f10(0) – reset array pointer
    message.flags = 1; // indicates that an entity array is present
    message.extra = extraParam; // caller-provided parameter
    message.hasArray = 1;

    // Obtain the entity manager containing the list of active entities
    // *(DAT_012233a0 + 4) is a pointer to a pointer; check it's valid and not a sentinel
    int* entityManagerPtr = **(int***)(DAT_012233a0 + 4);
    if (entityManagerPtr != 0 && entityManagerPtr != (int*)0x1f30) {
        int manager = EntityManager::getInstance(DAT_01130fa0); // FUN_0043b870
        if (manager != 0) {
            int entityCount = *(int*)(manager + 0x2c); // number of entities in manager
            if (entityCount != 0) {
                // Iterate over all entities and collect those matching a condition
                for (int i = 0; i < entityCount; i++) {
                    int entity = SimManager::getNextSimObject(); // FUN_007351c0 – uses internal iterator
                    // Check if entity has the required flag (bit 2 of +0x5c)
                    if ((*(uint*)(entity + 0x5c) >> 2 & 1) == 0) {
                        // Add entity to the dynamic array within the message
                        if (message.entityCount == message.entityCapacity) {
                            int newCapacity = (message.entityCapacity == 0) ? 1 : message.entityCapacity * 2;
                            Memory::reallocArray(&message.entityArray, &message.entityCapacity, newCapacity); // FUN_006b1e10
                        }
                        message.entityArray[message.entityCount] = entity;
                        message.entityCount++;
                    }
                }
            }
        }
    }

    // Dispatch the event to the handler found earlier
    EventScheduler::callHandler(0x637b907, &message); // FUN_008c7cb0

    // If we allocated an entity array, attach it to the event for later cleanup
    if (message.entityArray != 0) {
        EventScheduler::setEventDataArray(message.entityArray, this); // FUN_009c8f10(local_c, this)
    }
}