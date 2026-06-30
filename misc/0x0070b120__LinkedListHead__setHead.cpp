// FUNC_NAME: LinkedListHead::setHead
// Function address: 0x0070b120
// Role: Sets the head of an intrusive singly linked list.
// The head object (this) has fields:
//   +0x08: pointer to the head node (Node*)
//   +0x0C: storage for the previous next pointer of the inserted node
// The node is embedded at offset 0x48 within the passed object.
// When a non-null object is inserted, its node's next pointer is redirected to
// point to the head pointer field, storing the old next in +0x0C.
// The old head (if any) is released via removeNode().

class LinkedListHead {
    // Offset relative to this:
    // +0x08: Node* headPtr  
    // +0x0C: Node* savedNext (backup of new node's original next)
    
    struct Node {
        // +0x00: (unused in this function)
        // +0x04: Node* next
    };

    // External function: remove node at the address of head pointer.
    void __thiscall removeNode(int** headPtrAddr);  // FUN_004daf90

public:
    void __thiscall setHead(void* object) {
        // Get pointer to the head pointer field
        int** headPtrAddr = reinterpret_cast<int**>(this + 8);
        
        // Adjust object pointer to the embedded node (offset 0x48)
        Node* newNode = nullptr;
        if (object != nullptr) {
            newNode = reinterpret_cast<Node*>(reinterpret_cast<char*>(object) + 0x48);
        }
        
        if (*headPtrAddr != newNode) {
            // Release the old head node if it exists
            if (*headPtrAddr != nullptr) {
                removeNode(headPtrAddr);
            }
            
            // Set new head
            *headPtrAddr = newNode;
            
            if (newNode != nullptr) {
                // Save the old next pointer of the new node
                *reinterpret_cast<int*>(this + 0x0C) = *reinterpret_cast<int*>(newNode + 4);
                
                // Redirect node's next to point to the head pointer field
                *reinterpret_cast<int**>(newNode + 4) = headPtrAddr;
            }
        }
    }
};