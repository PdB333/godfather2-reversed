// FUNC_NAME: LinkedListManager::insertNewNode
struct LinkedListNode {
    int data;          // +0x00
    // padding/other fields 0x04-0x1b (unknown)
    LinkedListNode* prev; // +0x1c
    LinkedListNode* next; // +0x20
};

class LinkedListManager {
public:
    LinkedListNode* head; // +0x00
    LinkedListNode* tail; // +0x04

    void insertNewNode();
};

// Allocates a new node and inserts it before the tail (or as both head and tail if empty)
void __thiscall LinkedListManager::insertNewNode() {
    LinkedListNode* newNode = (LinkedListNode*)FUN_005c4410(0x24, 0);
    if (newNode == nullptr) {
        newNode = nullptr;
    } else {
        newNode->data = 0;       // offset +0x00
        newNode->prev = nullptr; // offset +0x1c
        newNode->next = nullptr; // offset +0x20
    }

    LinkedListNode* oldTail = tail;
    if (oldTail == nullptr) {
        // Empty list: node becomes both head and tail
        tail = newNode;
        head = newNode;
        return;
    }

    LinkedListNode* oldPrev = oldTail->prev; // node before the tail
    if (oldPrev != nullptr) {
        oldPrev->next = newNode;        // wire oldPrev to newNode
        newNode->prev = oldPrev;        // newNode's prev = oldPrev
    }
    newNode->next = oldTail;            // newNode's next = oldTail
    oldTail->prev = newNode;            // oldTail's prev = newNode

    if (tail == head) {
        // Only one element existed; new node becomes the new head
        head = newNode;
    }
}