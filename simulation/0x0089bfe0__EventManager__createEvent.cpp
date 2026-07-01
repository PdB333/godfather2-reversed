// FUNC_NAME: EventManager::createEvent
// Address: 0x0089bfe0
// Role: Creates an event object, initializes it with a type byte and two 32-bit values, then registers it with the global manager.

// Note: The function name is inferred from the pattern: it allocates 0x48 bytes (sizeof Event), calls a base constructor (FUN_0089be90) 
// passing the manager's 'this' pointer, sets fields at offsets 0x38, 0x3c, 0x40, and registers the new object.

class EventManager {
public:
    // Allocates and constructs an Event, then registers it.
    // param_2 (byte): event type/enum
    // param_3 (int): some ID or value
    // param_4 (int): some ID or value
    void __thiscall createEvent(char eventType, int param3, int param4) {
        if (!isGlobalHeapReady()) { // FUN_00481660 – likely heap/allocator check
            return;
        }

        Event* newEvent = (Event*) allocMemory(0x48); // FUN_009c8e50 – allocate 72 bytes
        if (newEvent == nullptr) {
            return;
        }

        // Base constructor initializes common Event fields using this (manager)
        initEventObject(this, &newEvent); // FUN_0089be90 – initializes with manager's reference (this)

        // Set specific fields
        newEvent->field_0x38 = eventType;   // +0x38
        newEvent->field_0x3c = param3;      // +0x3c
        newEvent->field_0x40 = param4;      // +0x40

        // Register the event with the global system (e.g., add to event list)
        registerObject(newEvent); // FUN_00481690
    }
};

// Helper forward declarations (actual implementations elsewhere)
extern bool isGlobalHeapReady();
extern void* allocMemory(size_t size);
extern void initEventObject(EventManager* manager, Event* obj);
extern void registerObject(void* obj);