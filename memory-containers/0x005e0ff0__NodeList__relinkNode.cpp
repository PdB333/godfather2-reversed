// FUNC_NAME: NodeList::relinkNode
// Address: 0x005e0ff0
// This function removes the node that follows 'this' in a linked list and then relinks
// 'this' into the list at the position originally occupied by the removed node.
// The list head is stored at +0x1c in the container object (param2).
// Nodes are expected to have the following layout:
//   +0x00: user data
//   +0x04: pointer to previous Link (or pointer to pointer representing "prev")
//   +0x08: pointer to next Link (or pointer to pointer representing "next")
// Links are structured as:
//   +0x00: mNext (pointer to next Link)
//   +0x04: mPrev (pointer to previous Link)
// Some nodes carry a flag at +0x15 (non‑zero means sentinel or special state).

void __thiscall NodeList::relinkNode(int node, int listContainer)
{
    // Remove the next node from the list
    int* nextLink = *(int**)(node + 8);               // node->mNextLink
    *(int*)(node + 8) = *nextLink;                    // node->mNextLink = nextLink->mNext
    int* skippedNode = (int*)*nextLink;               // address of the node that follows the removed one
    if (*(char*)(skippedNode + 0x15) == '\0') {
        *(int*)(skippedNode + 4) = node;              // set its mPrevLink to this node
    }
    nextLink[1] = *(int*)(node + 4);                  // removed node's mPrevLink = node->mPrevLink

    // Insert 'node' back into the list at the new position
    int head = *(int*)(listContainer + 0x1c);         // ListHead* at +0x1c
    // Treat the last pointer as being at +0x04 in the head structure
    if (node == *(int*)(head + 4)) {                  // if node is currently the last element
        *(int*)(head + 4) = (int)nextLink;            // head->mLast = nextLink
        *nextLink = node;                             // nextLink->mNext = node
        *(int**)(node + 4) = nextLink;                // node->mPrevLink = nextLink
        return;
    }

    int* prevLink = *(int**)(node + 4);               // node->mPrevLink
    if (node == *prevLink) {                          // if node is the first element
        *prevLink = (int)nextLink;                    // previous link's mNext = nextLink
        *nextLink = node;                             // nextLink->mNext = node
        *(int**)(node + 4) = nextLink;                // node->mPrevLink = nextLink
        return;
    }

    // General case: node is somewhere in the middle
    prevLink[2] = (int)nextLink;                      // previous link's third field (likely mNext of previous node?) = nextLink
    *nextLink = node;                                 // nextLink->mNext = node
    *(int**)(node + 4) = nextLink;                    // node->mPrevLink = nextLink
    return;
}