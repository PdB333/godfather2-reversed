// FUNC_NAME: EARSObject::insertNodeAfterSelf
// 0x004a2f60: Attaches a ListNode to this object's embedded list, inserting it immediately after this object's own node (at offset +0x48).
// ListNode structure: offset 0 = pListHead (pointer to the list's dummy head node), offset 4 = pNext.
// The object at +0x48 is the dummy head node (m_node), making this a singly linked list with a sentinel.

class EARSObject {
public:
    struct ListNode {
        ListNode* pListHead; // +0x00 (compared with &m_node)
        ListNode* pNext;     // +0x04
    } m_node; // +0x48

    // Removes a node from its current list (if any), called by insertNodeAfterSelf.
    // Full implementation not shown – likely unlinks pNode from its list.
    void removeFromList(ListNode* pNode);

    // Inserts pNode into this object's list right after the sentinel head (m_node).
    // If pNode is already attached to this same list (pNode->pListHead == &m_node), no change.
    void __thiscall insertNodeAfterSelf(ListNode* pNode) {
        ListNode* pThisHead = &m_node; // address of the dummy head node

        if (pNode->pListHead != pThisHead) {
            if (pNode->pListHead != nullptr)
                removeFromList(pNode); // remove from previous list

            pNode->pListHead = pThisHead; // mark as belonging to this list

            // Insert pNode immediately after pThisHead (new first real element)
            pNode->pNext = pThisHead->pNext;
            pThisHead->pNext = pNode;
        }
    }
};