// FUNC_NAME: EventManager::processEvent
// Function at 0x00446f80
// Handles an event by dispatching to registered callbacks or default handler.
// this->0x1c flags, this->0x28 targetId, obj->0x2d0 callback count, obj->0xd0 callback array (pairs of id+func).
// If a matching callback is found, it's called with (targetId, time, userData).
// Otherwise, a target object is retrieved and default handling is performed.

void EventManager::processEvent(void* obj, uint32 userData, bool setFlag)
{
    uint32 targetId;
    void* targetObj;
    uint32 time;
    char eventValid;
    int i;
    int callbackCount;
    void** callbackArray;

    // Determine target ID: from field_28 or computed via helper
    if ((field_1c & 1) == 0) {
        targetId = getSomeId(field_28);  // FUN_004dafd0
    } else {
        targetId = field_28;
    }

    time = getCurrentTime();  // FUN_0043ab10

    // Prepare event object; obj may be modified
    obj = (void*)((uint32)obj & 0xffffff00);  // Clear low byte
    eventValid = validateEvent(obj, this, 1, &obj, &result);  // FUN_00446bf0

    updateEventQueue(obj, this);  // FUN_00446a60

    if (eventValid != 0) {
        // Search callback list in obj
        callbackCount = *(int*)((uint8*)obj + 0x2d0);
        callbackArray = (void**)((uint8*)obj + 0xd0);
        for (i = 0; i < callbackCount; i++) {
            if ((uint32)callbackArray[i*2] == targetId) {
                // Found matching event, call handler if not null
                if (callbackArray[i*2 + 1] != nullptr) {
                    ((void(*)(uint32, uint32, uint32))callbackArray[i*2 + 1])(targetId, time, userData);
                    return;
                }
                break;
            }
        }

        // No handler found; get target object
        targetObj = getObjectByUID(targetId);  // FUN_00483410
        if (targetObj != nullptr) {
            // Call default handler if low byte of obj (after validation) is zero
            if ((char)obj == 0) {
                defaultEventHandler(obj, targetObj, userData);  // FUN_004467c0
            }
            // Optionally set flag on target object
            if (setFlag != 0) {
                *(uint32*)((uint8*)targetObj + 0x14) |= 0x40000000;
            }
        }
    }
}