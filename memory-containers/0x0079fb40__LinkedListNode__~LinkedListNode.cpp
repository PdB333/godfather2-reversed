// FUNC_NAME: LinkedListNode::~LinkedListNode
int __thiscall LinkedListNode::~LinkedListNode(byte deallocFlag) {
    // +0x28: virtual function table (vtable) pointer
    this->vtable = &PTR_LAB_00e317cc;

    // +0x18: pointer to previous node in the linked list (prev)
    // +0x1c: pointer to next node in the linked list (next)
    // +0x20: pointer to data (likely owned by this node)
    if (this->prev != nullptr) {
        if (this->next == nullptr) {
            // Only previous node exists: update its next pointer to the data
            this->prev->next = reinterpret_cast<LinkedListNode*>(this->data);
        } else {
            // Next node exists: update its prev pointer to the data
            this->next->prev = reinterpret_cast<LinkedListNode*>(this->data);
        }
        if (this->data != nullptr) {
            // Update data's next pointer to the next node
            this->data->next = reinterpret_cast<LinkedListNode*>(this->next);
        }
    }

    // Call base destructor (likely from a base class)
    FUN_0064d150();

    // If the deallocation flag is set, free the memory
    if ((deallocFlag & 1) != 0) {
        operator delete(this);
    }

    return reinterpret_cast<int>(this);
}