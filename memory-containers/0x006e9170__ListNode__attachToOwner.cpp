// FUNC_NAME: ListNode::attachToOwner
// Reconstructed from 0x006e9170 - attaches this node to another object's node list at offset 0x48
// The class has two pointers: m_pNode (owner node) and m_pNext (singly linked list next)
// Detaches from previous owner's list and inserts at front of the new owner's list.

class ListNode {
public:
    ListNode* m_pNode;  // +0x00: pointer to the node we are attached to (can be null)
    ListNode* m_pNext;  // +0x04: next element in the singly linked list

    // Removes this node from whatever list it is currently in (called FUN_004daf90)
    __thiscall void detachFromList();

    // Attaches this node to the given owner object's internal node (at offset 0x48 in the owner).
    // If pOwner is null, we detach and set m_pNode to null.
    // If pOwner is non-null, we insert ourselves at the front of the target node's list.
    __thiscall ListNode* attachToOwner(void* pOwner) {
        ListNode* pTargetNode;
        if (pOwner != nullptr) {
            // Owner object has a ListNode member at offset 0x48
            pTargetNode = reinterpret_cast<ListNode*>(static_cast<char*>(pOwner) + 0x48);
        } else {
            pTargetNode = nullptr;
        }

        if (m_pNode != pTargetNode) {
            if (m_pNode != nullptr) {
                detachFromList();  // remove from previous list
            }
            m_pNode = pTargetNode;

            if (pTargetNode != nullptr) {
                // Insert at front of target node's list
                m_pNext = pTargetNode->m_pNext;
                pTargetNode->m_pNext = this;
            } else {
                // When pTargetNode is null, we are detached; m_pNext is left unchanged (but will be overwritten on next attach)
            }
        }
        return this;
    }
};