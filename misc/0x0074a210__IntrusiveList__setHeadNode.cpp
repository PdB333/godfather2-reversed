// FUNC_NAME: IntrusiveList::setHeadNode
void __thiscall IntrusiveList::setHeadNode(void* item) {
    // Embedded list node is at offset 0x48 in the passed object
    ListNode* newNode = (item != nullptr) ? reinterpret_cast<ListNode*>(static_cast<char*>(item) + 0x48) : nullptr;

    // Pointer to the head pointer of the linked list (at this+0xC0)
    ListNode** headPtr = reinterpret_cast<ListNode**>(static_cast<char*>(this) + 0xC0);
    ListNode* oldHead = *headPtr;

    if (oldHead != newNode) {
        // Release the previous head if it existed
        if (oldHead != nullptr) {
            // FUN_004daf90 likely frees or detaches the node
            releaseNode(headPtr);
        }

        // Update the head pointer
        *headPtr = newNode;

        if (newNode != nullptr) {
            // Save the existing next pointer of the new node into this+0xC4
            // (possibly for restoration or iteration)
            *reinterpret_cast<int*>(static_cast<char*>(this) + 0xC4) = 
                *reinterpret_cast<int*>(static_cast<char*>(newNode) + 4);

            // Set the new node's next pointer to point to the head pointer itself
            // Enables O(1) removal by updating the pointer that points to this node
            *(reinterpret_cast<int**>(static_cast<char*>(newNode) + 4)) = headPtr;
        }
    }
}