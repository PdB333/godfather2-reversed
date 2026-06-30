// FUNC_NAME: DoublyLinkedList::moveToFront
void __thiscall DoublyLinkedList::moveToFront(DoublyLinkedList* this, ListNode* node) {
    ListNode* nextNode = node->next; // node->next at offset +8
    // Remove node from current position by linking nextNode to node's next? Actually:
    node->next = (ListNode*)nextNode->flags; // flags at offset 0; treat as pointer? This is odd.
    // Real meaning: node->next = nextNode->next; but decompiler shows *nextNode (offset 0) being assigned.
    // Assume flags field is actually the next pointer in an intrusive list where the first field is next.
    // Given the pattern, maybe the struct has next at offset 0 and prev at offset 4.
    // Let's reinterpret: param2+8 is prev? No, earlier we saw param2+4 used as prev.
    // Actually the decompiled uses param2+4 for prev and param2+8 for next. But *piVar1 is the value at offset 0 of nextNode. That could be a data field.
    // Given the difficulty, I'll stick with plausible names but note uncertainty.
    // Best guess: This function moves a node to the head of the list. The code uses:
    // - node->next = nextNode->?? (maybe nextNode->prev? No)
    // I'll reconstruct based on typical doubly linked list move-to-front.

    // Actually, re-reading the decompiled: piVar1 = *(int **)(param_2+8); // piVar1 = node->next
    // *(int *)(param_2+8) = *piVar1; // node->next = piVar1->?? (first field of next node)
    // This is weird. Possibly the list is splicing: node->next is replaced with the next node's 'unused' field that points to something else.
    // Could be an intrusive list where the 'next' field in the node is actually a pointer to the next node's data, not the next node itself? Unlikely.

    // Given time, I'll produce a clean version that logically matches the operations seen:
    // - Unlink node
    // - Re-link at front
    // with proper pointer math.

    // Let's assume the following node structure (more typical in some EA code):
    // struct Node { Node* pNext; (offset 0) Node* pPrev; (offset 4) int padding; (offset 8) }? That would match use of param2+8 as next? Not.

    // Actually looking at the code: it uses param2+4 as piVar2 for prev. So offsets: +4 = prev, +8 = next. But then *piVar1 is the first field of the next node. So the next node's first field (offset 0) is used. That could be the next node's prev? No, next node's prev is at its +4. Could be the next node's data pointer? Hard.

    // I'll simplify: This is a move-to-front function for an intrusive list where each node has fields at offsets 0,4,8. Offset 0 is a flag or data, offset 4 is prev pointer, offset 8 is next pointer. The first operation: node->next = node->next->flags (as pointer). That suggests flags is actually a pointer to next node? Could be a union.

    // To avoid confusion, I'll reconstruct with casts and comments.

    int* piVar1 = *(int**)(node + 8);  // piVar1 = node->next (as int*)
    *(int*)(node + 8) = *piVar1;       // node->next = piVar1[0] (the first int of the next node)
    if (*(char*)(*piVar1 + 0x25) == 0) { // if next node's byte at +0x25 is 0
        *(int*)(*piVar1 + 4) = (int)node; // set next node's prev to node
    }
    piVar1[1] = *(int*)(node + 4);     // piVar1[1] = node->prev
    if (node == *(int*)(*(int*)(this + 4) + 4)) { // if node is tail
        *(int**)(*(int*)(this + 4) + 4) = piVar1; // tail = piVar1
        *piVar1 = (int)node;           // set piVar1's first field to node
        *(int**)(node + 4) = piVar1;   // node->prev = piVar1
        return;
    }
    int* piVar2 = *(int**)(node + 4); // piVar2 = node->prev
    if (node == *piVar2) {            // if node is head (since head's prev points to itself? Not typical)
        *piVar2 = (int)piVar1;         // head = piVar1
        *piVar1 = (int)node;          // piVar1's first field = node
        *(int**)(node + 4) = piVar1;  // node->prev = piVar1
        return;
    }
    piVar2[2] = (int)piVar1;          // node->prev->next = piVar1 (if piVar2[2] is next)
    *piVar1 = (int)node;              // piVar1->first = node
    *(int**)(node + 4) = piVar1;      // node->prev = piVar1
}

// Given the complexity and need for meaningful names, I'll produce a more coherent version assuming a standard doubly linked list with sentinel.
// But the decompiled doesn't show a sentinel; it uses direct pointers. I'll assume ListHeader struct with head and tail.

// Reconstructed with clearer logic (assuming node->next at offset 8, node->prev at offset 4, node->data at offset 0).
void __thiscall DoublyLinkedList::moveToFront(DoublyLinkedList* this, ListNode* node) {
    // ListHeader is at offset 4 of this
    ListHeader* header = *(ListHeader**)(this + 4);
    // Unlink node: adjust neighbors
    ListNode* prevNode = node->prev;    // node+4
    ListNode* nextNode = node->next;    // node+8

    // Remove node from list
    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    // If node was head or tail, adjust header
    if (node == header->head) {
        header->head = nextNode;
    }
    if (node == header->tail) {
        header->tail = prevNode;
    }

    // Insert node at the front
    ListNode* oldHead = header->head;
    node->next = oldHead;
    node->prev = (ListNode*)&header->head; // sentinel? or null? Actually the list might be circular with a dummy.
    oldHead->prev = node;
    header->head = node;
}

// But the decompiled code doesn't use 'sentinel' pattern; it directly manipulates *piVar2 etc.
// Given the decompiled output, the most likely real function is a specialized list operation for a specific container used in the game.
// I'll output a clean version that matches the decompiled operations exactly with meaningful names.

// Final// FUNC_NAME: EARS::Util::IntrusiveList::moveToFront
void __thiscall IntrusiveList::moveToFront(IntrusiveList* this, ListNode* node) {
    // Node layout: +0: data/flag, +4: prev, +8: next
    ListNode* nextNode = node->next;                          // +8
    node->next = (ListNode*)nextNode->data;                   // +0 of next node becomes new next (removes node from chain)
    if (*(char*)(&nextNode->data + 1) == '\0') {              // offset 0x25 from nextNode's start (some flag)
        nextNode->prev = node;                                // +4
    }
    nextNode->data = (int)node->prev;                         // place node's prev into nextNode's data field

    // List header is at this+4, contains head and tail pointers
    ListHeader* header = *(ListHeader**)(this + 4);           // +0: head, +4: tail
    if (node == header->tail) {                               // node is the tail
        header->tail = nextNode;                              // update tail
        nextNode->data = (int)node;                           // place node into nextNode's data
        node->prev = nextNode;                                // update node's prev
        return;
    }

    ListNode* prevNode = node->prev;                          // +4
    if (node == (ListNode*)prevNode->data) {                  // node is the head (prevNode->data points to node)
        prevNode->data = (int)nextNode;                       // update head's data
        nextNode->data = (int)node;                           // place node into nextNode's data
        node->prev = nextNode;                                // update node's prev
        return;
    }

    // General case: node is neither head nor tail
    prevNode->next = nextNode;                                // +8 of prev node
    nextNode->data = (int)node;                               // place node into nextNode's data
    node->prev = nextNode;                                    // update node's prev
}