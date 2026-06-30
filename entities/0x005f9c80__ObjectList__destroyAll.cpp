// FUNC_NAME: ObjectList::destroyAll
// Function address: 0x005f9c80
// Role: Destroys all elements in a doubly linked list and reinitializes the list to empty.
// The list stores polymorphic objects with a vtable; each element is deleted via virtual function at vtable index 1 (deallocation with size 0xc).

struct ListNode {
    void* vtable;        // +0x00
    ListNode* next;      // +0x04
    ListNode* prev;      // +0x08
    // data follows (size 0xc total? since deallocation size 0xc)
};

class ObjectList {
public:
    ListNode* head;      // +0x18 (offset 0x18 from this)
    int count;           // +0x1C (offset 0x1C from this)

    // __thiscall (ECX -> ESI)
    void destroyAll() {
        ListNode* iter = head->next;        // first real element (head->next)
        ListNode* nextNode;
        head->next = head;                  // reinitialize list head
        head->prev = head;
        count = 0;

        if (iter != head) {
            do {
                nextNode = iter->next;      // save next before delete
                // Call virtual destructor with deallocation size 0xc (12 bytes)
                // vtable index 1 (second function) expects a size parameter
                (*(void(__thiscall**)(ListNode*, int))iter->vtable[1])(iter, 0xc);
                iter = nextNode;
            } while (nextNode != head);
        }
    }
};