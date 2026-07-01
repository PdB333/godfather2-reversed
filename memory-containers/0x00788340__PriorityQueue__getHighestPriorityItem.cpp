// FUNC_NAME: PriorityQueue::getHighestPriorityItem

#include <cstddef>

// Node in a singly linked list priority queue.
// Each node stores a next pointer, a priority value, and a pointer to the actual data.
struct PriorityListNode {
    PriorityListNode* next;        // +0x00
    int             padding;       // +0x04 (unused or prev? observed as ignored)
    float           priority;      // +0x08
    void*           data;          // +0x0C
};

// Container class for the priority queue.
// Struct layout:
//   +0x00: head (PriorityListNode*)
//   +0x04: sentinelOrField (int) – used as fallback return value when list is empty
class PriorityQueue {
public:
    PriorityListNode* head;         // +0x00
    int               sentinelOrField; // +0x04

    // Returns a pointer to the data of the node with the highest priority.
    // If the queue is empty, returns a pointer to the container's sentinel field.
    void* getHighestPriorityItem() {
        PriorityListNode* curr = head;
        PriorityListNode* best = nullptr;

        while (curr != nullptr) {
            if (best == nullptr || curr->priority > best->priority) {
                best = curr;
            }
            curr = curr->next;
        }

        if (best != nullptr) {
            return best->data;          // +0x0C offset (piVar2 + 3)
        }
        // Return the address of the sentinel field as a default
        return reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(this) + offsetof(PriorityQueue, sentinelOrField));
    }
};