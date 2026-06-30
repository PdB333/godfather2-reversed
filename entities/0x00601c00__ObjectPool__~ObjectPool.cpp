// FUNC_NAME: ObjectPool::~ObjectPool

class ObjectPool {
    // Internal node structure used for both bucket sentinels and allocated nodes
    struct Node {
        Node* data;      // +0x00: points to actual node (for sentinel) or payload? (for allocated)
        Node* next;      // +0x04: next node in circular list (sentinels) or global list
    };

    void** vtable;                   // +0x00: vtable pointer (set twice during destruction)
    Node*  allocatedListHead;        // +0x04: head of global list of all allocated nodes
    // ... unknown fields (offsets 0x08 to 0x37) ...
    Node*  buckets;                  // +0x38: pointer to array of sentinel nodes (each 8 bytes)
    unsigned short bucketCount;      // +0x3c: number of buckets (as unsigned short)

public:
    // Destructor: removes all nodes from each bucket and clears the global allocated list
    void __fastcall ~ObjectPool();
};

void __fastcall ObjectPool::ObjectPool() {
    unsigned int idx;
    Node* sentinel;
    Node* nodeToRemove;
    Node* prevNode;
    Node* walker;

    // Step 1: Set vtable to destructor-specific vtable (marks object as being destroyed)
    vtable = (void**)&PTR_FUN_00e40838;

    if (bucketCount != 0) {
        idx = 0;
        do {
            sentinel = &buckets[idx];
            nodeToRemove = sentinel->data;  // pointer to actual node (if any) in this bucket

            if (nodeToRemove != nullptr) {
                prevNode = nodeToRemove->next;

                if (prevNode == sentinel) {
                    // Node is the only one in the bucket: update its next to sentinel's next
                    nodeToRemove->next = sentinel->next;
                } else {
                    // Walk the circular list to find the node before the sentinel
                    walker = prevNode->next;
                    while (walker != sentinel) {
                        prevNode = walker;
                        walker = prevNode->next;
                    }
                    prevNode->next = sentinel->next;
                }
                // Clear sentinel's data pointer (no longer pointing to any node)
                sentinel->data = nullptr;
            }
            idx++;
        } while (idx < bucketCount);
    }

    // Step 2: Set vtable to base class vtable (indicates destruction is complete)
    vtable = (void**)&PTR_FUN_00e32808;

    // Step 3: Clear the global allocated list: zero out all nodes' data and next
    Node* currentNode = allocatedListHead;
    while (currentNode != nullptr) {
        Node* nextNode = currentNode->next;
        currentNode->next = nullptr;
        currentNode->data = nullptr;
        currentNode = nextNode;
    }
}