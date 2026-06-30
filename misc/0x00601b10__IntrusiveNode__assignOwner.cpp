// FUNC_NAME: IntrusiveNode::assignOwner
// Function address: 0x00601b10
// Role: Assigns a new owner to an intrusive singly-linked node and inserts the node
//       at the front of the owner's list. If the node already belongs to the same owner,
//       no action is taken. If it belonged to a different owner, it is first removed
//       from that list via removeFromCurrentList() (FUN_004daf90). The owner is expected
//       to store its list head pointer at offset +4 (e.g., Owner::firstNode).

// Forward declaration of the owner class (expected to have a pointer at +4)
class Owner;

// Intrusive node with two fields:
//   +0: Owner*   m_owner
//   +4: IntrusiveNode* m_next
class IntrusiveNode {
public:
    Owner*   m_owner;  // +0x00
    IntrusiveNode* m_next; // +0x04

    // Removes this node from its current owner's list (calls FUN_004daf90)
    void removeFromCurrentList();

    // Assigns a new owner and reinserts at the front of that owner's list
    IntrusiveNode* assignOwner(Owner* newOwner);
};

// Implementation
IntrusiveNode* IntrusiveNode::assignOwner(Owner* newOwner) {
    if (m_owner != newOwner) {
        if (m_owner != nullptr) {
            removeFromCurrentList(); // FUN_004daf90 - detaches from old owner
        }

        m_owner = newOwner;

        if (newOwner != nullptr) {
            // Insert at front: newOwner has a list head pointer at offset +4
            m_next = *(IntrusiveNode**)((char*)newOwner + 4); // newOwner->firstNode
            *(IntrusiveNode**)((char*)newOwner + 4) = this;   // newOwner->firstNode = this
        }
    }
    return this;
}