// FUNC_NAME: LinkedList::LinkedList (copy constructor)
// This function is a copy constructor for a doubly linked list container.
// It deep copies all nodes from the source list (param_2) into the new list (this).
// Node structure: +0x00 next, +0x04 prev, +0x08... data (total 0x2C bytes)
// List structure: +0x00 head, +0x04 tail

typedef unsigned int uint32;
typedef unsigned char byte;

struct LinkedListNode {
    LinkedListNode* next;   // +0x00
    LinkedListNode* prev;   // +0x04
    byte data[0x2C - 8];    // remaining, total size 0x2C
};

struct LinkedList {
    LinkedListNode* head;   // +0x00
    LinkedListNode* tail;   // +0x04
};

// External functions used:
LinkedListNode* __stdcall allocateNode(uint32 size); // FUN_009c8e50, size = 0x2C
LinkedListNode* __thiscall copyNode(LinkedListNode* src); // FUN_008eacb0, clones a node

LinkedList* __thiscall LinkedList_LinkedList(LinkedList* this, LinkedList* source) {
    this->head = 0;
    this->tail = 0;
    
    LinkedListNode* srcNode = source->head;
    while (srcNode != 0) {
        LinkedListNode* newNode = allocateNode(0x2C);
        if (newNode != 0) {
            newNode = copyNode(srcNode); // copyNode returns a pointer to a new node initialized from srcNode
            newNode->next = 0;
            newNode->prev = this->tail;
            
            if (this->tail == 0) {
                this->head = newNode;
            } else {
                this->tail->next = newNode;
            }
            this->tail = newNode;
        }
        srcNode = srcNode->next;
    }
    
    return this;
}