// FUNC_NAME: ListContainer::releaseAll

class ListContainer {
public:
    // Offsets (int-sized, 4 bytes each):
    // +0x00 (this[0]): head of singly linked list (SomeNode*)
    // +0x04 (this[1]): unused? (padding or other member)
    // +0x08 (this[2]): unused? 
    // +0x0C (this[3]): pointer to a single object (void*)
    // +0x10 (this[4]): pointer to a vtable-like function table (int*)

    struct SomeNode {
        SomeNode* next; // +0x04 relative to node
        // Node does not have a vtable; release function is supplied by container
    };

    SomeNode* head;           // offset 0x00
    // int unused1;           // offset 0x04
    // int unused2;           // offset 0x08
    void* singleObject;       // offset 0x0C
    void** functionTable;     // offset 0x10 (cast from int*)

    void releaseAll() {
        // Iterate over singly linked list (next at offset +0x04)
        SomeNode* current = head;
        while (current) {
            SomeNode* next = current->next;
            // Call virtual function at index 1 (vtable[1]) with current object and flag 0
            typedef void (*ReleaseFunc)(void* obj, int flag);
            ((ReleaseFunc)(functionTable[1]))(current, 0);
            current = next;
        }
        // Release the single object if present
        if (singleObject) {
            ((ReleaseFunc)(functionTable[1]))(singleObject, 0);
        }
        // Call final cleanup virtual function at index 3 (vtable[3])
        typedef void (*CleanupFunc)();
        ((CleanupFunc)(functionTable[3]))();
    }
};