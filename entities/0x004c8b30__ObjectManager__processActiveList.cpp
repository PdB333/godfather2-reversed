// FUNC_NAME: ObjectManager::processActiveList
// Address: 0x004c8b30
// Role: Iterates over a global singly-linked list of objects and calls their first virtual method with argument 1.

void ObjectManager::processActiveList()
{
    // Global pointer to the head of the linked list (DAT_012054a8)
    Node* head = reinterpret_cast<Node*>(DAT_012054a8);
    
    // Traverse the list, processing each node and advancing the head pointer.
    // The head is updated before the virtual call to avoid reentrancy issues.
    while (head != nullptr)
    {
        // Retrieve the vtable pointer from the current node (offset +0x00)
        void** vtbl = reinterpret_cast<void**>(head->vtblPtr);
        
        // Move head to the next node (stored at offset +0x08)
        DAT_012054a8 = head->next;
        head = reinterpret_cast<Node*>(DAT_012054a8); // Note: Actually the loop condition uses global, but we update head for clarity
        
        // Call the first virtual function (index 0) with argument 1
        // This is likely a 'tick' or 'update' method with a delta time or a flag.
        typedef void (*VirtualFunc)(int);
        VirtualFunc func = reinterpret_cast<VirtualFunc>(vtbl[0]);
        func(1);
        
        // Re-read the global head for the next iteration
        head = reinterpret_cast<Node*>(DAT_012054a8);
    }
}

// Node structure for the linked list
// Offsets (relative to base):
// +0x00: void* vtblPtr;  // pointer to vtable
// +0x04: padding?       // not used in this function
// +0x08: Node* next;    // pointer to next node
struct Node
{
    void* vtblPtr;   // +0x00
    // unknown +0x04
    Node* next;      // +0x08
};