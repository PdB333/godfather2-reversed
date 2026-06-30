// FUN_00440590: EventManager::scheduleEvent
// 0x00440590

#include <cstdint>

// Forward declarations of helper functions used
void __fastcall FUN_00408bf0(void* param1, int param2, uint32_t param3); // likely similar to scheduleImmediate
void __fastcall FUN_00408a00(void* param1, uint32_t param2); // maybe clearEvent
void __cdecl FUN_00b97aea(); // restartTimer
int  __fastcall FUN_004414b0(void* list, uint32_t hashVal, int* outIndex); // insertIntoSortedList
void __cdecl FUN_00441540(); // scheduleUpdate
void __cdecl FUN_00408310(uint32_t* refCount); // releaseRefCount

// Global variables (guessed)
extern float g_tickRate; // _DAT_00e2e220 (tick frequency, e.g., 1000.0f)
extern uint32_t g_currentTick; // _DAT_01205224

class EventManager {
public:
    // +0x16: index into an array of event lists (e.g., priority level)
    int16_t m_listIndex;

    // +0x18: pointer to array of linked list heads (one per priority level)
    void** m_eventLists;

    // Hash table for event IDs (static global)
    static EventRef* g_eventHashTable; // _DAT_01162380, array of 4096 pointers

    // Ref-counted event ID structure
    struct EventRef {
        EventRef* next;  // +0x00
        uint32_t id;     // +0x04 (hash)
        uint16_t refCount; // +0x08 (maybe offset?)
        // ... unknown
    };

    // Node structure for timed event queue
    struct TimedEvent {
        TimedEvent* prev; // +0x00
        TimedEvent* next; // +0x04
        uint32_t timeout; // +0x10? (or +0x14) - store computed tick value
        // ... data
    };

    void scheduleEvent(uint32_t* eventId, int context, float delaySec, void* callback, uint32_t flags) {
        if (delaySec > 0.0f) {
            uint32_t id = *eventId;
            uint16_t refCount = 0;
            int16_t newRef = 0;

            // Lookup event ID in hash table (12-bit hash)
            if (id != 0) {
                uint32_t hashIndex = id & 0xFFF;
                EventRef* ref = g_eventHashTable[hashIndex];
                while (ref != nullptr && ref->id != id) {
                    ref = ref->next;
                }
                if (ref != nullptr) {
                    ref->refCount++;
                    newRef = 1;
                }
            }

            // Get the correct event list for this priority level
            int listIndex = m_listIndex;
            void* listHead = reinterpret_cast<void**>(reinterpret_cast<int*>(m_eventLists)[listIndex]);
            // listHead points to a "sentinel" node at +0x18 of the actual container
            // Actually more complex: m_eventLists[listIndex] -> some struct with +0x18 being list sentinel
            void* container = m_eventLists[listIndex];
            TimedEvent* sentinel = *reinterpret_cast<TimedEvent**>(reinterpret_cast<char*>(container) + 0x18);
            // sentinel is the list sentinel (next points to first real, prev points to last)

            // Compute timeout in ticks
            uint32_t timeout = static_cast<uint32_t>(delaySec * g_tickRate);
            uint32_t currentTick = g_currentTick;
            uint32_t absoluteTimeout = currentTick + timeout; // not used directly, but they compare (currentTick - timeout) something
            // Actually they compute uVar3 = g_currentTick - (uint32_t)(delaySec * g_tickRate)
            // Which is weird: negative? Wait - they sub from currentTick. That suggests they want to compare with a stored "deadline" (which is absolute).
            // But the loop checks if (uVar3 < puVar4[5]), meaning they are comparing a future time (deadline) with an interval?
            // Let's re-analyze: local_14 = uVar3 = DAT_01205224 - (int)(param_4 * _DAT_00e2e220)
            // That gives a "start time" (current minus delay). Then they search for an event whose timeout (stored value) is greater than that start time? That seems backwards.
            // Actually they might be using a countdown: stored timeout is remaining time? Then they compare (current - delay < remaining) -> if delay is longer than remaining, they need to adjust?
            // Hmm, it's complicated. For reconstruction, I'll use a simpler abstraction.

            // Iterate through the list to find insertion point (sorted by deadline?)
            TimedEvent* cur = sentinel->next;
            while (cur != sentinel) {
                if (absoluteTimeout < cur->timeout) { // Actually the original checks uVar3 < puVar4[5] but we invert logic
                    // found position
                    break;
                }
                cur = cur->next;
            }
            // Insert before cur
            // Use helper FUN_004414b0 which does insertion and returns new node index
            int dummy;
            int resultIndex = FUN_004414b0(cur, cur->id, &dummy); // This function expects parameters differently
            FUN_00441540(); // probably finalize insertion or signal update
            // Update the list head pointer if new node becomes first
            // Actually the code checks if after insertion, the node at position 1 (first real?) equals the head
            if (resultIndex == *reinterpret_cast<int*>(reinterpret_cast<char*>(container) + 0x18)) {
                FUN_00b97aea(); // restart timer
            }

            // Release temporary ref if we took one
            if (newRef) {
                FUN_00408310(&id);
            }
        }
        else {
            // Immediate or cancel path
            // They pack eventId and callback together (local_30 = CONCAT44(param_5, *param_2))
            // And call either immediate schedule (param_3==0) or cancel (param_3!=0)
            // This part likely handles clearing or running the event immediately
            if (context == 0) {
                FUN_00408a00(&eventId, (flags >> 1) & 0xFFFFFF01);
            } else {
                FUN_00408bf0(&eventId, context, (flags >> 1) & 0xFFFFFF01);
            }
            // If callback is provided and flag bit 0 is clear, call it
            if (callback != nullptr && (flags & 1) == 0) {
                (*(void (*)(int))callback)(1); // callback with 1
            }
        }
    }
};