// FUNC_NAME: CNodeList::addNodeAfter
// Insert a new node after the node pointed to by *nodePtrPtr. The new node is allocated from the internal array.
// +0x00: dataArray (int*) - pointer to array of nodes (each node is two ints: data + next)
// +0x04: size (int) - number of nodes currently stored
// +0x08: capacity (int) - number of slots allocated in dataArray
// Node layout: +0x00 data, +0x04 next (pointer to next node in linked list)

struct Node {
    int data;  // +0x00: payload (usually a pointer to an external object)
    Node* next; // +0x04: next node in the intrusive list
};

struct CNodeList {
    Node* dataArray; // +0x00
    int size;        // +0x04
    int capacity;    // +0x08
};

void __thiscall CNodeList::addNodeAfter(int* nodePtrPtr) {
    // nodePtrPtr is a pointer to a Node* (the node after which we insert)
    Node** afterNode = (Node**)nodePtrPtr;
    
    // Check if we need to grow the internal array
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        FUN_008a8870(newCapacity); // void reallocate(int newCapacity)
    }
    
    // Get pointer to the new node slot at the end of the array
    Node* newNode = &dataArray[size];
    size++;
    
    if (newNode != nullptr) {
        // Set the new node's data to the value stored at *nodePtrPtr
        // (which is the external pointer to an object that has a 'next' field at +0x04)
        newNode->data = *nodePtrPtr;
        newNode->next = nullptr;
        
        int externalObjPtr = *nodePtrPtr;
        if (externalObjPtr != 0) {
            // externalObjPtr is a pointer to an object that itself contains a next pointer at +0x04
            // We insert the new node into the linked list after this object
            Node* externalObj = (Node*)externalObjPtr; // treat as Node to access its next
            newNode->next = externalObj->next;
            externalObj->next = newNode;
        }
    }
}