// FUNC_NAME: EventScheduler::processEvents
// Address: 0x00991ad0
// Processes a linked list of event nodes, dispatching events in multiple phases.
// Each node has a next pointer (+0x4), an event ID (+0x44), and flags (+0x46).
// Nodes with bit 0 clear are processed; after the final phase, bit 0 is set.

// External dispatch functions (addresses from callees)
void dispatchEvent(void* context, void* messageType, int eventId); // 0x005c0d50
void finalizeEvent(); // 0x005c0d30 (no arguments, possibly cleanup)

// Event type constants (addresses of message handlers or type IDs)
const void* kEventTypePhase1 = (void*)0x009910e0;
const void* kEventTypePhase2 = (void*)0x00991110;
const void* kEventTypePhase3 = (void*)0x00990880;
const void* kEventTypePhase4 = (void*)0x00991140;
const void* kEventTypePhase5 = (void*)0x00991970;

// Node structure for the event list
struct EventNode {
    EventNode* next;      // +0x04
    short eventId;        // +0x44
    unsigned short flags; // +0x46 (bit 0 = processed)
};

// Manager structure (this)
struct EventScheduler {
    // ... other members ...
    EventNode* eventList; // +0x60
    // context data at +0x04 used in dispatchEvent
};

void __fastcall EventScheduler::processEvents(EventScheduler* this) {
    EventNode* node;

    // Phase 1: dispatch first event type for all unprocessed nodes
    node = this->eventList;
    while (node != nullptr) {
        if ((node->flags & 1) == 0) {
            dispatchEvent((void*)((int)this + 4), kEventTypePhase1, node->eventId);
        }
        node = node->next;
    }

    // Phase 2: finalize all unprocessed nodes (no event type)
    node = this->eventList;
    while (node != nullptr) {
        if ((node->flags & 1) == 0) {
            finalizeEvent();
        }
        node = node->next;
    }

    // Phase 3: dispatch second event type
    node = this->eventList;
    while (node != nullptr) {
        if ((node->flags & 1) == 0) {
            dispatchEvent((void*)((int)this + 4), kEventTypePhase2, node->eventId);
        }
        node = node->next;
    }

    // Phase 4: dispatch third event type
    node = this->eventList;
    while (node != nullptr) {
        if ((node->flags & 1) == 0) {
            dispatchEvent((void*)((int)this + 4), kEventTypePhase3, node->eventId);
        }
        node = node->next;
    }

    // Phase 5: dispatch fourth event type and mark node as processed
    node = this->eventList;
    while (node != nullptr) {
        if ((node->flags & 1) == 0) {
            dispatchEvent((void*)((int)this + 4), kEventTypePhase4, node->eventId);
            node->flags |= 1; // mark processed
        }
        node = node->next;
    }
}