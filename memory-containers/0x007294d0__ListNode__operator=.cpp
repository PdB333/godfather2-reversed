// FUNC_NAME: ListNode::operator=
// Function at 0x007294d0: Assignment operator for an intrusive linked list node with a double‑pointer back‑link.
// This is a __thiscall member function of a node class used in TNL‑style intrusive lists.
// Field layout:
//   +0x00 : data (value being stored)
//   +0x04 : next (pointer to the next node)
//   +0x08 : pprev (pointer to the pointer that points to this node, used for O(1) removal)

class ListNode {
public:
    void* data;           // +0x00
    ListNode* next;       // +0x04
    ListNode** pprev;     // +0x08

    // FUN_004daf90 – helper to unlink a node from its list by updating its pprev target
    static void unlinkNode(ListNode** nodePtr);

    ListNode& operator=(const ListNode& other) {
        data = other.data;

        // Check if the 'next' fields are at the same address (self‑assignment or same target)
        if (&next != &other.next) {
            if (next != other.next) {
                // Remove the old 'next' node from its container (if it existed)
                if (next != nullptr) {
                    unlinkNode(&next);
                }
                // Copy the new 'next' pointer
                next = other.next;

                // Link the new 'next' node back to this node
                if (next != nullptr) {
                    // Save the previous back‑link of the new next node (unused here, but preserved)
                    pprev = next->pprev;
                    // Make the new next node point back to the 'next' field of this node
                    next->pprev = &next;
                }
            }
        }
        return *this;
    }
};