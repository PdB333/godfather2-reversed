// FUNC_NAME: IntrusiveList::spliceNodeAfter
// @ addr 0x00484c10
// Intrusive doubly-linked list node manipulation.
// This method moves a node (pointed to by currentNode->next) to a position
// just after currentNode, adjusting the corresponding list head (tail pointer)
// and neighbor links.
//
// Structures (offsets in bytes):
//   IntrusiveListNode {
//       IntrusiveListNode* next;           // +0x00
//       IntrusiveListNode* prev;           // +0x04
//       IntrusiveListNode* secondNext;     // +0x08 (secondary forward link, used for splicing)
//       unsigned char   flag;              // +0x15 (21)
//   }
//   IntrusiveListHead {
//       IntrusiveListNode* head;           // +0x00 (not used directly here)
//       IntrusiveListNode* tail;           // +0x04 (tail pointer, tail->prev is the last real node)
//   }

void __thiscall IntrusiveList::spliceNodeAfter(IntrusiveListNode* currentNode, IntrusiveListHead* listHead) {
    // The node to move is stored in currentNode->next (offset 0x00)
    IntrusiveListNode* nodeToMove = currentNode->next;

    // Detach nodeToMove from currentNode by updating currentNode->next to nodeToMove->secondNext
    currentNode->next = nodeToMove->secondNext;

    // If nodeToMove's successor has its flag unset, update its prev pointer to currentNode
    if (nodeToMove->secondNext->flag == 0) {
        nodeToMove->secondNext->prev = currentNode;
    }

    // Give nodeToMove the same prev as currentNode
    nodeToMove->prev = currentNode->prev;

    // Check if currentNode is the last real node (i.e., equal to tail->prev)
    if (currentNode == listHead->tail->prev) {
        // Update tail->prev to point to nodeToMove
        listHead->tail->prev = nodeToMove;
        // Set nodeToMove->secondNext to currentNode (forming a cycle? or linking back)
        nodeToMove->secondNext = currentNode;
        // Update currentNode->prev to nodeToMove
        currentNode->prev = nodeToMove;
        return;
    }

    // Get the node that was before currentNode
    IntrusiveListNode* prevNode = currentNode->prev;

    // If currentNode is exactly prevNode->secondNext, we can do a direct swap
    if (currentNode == prevNode->secondNext) {
        prevNode->secondNext = nodeToMove;
        nodeToMove->secondNext = currentNode;
        currentNode->prev = nodeToMove;
        return;
    }

    // General case: update prevNode->next to nodeToMove
    prevNode->next = nodeToMove;
    nodeToMove->secondNext = currentNode;
    currentNode->prev = nodeToMove;
}