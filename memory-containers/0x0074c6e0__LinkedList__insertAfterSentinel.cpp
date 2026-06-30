// FUNC_NAME: LinkedList::insertAfterSentinel
// Address: 0x0074c6e0
// This function inserts a node into a singly linked list after a sentinel head.
// The sentinel head is located at offset 0x48 within the container object.
// Node structure: [0] pointer to sentinel (or null), [4] next pointer.
// __thiscall: this = node to insert, param_2 = container with sentinel at +0x48 (or null)

struct LinkedListNode {
    int sentinelPtr; // offset 0x00: points to sentinel or null
    int next;        // offset 0x04: next node pointer
};

void __thiscall LinkedList::insertAfterSentinel(LinkedListNode* this, void* container)
{
    LinkedListNode* sentinel;

    // Determine sentinel address: container + 0x48, or null if container is null
    if (container == 0) {
        sentinel = 0;
    } else {
        sentinel = (LinkedListNode*)((char*)container + 0x48);
    }

    // Set this node's sentinel pointer
    this->sentinelPtr = (int)sentinel;

    // Initialize next to null
    this->next = 0;

    // If there is a sentinel, link this node after it
    if (sentinel != 0) {
        this->next = sentinel->next;                     // point to current first element
        sentinel->next = (int)this;                      // sentinel points to new node
    }
}