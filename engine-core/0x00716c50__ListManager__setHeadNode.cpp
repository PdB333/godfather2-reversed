// FUNC_NAME: ListManager::setHeadNode

// This function sets the head node of a linked list.
// The head node pointer is stored at this+0x1c78.
// The node is embedded at object+0x48.
// The node's field at +4 is a pointer that will point back to the head variable address.
// The function removes any existing head before setting the new one.

void __thiscall ListManager::setHeadNode(ListManager* this, void* object) {
    // Pointer to the head variable in the list manager (at offset 0x1c78)
    int** headPtr = (int**)((char*)this + 0x1c78);

    // Compute the node pointer from the object: embedded at object+0x48
    int* newNode;
    if (object == nullptr) {
        newNode = nullptr;
    } else {
        newNode = (int*)((char*)object + 0x48);
    }

    // Only update if the head is different from the new node
    if (*headPtr != newNode) {
        // Remove the old head node from the list (if it exists)
        if (*headPtr != nullptr) {
            FUN_004daf90(headPtr);  // function that removes the node pointed by *headPtr
        }

        // Set the new head
        *headPtr = newNode;

        // If a new node is being attached, update its backward pointer and save old value
        if (newNode != nullptr) {
            // Save the old value of newNode+4 into this+0x1c7c
            *(int**)((char*)this + 0x1c7c) = *(int**)(newNode + 1); // newNode+4
            // Set newNode+4 to point to the head variable
            *(int***)(newNode + 1) = headPtr;
        }
    }
}