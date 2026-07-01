// FUNC_NAME: EventScheduler::handleEvent
void __thiscall EventScheduler::handleEvent(int* eventData) {
    // Validate/initialize event data
    validateEvent(eventData);

    // Check event type against expected global type
    if (*eventData != g_expectedEventType) {
        return;
    }

    // Extract payload from event data
    int* payload = reinterpret_cast<int*>(eventData[1]); // +0x04
    int eventId = payload[2]; // +0x08
    int firstIndex = payload[4]; // +0x10
    int secondIndex = payload[5]; // +0x14

    // Access manager singleton (global at 0x0112b9b4)
    void* manager = *reinterpret_cast<void**>(reinterpret_cast<char*>(g_pManager) + 0x40);
    if (manager == nullptr) {
        return;
    }

    // Get context from manager (offset 0x60)
    void* context = *reinterpret_cast<void**>(reinterpret_cast<char*>(manager) + 0x60);

    // Check if this event is relevant: either matches owner ID or virtual predicate
    int ownerId = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x14);
    if (eventId == ownerId) {
        // Direct match
    } else {
        // Virtual call: vtable at (this - 0x3c), offset 0x2c (entry 11)
        int* vtable = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) - 0x3c);
        typedef bool (*IsRelevantFunc)(int);
        IsRelevantFunc isRelevant = reinterpret_cast<IsRelevantFunc>(vtable[11]);
        if (!isRelevant(eventId)) {
            return;
        }
    }

    // Remove callbacks if indices are valid
    if (firstIndex != -1) {
        int* vtable = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) - 0x3c);
        typedef void (*RemoveFunc)(void*, int);
        RemoveFunc remove = reinterpret_cast<RemoveFunc>(vtable[12]);
        remove(context, firstIndex);
    }
    if (secondIndex != -1) {
        int* vtable = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) - 0x3c);
        typedef void (*RemoveFunc)(void*, int);
        RemoveFunc remove = reinterpret_cast<RemoveFunc>(vtable[12]);
        remove(context, secondIndex);
    }
}