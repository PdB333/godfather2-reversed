// FUNC_NAME: LinkedList::clone
// Function at 0x004265d0: Deep copy a singly linked list of 3-field nodes.
// Each node: +0: int key, +4: int data, +8: Node* next. Total 12 bytes.
// param_1 = pointer to source list head (Node*)
// param_2 = pointer to allocator vtable (first function is allocate)
// Returns pointer to new list head.

struct Node {
    int key;       // +0x00
    int data;      // +0x04
    Node* next;    // +0x08
};

// Allocator vtable: first entry is allocate function
// AllocFunc(void* self, int size, void* stackOutput) -> void* allocatedMemory
typedef void* (*AllocFunc)(void*, int, void*);

struct Allocator {
    AllocFunc allocate;  // +0x00
};

Node* __fastcall LinkedList_clone(Node* head, Allocator* alloc) {
    Node* newHead = nullptr;

    // Only clone if list is non-empty (head->key != 0 OR head->next != nullptr)
    if (head->key != 0 || head->next != nullptr) {
        // Count nodes in source list
        int count = 0;
        Node* current = head;
        do {
            current = current->next;
            count++;
        } while (current != nullptr);

        // Allocate memory for 'count' nodes (12 bytes each)
        // The alloc function is called with size and a pointer to stack locals for alignment
        int stackDummy[3] = {0, 0, 0};  // local_c, local_8, local_4
        newHead = (Node*)alloc->allocate(alloc, count * sizeof(Node), stackDummy);

        // Copy first node
        // First 8 bytes: key and data
        *reinterpret_cast<__int64*>(newHead) = *reinterpret_cast<__int64*>(head);
        // Next pointer at +8
        newHead->next = head->next;

        // Copy subsequent nodes
        Node* prevNew = newHead;
        Node* src = head->next;
        while (src != nullptr) {
            // Next new node starts 12 bytes after previous new node
            Node* newNode = (Node*)((char*)prevNew + sizeof(Node));  // +0x0C

            // Link previous new node to this one
            prevNew->next = newNode;

            // Copy first 8 bytes (key and data)
            *reinterpret_cast<__int64*>(newNode) = *reinterpret_cast<__int64*>(src);
            // Copy next pointer (at offset 8 of source)
            newNode->next = src->next;

            // Advance
            prevNew = newNode;
            src = src->next;
        }

        // Terminate the new list
        prevNew->next = nullptr;
    }

    return newHead;
}