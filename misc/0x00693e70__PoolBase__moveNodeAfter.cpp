// FUNC_NAME: PoolBase::moveNodeAfter
// Function at 0x00693e70: Moves a node from its current position to after a specified target node in a doubly linked list.
// 'this' points to a PoolBase object (offset +0x4 points to PoolList - contains head/tail pointers).
// param_2 points to a 'Link' struct (two pointers: current node, target node for insertion after).
// Node struct: +0x4 prev, +0x8 next, +0x25 usedFlag (0 = inactive/head sentinel, non-zero = active).
void __thiscall PoolBase::moveNodeAfter(PoolBase* this, int* link)
{
    int* node;          // the node to move
    int* nextNode;      // node->next
    int* targetPrev;    // link[1] is the node after which to insert (or sentinel)
    int* poolList;       // &this->poolList

    node = (int*)*link;                         // node = link->current
    *link = *(int*)(node + 8);                  // advance link->current to node->next (removing node from its old position)
    nextNode = (int*)*(int*)(node + 8);         // node->next
    if (*(char*)(nextNode + 0x25) == '\0') {    // if next node is not active (head sentinel)
        *(int**)(nextNode + 4) = link;          // set nextNode->prev to point to the link (for re-traversal)
    }
    *(int*)(node + 4) = link[1];                // node->prev = link->target (node after which to insert)
    targetPrev = (int*)link[1];
    poolList = (int*)*(int*)(this + 4);         // poolList = this->poolList

    if (link == (int*)*(int*)(poolList + 4)) {  // if link is the tail of the list (link address equals tail pointer)
        *(int*)(poolList + 4) = (int)node;      // tail = node
        *(int**)(node + 8) = link;              // node->next = link (pointing back to the link/sentinel)
        link[1] = (int)node;                    // link->target = node (update the link's target)
        return;
    }

    // targetPrev is the node after which we want to insert
    if (link == (int*)targetPrev[2]) {          // if link is the 'next' field of the target node (i.e., target->next == link)
        targetPrev[2] = (int)node;              // target->next = node
        *(int**)(node + 8) = link;              // node->next = link
        link[1] = (int)node;                    // link->target = node
        return;
    }

    *targetPrev = (int)node;                    // target->prev = node (insert before target? Actually this is unusual)
    *(int**)(node + 8) = link;                  // node->next = link
    link[1] = (int)node;                        // link->target = node
    return;
}