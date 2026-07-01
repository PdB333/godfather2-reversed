// FUNC_NAME: EventScheduler::onReferenceReleased

// Global game time (likely updated each frame)
extern int gCurrentTime; // DAT_01205224

struct ScheduledEvent {
    ScheduledEvent* next;  // +0x00 linked list next
    int unk04;
    int unk08;
    int timeOffset;        // +0x0C remaining delay or time until fire
};

class EventScheduler {
    // +0x00 vtable?
public:
    // +0x54 reference count (shared ownership)
    // +0x58 lastUpdateTime (game time when last processed)
    // +0x48 head of linked list of ScheduledEvent
    // +0x7C extraTimer (optional, additive timer)

    void __thiscall onReferenceReleased() {
        int* refCount = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x54);
        --(*refCount);

        if (*refCount == 0) {
            // Compute elapsed time since last update
            int deltaTime = gCurrentTime - *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x58);

            // Update all scheduled events in the linked list
            ScheduledEvent* event = *reinterpret_cast<ScheduledEvent**>(reinterpret_cast<char*>(this) + 0x48);
            while (event != nullptr) {
                if (event->timeOffset != 0) {
                    event->timeOffset += deltaTime; // Advance timer
                }
                event = event->next;
            }

            // Also update an optional extra timer at +0x7C
            int* extraTimer = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x7C);
            if (*extraTimer != 0) {
                *extraTimer += deltaTime;
            }

            // Reset last update time
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x58) = 0;
        }
    }
};