// FUNC_NAME: EventManager::processObjectEvent
// Address: 0x0051a9f0
// Role: Iterates a global linked list of objects, checks if a specific 64-bit event (from GetCurrentEventId()) matches the object's event filter, and if so, sets/clears flags on the object.

// Object structure offsets (relative to base pointer):
// +0x0C: uint32_t flags
// +0x10: uint32_t sourceID (compared to this pointer, or 0 for all)
// +0x14: Object* next (linked list)
// +0x70: uint32_t eventIdLow
// +0x74: uint32_t eventIdHigh

// Global head of linked list (DAT_01205514)
Object* g_objectListHead;

// Returns the current 64-bit event ID from the engine
uint64_t GetCurrentEventId();  // FUN_0051d730

// Notification callback after marking object
void OnObjectEventFlagChanged(); // FUN_0051b120

void __thiscall EventManager::processObjectEvent(void)
{
    uint64_t currentEventId = GetCurrentEventId();
    Object* obj = g_objectListHead;
    
    while (obj != nullptr)
    {
        // Check if object matches: either sourceID is 0 (broadcast) or matches this pointer,
        // and the stored event ID matches the current one.
        if ( (unaff_ESI == 0 || unaff_ESI == obj->sourceID) && // unaff_ESI is the 'this' pointer of the caller (could be a handler)
             (obj->eventIdLow == (uint32_t)currentEventId) &&
             (obj->eventIdHigh == (uint32_t)(currentEventId >> 32)) )
        {
            // If flag 0x20000 (OBJECT_FLAG_EVENT_PENDING) is not set, set it and call notification
            if ((obj->flags & 0x20000) == 0)
            {
                obj->flags |= 0x20000;
                OnObjectEventFlagChanged();
            }
            // Clear flag 0x40000 (OBJECT_FLAG_EVENT_ACTIVE) 
            obj->flags &= 0xFFFBFFFF; // Clears bit 18 (0x40000)
        }
        
        obj = obj->next; // +0x14
    }
}