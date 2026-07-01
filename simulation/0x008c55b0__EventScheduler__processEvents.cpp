// FUNC_NAME: EventScheduler::processEvents
// Function address: 0x008c55b0
// Role: Processes a queue of events (type 1) from an array at +0x130, dispatching them if conditions are met.
// Class: EventScheduler (hypothesized based on EA EARS engine patterns)
// Offsets:
//   +0x54: scheduler owner ID (compared against target object's +0x40 owner field)
//   +0x130: pointer to array of EventEntry structs (size 0x1c each)
//   +0x134: number of entries in the array
// EventEntry layout (0x1c bytes):
//   +0x00: unknown (4 bytes)
//   +0x04: type (int, expected ==1 for this path)
//   +0x08: pointer to target object (must be non-null)
//   +0x0c: action character flag (triggered when non-zero)
//   +0x10: sub-object (passed to event processing functions)
//   +0x14-0x1b: padding or additional fields

void __thiscall EventScheduler::processEvents(void) {
    EventEntry* entries = *(EventEntry**)(this + 0x130);
    uint32_t count = *(uint32_t*)(this + 0x134);
    uint32_t i = 0;
    int byteOffset = 0; // cumulative offset into array (increment by 0x1c)

    if (count != 0) {
        do {
            EventEntry* entry = (EventEntry*)((uint8_t*)entries + byteOffset);
            char actionChar = *(char*)(entry + 0x0c); // flag at +0x0c

            if (actionChar != '\0') {
                // Process the sub-object at offset +0x10 (likely event payload)
                processEventSubObject((void*)((uint8_t*)entry + 0x10));
            }

            // Check if this is a targeted event (type == 1) with a valid target
            if (*(int*)(entry + 0x04) == 1 && *(void**)(entry + 0x08) != nullptr) {
                uint32_t targetOwner = *(uint32_t*)(*(void**)(entry + 0x08) + 0x40);
                uint32_t schedulerOwner = *(uint32_t*)(this + 0x54);
                if (targetOwner != schedulerOwner) {
                    // Dispatch the event: func(param_1, sub-object, actionChar, 1)
                    dispatchEventToTarget(this, (void*)((uint8_t*)entry + 0x10), actionChar, 1);
                }
            }

            i++;
            byteOffset += 0x1c;
        } while (i < count);
    }
}

// Callee stubs for clarity:
void processEventSubObject(void* subObj);   // FUN_008c3d90
void dispatchEventToTarget(void* scheduler, void* subObj, char actionChar, int mode); // FUN_006b3fe0