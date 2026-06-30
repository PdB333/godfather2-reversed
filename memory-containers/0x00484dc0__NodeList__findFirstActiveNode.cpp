// FUNC_NAME: NodeList::findFirstActiveNode

// Function at 0x00484dc0
// This method traverses a linked list (starting from m_pHead at +0x08) and returns
// the first node whose active flag (at +0x15) is non-zero.
// Returns: pointer to the first active node, or last node if none active.
// Note: The original decompiler shows void return, but the actual implementation
// leaves the result in EAX, indicating a pointer return.

class NodeList
{
public:
    struct Node
    {
        // +0x00: unknown data
        // +0x08: pointer to next Node (m_pNext)
        Node* m_pNext;
        // +0x0C to +0x14: unknown
        char m_bActive; // +0x15
    };

    Node* findFirstActiveNode()
    {
        Node* pNode = m_pHead; // +0x08 of this

        // If the current node is inactive, follow the chain
        while (pNode->m_bActive == '\0')
        {
            pNode = pNode->m_pNext; // follow next pointer at +0x08
        }

        // Post-loop: pNode points to the first active node (or end of list)
        // The function implicitly returns pNode in EAX.
        return pNode;
    }

private:
    // +0x08: pointer to head of list (m_pHead)
    Node* m_pHead;
};