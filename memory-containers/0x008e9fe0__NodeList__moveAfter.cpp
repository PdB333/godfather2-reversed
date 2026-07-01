// FUNC_NAME: NodeList::moveAfter
// Function address: 0x008e9fe0
// Relinks a node to a position after another node in a doubly linked intrusive list.
// param_2 is an iterator structure containing [currentNode, previousNode] pointers.
// The node at *param_2 (current) is moved to be after the previous node (param_2[1]).
// The iterator is then advanced to the next position.

struct ListNode {
    int* m_data;            // +0x00 unknown (likely data pointer or offset)
    ListNode* m_prev;       // +0x04 previous node
    ListNode* m_next;       // +0x08 next node
    // +0x0C..+0x18 unknown/padding
    char m_isDummy;         // +0x19 flag indicating a sentinel/dummy head node
};

struct ListHeader {
    ListNode* m_head;       // +0x00 head of list (dummy?)
    ListNode* m_tail;       // +0x04 tail of list
};

class NodeList {
public:
    ListNode* m_pHeader;    // +0x04 pointer to ListHeader

    // Moves the node pointed to by param_2 (iterator) to after param_2[1].
    // The iterator is advanced to the next node.
    void __thiscall moveAfter(int* param_2) {
        ListNode* currentNode = (ListNode*)*param_2;        // node to be moved
        *param_2 = (int)currentNode->m_next;                // advance iterator to next

        // If next node is not a dummy head, update its prev pointer
        if (currentNode->m_next->m_isDummy == 0) {
            currentNode->m_next->m_prev = (ListNode*)param_2;
        }

        currentNode->m_prev = (ListNode*)param_2[1];        // link node to previous in iterator

        ListHeader* header = (ListHeader*)m_pHeader;
        // If the iterator is at the tail (i.e., param_2 equals header->tail pointer address)
        if ((int*)param_2 == (int*)(&header->m_tail)) {
            header->m_tail = currentNode;                   // new tail
            currentNode->m_next = (ListNode*)param_2;       // next is the dummy tail indicator
            param_2[1] = (int)currentNode;                  // update previous pointer
            return;
        }

        // Otherwise, get the current previous node from iterator
        ListNode* prevNode = (ListNode*)param_2[1];
        // If iterator's position is exactly after prevNode (normal case)
        if ((ListNode*)param_2 == prevNode->m_next) {
            prevNode->m_next = currentNode;                 // link prevNode to currentNode
            currentNode->m_next = (ListNode*)param_2;       // currentNode's next is the iterator position
            param_2[1] = (int)currentNode;                  // iterator's previous becomes currentNode
            return;
        }

        // Edge case: param_2 is not directly after prevNode (list was corrupted?)
        prevNode->m_data = (int*)currentNode;               // overwrite prevNode data? (likely error handling)
        currentNode->m_next = (ListNode*)param_2;
        param_2[1] = (int)currentNode;
    }
};