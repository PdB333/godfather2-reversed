// FUNC_NAME: LinkedList::insertFront

struct LinkedListNode {
    LinkedListNode* pPrev; // +0x88
    LinkedListNode* pNext; // +0x8C
    LinkedList* pOwner;    // +0x80
    // Other data may follow
};

struct LinkedList {
    LinkedListNode* pHead; // +0x84
    // Other fields
};

void __thiscall LinkedList::insertFront(LinkedList* this, LinkedListNode* pNode)
{
    // Insert pNode at the head of the list
    pNode->pPrev = this->pHead;   // +0x88 = [this]+0x84
    pNode->pNext = nullptr;       // +0x8C = 0

    if (this->pHead != nullptr) {
        // Update the old head's previous pointer to point to the new node
        this->pHead->pNext = pNode; // +0x8C of old head = pNode
    }

    this->pHead = pNode;         // +0x84 = pNode
    pNode->pOwner = this;        // +0x80 = this

    // Post-insertion callback (likely notification or list maintenance)
    FUN_006101b0();
}