// FUNC_NAME: ListNode::setDataAndInsertAfter

// Reconstructed from 0x00707860: ListNode member function for setting the data pointer and inserting the node into a linked list after the given node.

class ListNode {
public:
    void* data;       // +0x00: Pointer to associated object (or AnotherListNode?)
    ListNode* next;   // +0x04: Next node in list
};

// Helper function at 0x004daf90 – removes this node from its current list
extern void unlinkNode(ListNode* node);

ListNode* __thiscall ListNode::setDataAndInsertAfter(ListNode* this, ListNode* newData)
{
    // If the current data is different from the new data
    if (this->data != newData) {
        // If current data is not null, remove this node from its old list
        if (this->data != 0) {
            unlinkNode(this);
        }
        // Set the new data pointer
        this->data = newData;
        // If new data is valid, insert this node after newData in its list
        if (newData != 0) {
            this->next = newData->next;   // Link to newData's successor
            newData->next = this;         // Make newData point to this node
        }
    }
    return this;
}