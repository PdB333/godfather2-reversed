// FUNC_NAME: IntrusiveNode::assign
// Function address: 0x005f7ba0
// Role: Assigns the contents of one intrusive linked list node to another,
//       handling the doubly linked list pointers and freeing the old value if replaced.

class IntrusiveNode {
public:
    int* m_value;   // +0x00: Pointer to some owned value (may be null)
    IntrusiveNode* m_next;  // +0x04: Next node in the doubly linked list
    IntrusiveNode* m_prev;  // +0x08: Previous node in the doubly linked list

    // __thiscall
    IntrusiveNode* assign(IntrusiveNode* other) {
        if (this == other) {
            // Copy to self: no-op, but still copy prev field at end
        } else {
            int* newValue = other->m_value;
            if (m_value != newValue) {
                // Free old value if non-null
                if (m_value != nullptr) {
                    FUN_004daf90(this); // Frees the node's value (likely a destructor call)
                }
                m_value = newValue;
                if (newValue != nullptr) {
                    // Update the doubly linked list: link this node after the value's current next pointer
                    m_next = reinterpret_cast<IntrusiveNode*>(newValue[1]); // +4 of value is next pointer
                    reinterpret_cast<IntrusiveNode**>(newValue + 1)[0] = this; // value->next = this
                }
            }
        }
        // Copy the previous pointer from source (this may later be adjusted by caller)
        m_prev = other->m_prev;
        return this;
    }
};

// Note: FUN_004daf90 at 0x004daf90 is likely a destructor or deallocation function for the value pointed to by m_value.