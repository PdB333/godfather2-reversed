// FUNC_NAME: EventScheduler::processEvents
// Address: 0x005dc2f0
// Processes a linked list of events, calling a handler on each, and then cleaning up.
// The list is stored in a sentinel structure pointed to by this+8.
// Returns 1 if events were processed, 0 otherwise.

#include <cstdint>

class EventScheduler {
    struct Sentinel {
        // Offset +0x00: unknown (first few bytes of sentinel)
        // Offset +0x1c: points to the next (first event node) in the list
        // Offset +0x20: points to the current node (head) to process
        // Sentinel node is used as a circular list; next mark if empty points to itself.
    };

    struct EventNode {
        // Offset +0x00: unknown (first word, often a vtable or data)
        // Offset +0x10 (piVar3[4]): pointer to the next event node
    };

    void* vtable; // +0x00 (provided by class)
    Sentinel* eventList; // +0x08: pointer to the sentinel of the event list
    // +0x10: vtable pointer (we already have vtable as first member, but offset 0x10 might be another vtable? Actually based on param_1+0x10 call, it's likely a vtable)
    uint8_t _pad[0x10 - sizeof(void*) - sizeof(Sentinel*)]; // adjust padding, not exact
};

extern void assert_failed(); // FUN_00b97aea - debug assertion
extern void processEvent(Sentinel* list, uint8_t buffer[8], Sentinel* sentinel, EventNode* node); // FUN_005dec30
extern void releaseEventNode(); // FUN_005dcdc0
extern void freeEventNode(EventNode* node); // FUN_009c8eb0
extern void cleanupEventList(); // FUN_005de360

int __thiscall EventScheduler::processEvents() {
    // this is param_1
    Sentinel* sentinel = reinterpret_cast<Sentinel*>(reinterpret_cast<uint8_t*>(this) + 8);
    EventNode* currentNode;
    uint8_t buffer[8] = {0};

    if (sentinel != nullptr) {
        currentNode = sentinel->current; // offset +0x20: pointer to first node to process

        while (currentNode != 0) {
            // Get the head of the list (first node)
            EventNode* firstNode = sentinel->next; // offset +0x1c: points to the first event node

            // Debug check: if firstNode is the sentinel itself (empty list) -> assert
            if (reinterpret_cast<void*>(firstNode) == reinterpret_cast<void*>(sentinel->next)) {
                assert_failed();
            }

            // Save the next node after the current one before processing (in case current gets removed)
            EventNode* nextNode = currentNode->next; // offset +0x10: next pointer

            // Process the current node
            processEvent(sentinel, buffer, sentinel, currentNode);

            if (nextNode != 0) {
                // Release and free the next node (if it exists)
                releaseEventNode(); // may affect global state
                freeEventNode(nextNode);
            }

            // Re-fetch the sentinel pointer (in case it was modified) and the new head
            sentinel = reinterpret_cast<Sentinel*>(reinterpret_cast<uint8_t*>(this) + 8);
            currentNode = sentinel->current; // offset +0x20
        }

        // After all nodes processed, return success
        cleanupEventList();
        (reinterpret_cast<void (*)()>(reinterpret_cast<uintptr_t*>(reinterpret_cast<uint8_t*>(this) + 0x10)[0] + 4))(); // call vtable+4 (likely destructor/dealloc)
        return 1;
    }

    // No list -> just cleanup and call virtual destructor
    cleanupEventList();
    (reinterpret_cast<void (*)()>(reinterpret_cast<uintptr_t*>(reinterpret_cast<uint8_t*>(this) + 0x10)[0] + 4))();
    return 0;
}