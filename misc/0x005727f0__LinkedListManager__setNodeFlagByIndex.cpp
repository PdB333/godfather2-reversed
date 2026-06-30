// FUNC_NAME: LinkedListManager::setNodeFlagByIndex
// Address: 0x005727f0
// Sets bit 0x10000000 (flag 28) on the node at the given index in a linked list.
// The list is stored as a head pointer at this+0x124, each node has next pointer at +0x124 and flags at +0x10.
// Returns true if the node exists and flag was set, false otherwise (null pointer or index out of range).

typedef int BOOL; // or use bool

class LinkedListNode {
public:
    uint32_t flags;       // +0x10
    // ... other members ...
    LinkedListNode* next; // +0x124
};

class LinkedListManager {
public:
    LinkedListNode* head; // +0x124
    // ... other members ...

    BOOL setNodeFlagByIndex(int index) {
        BOOL result = 0;
        if (this != NULL && index >= 0) {  // unaff_ESI is the index parameter (in EDX)
            LinkedListNode* node = this->head;  // param_1+0x124
            int count = 0;
            if (index > 0) {
                do {
                    node = node->next;  // each node's next at +0x124
                    if (node == NULL) {
                        return 0;       // early exit if list ends before index
                    }
                    count++;
                } while (count < index);
            }
            if (node != NULL) {
                node->flags |= 0x10000000;  // set bit 28
                result = 1;
            }
        }
        return result;
    }
};